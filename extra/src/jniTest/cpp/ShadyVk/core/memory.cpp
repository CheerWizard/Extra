/*
 * Copyright 2026 CheerWizard
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "memory.hpp"
#include "logger.hpp"

#include <sys/mman.h>

void FreeIndices::push(u32 index) {
    if (top < indices.size()) {
        indices[top++] = index;
    }
}

u32 FreeIndices::pop() {
    if (top > 0) {
        return indices[--top];
    }
    return BLOCK_INDEX_NULL;
}

void LockFreeIndices::push(u32 index) {
    u32 oldTop = top.load(std::memory_order_relaxed);

    do {
        if (oldTop >= indices.size()) {
            throw std::overflow_error("Failed due to lock free indices stackoverflow");
        }
    } while (!top.compare_exchange_weak(
        oldTop,
        oldTop + 1,
        std::memory_order_release,
        std::memory_order_relaxed
    ));

    indices[oldTop] = index;
}

u32 LockFreeIndices::pop() {
    u32 oldTop = top.load(std::memory_order_relaxed);

    do {
        if (oldTop == 0) {
            return BLOCK_INDEX_NULL;
        }
    } while (!top.compare_exchange_weak(
        oldTop,
        oldTop - 1,
        std::memory_order_acquire,
        std::memory_order_relaxed
    ));

    return indices[oldTop - 1];
}

void* MemoryProvider::allocate(size_t size) {
    void* ptr = mmap(
                nullptr,
                size,
                PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANONYMOUS,
                -1, 0);
    ASSERT(ptr != nullptr && ptr != MAP_FAILED, TAG, "Failed to map memory size %d", size);
    return ptr;
}

void MemoryProvider::free(void* address, size_t size) {
    const int res = munmap(address, size);
    ASSERT(res == 0, TAG, "Failed to unmap memory %p", address);
}

void* MemoryProvider::reallocate(void *oldAddress, size_t oldSize, size_t newSize) {
    void* newAddress = allocate(newSize);
    memcpy(newAddress, oldAddress, oldSize);
    free(oldAddress, oldSize);
    return newAddress;
}

void MemoryPool::create(size_t block_count, size_t block_size) {
    ASSERT(block_size != 0 && block_count != 0, TAG, "block size and count must be greater than zero")
    memory = memory_provider.allocate(block_count * block_size);
    memory_size = block_count * block_size;
    this->block_size = block_size;
    realloc_count = 0;
}

void MemoryPool::destroy() {
    memory_provider.free(memory, memory_size);
    memory = nullptr;
    memory_size = 0;
    current_block_index = 0;
    realloc_count = 0;
}

u32 MemoryPool::allocate() {
    u32 free_index = free_indices.pop();
    if (free_index != BLOCK_INDEX_NULL) {
        return free_index;
    }

    if (memory_size < (current_block_index + 1) * block_size) {
        resize(memory_size == 0 ? 100 * block_size : memory_size * 2);
    }

    return current_block_index++;
}

void MemoryPool::free(u32 index) {
    free_indices.push(index);
}

void* MemoryPool::getAddress(u32 index) const {
    if (index >= current_block_index || index == BLOCK_INDEX_NULL || memory == nullptr) return nullptr;
    return static_cast<char*>(memory) + index * block_size;
}

MemoryPoolStats MemoryPool::getStats() const {
    return {
        .blocks = memory_size / block_size,
        .used_blocks = current_block_index,
        .reallocations = realloc_count
    };
}

void MemoryPool::resize(size_t new_memory_size) {
    memory = memory_provider.reallocate(memory, memory_size, new_memory_size);
    memory_size = new_memory_size;
    realloc_count++;
}

void MemoryPoolTable::reserve(size_t capacity) {
    pools.reserve(capacity);
}

void MemoryPoolTable::destroy() {
    for (auto& pool : pools) {
        pool.second.destroy();
    }
    pools.clear();
}

MemoryPool& MemoryPoolTable::getOrAdd(size_t block_count, size_t block_size) {
    std::lock_guard lock(mutex);

    auto entry = pools.find(block_size);
    if (entry != pools.end()) {
        return entry->second;
    }

    pools.emplace(block_size, MemoryPool());
    auto& pool = pools.at(block_size);
    pool.create(block_count, block_size);
    return pool;
}

void MemoryPoolTable::log() {
#ifdef DEBUG
    u32 i = 0;
    for (const auto& pool : pools) {
        size_t block_size = pool.first;
        MemoryPoolStats stats = pool.second.getStats();
        LOG_INFO(TAG, "\n----------------- MemoryPool-%d ------------------\n"
                 "Block Size: %d bytes\n"
                 "Blocks: %d\n"
                 "Used Blocks: %d\n"
                 "Free Blocks: %d\n"
                 "Reallocations: %d\n",
                 ++i, block_size,
                 stats.blocks, stats.used_blocks, stats.blocks - stats.used_blocks,
                 stats.reallocations
        );
    }
#endif
}

void MemoryArena::create(size_t size) {
    memory = memory_provider.allocate(size);
    this->size = size;
    offset = 0;
}

void MemoryArena::destroy() {
    memory_provider.free(memory, size);
    memory = nullptr;
    size = 0;
    offset = 0;
}

void* MemoryArena::allocate(size_t size, size_t alignment) {
    size_t current = reinterpret_cast<size_t>(memory) + offset;
    size_t aligned = (current + alignment - 1) & ~(alignment - 1);
    size_t next_offset = aligned - reinterpret_cast<size_t>(memory) + size;

    if (next_offset > this->size) {
        size_t new_size = this->size == 0 ? size * 2 : this->size * 2;
        memory = memory_provider.reallocate(memory, this->size, new_size);
        this->size = new_size;
        current = reinterpret_cast<size_t>(memory) + offset;
        aligned = (current + alignment - 1) & ~(alignment - 1);
        next_offset = aligned - reinterpret_cast<size_t>(memory) + size;
    }

    this->offset = next_offset;
    return reinterpret_cast<void*>(aligned);
}

void MemoryArena::reset() {
    offset = 0;
}

void LockMemoryArena::create(size_t size) {
    std::lock_guard lock(mutex);
    arena.create(size);
}

void LockMemoryArena::destroy() {
    std::lock_guard lock(mutex);
    arena.destroy();
}

void* LockMemoryArena::allocate(size_t size, size_t alignment) {
    std::lock_guard lock(mutex);
    void* ptr = arena.allocate(size, alignment);
    return ptr;
}

void MemoryArenaTable::reserve(size_t capacity) {
    arenas.reserve(capacity);
}

void MemoryArenaTable::destroy() {
    for (auto& arena : arenas) {
        arena.second.destroy();
    }
    arenas.clear();
}

MemoryArena& MemoryArenaTable::getOrAdd(size_t typeId, size_t size) {
    std::lock_guard lock(mutex);

    size_t key = typeId ^ (size + 0x9e3779b9 + (typeId << 6) + (typeId >> 2));

    auto entry = arenas.find(key);
    if (entry != arenas.end()) {
        return entry->second;
    }

    arenas.emplace(key, MemoryArena());
    auto& arena = arenas.at(key);
    arena.create(size);
    return arena;
}

void MemoryArenaTable::log() {
}

void MemoryHeap::create(size_t size) {
    head.New(0, size);
    this->size = size;
}

void MemoryHeap::destroy() {
}

size_t MemoryHeap::allocate(size_t size) {
    Ptr<MemoryHeapBlock> prev;
    Ptr<MemoryHeapBlock> current = head;
    while (current) {
        if (current->size >= size) {
            size_t offset = current->offset;
            if (current->size == size) {
                if (prev) prev->next = current->next;
                else head = current->next;
                current.Delete();
            } else {
                current->offset += size;
                current->size -= size;
            }
            return offset;
        }
        prev = current;
        current = current->next;
    }
    return -1;
}

void MemoryHeap::free(size_t offset, size_t size) {
    Ptr<MemoryHeapBlock> prev;
    Ptr<MemoryHeapBlock> current = head;

    while (current && current->offset < offset) {
        prev = current;
        current = current->next;
    }

    Ptr<MemoryHeapBlock> newBlock;
    newBlock.New(offset, size, current);

    if (prev) prev->next = newBlock;
    else head = newBlock;

    mergeFreeBlocks();
}

void MemoryHeap::mergeFreeBlocks() const {
    Ptr<MemoryHeapBlock> current = head;

    while (current && current->next) {
        if (current->offset + current->size == current->next->offset) {
            Ptr<MemoryHeapBlock> next = current->next;
            current->size += next->size;
            current->next = next->next;
            next.Delete();
        } else {
            current = current->next;
        }
    }
}

void MemoryHeap::log() {
}

MemoryManager::MemoryManager() {
    poolTable.reserve(10);
    arenaTable.reserve(10);
}

MemoryManager::~MemoryManager() {
    poolTable.destroy();
    arenaTable.destroy();
}

MemoryManager& MemoryManager::getInstance() {
    static MemoryManager instance;
    return instance;
}

MemoryPool& MemoryManager::getMemoryPool(size_t block_size) {
    return poolTable.getOrAdd(100, block_size);
}

MemoryArena& MemoryManager::getMemoryArena(size_t typeId, size_t size) {
    return arenaTable.getOrAdd(typeId, size);
}

void MemoryManager::log() {
    poolTable.log();
    arenaTable.log();
}