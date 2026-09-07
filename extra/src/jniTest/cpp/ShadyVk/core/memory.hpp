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
#include <cstdint>
#include <atomic>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <array>
#include <string>
#include <vector>

#include "types.hpp"

#define BLOCK_INDEX_NULL UINT32_MAX

struct FreeIndices {

        void push(u32 index);
        u32 pop();

    private:
        u32 top = 0;
        std::array<u32, 256> indices = {};
    };

    struct LockFreeIndices {

        LockFreeIndices() = default;

        LockFreeIndices(const LockFreeIndices& other) noexcept {
            u32 top = other.top.load(std::memory_order_relaxed);
            this->top.compare_exchange_weak(top, top, std::memory_order_release, std::memory_order_relaxed);
            indices = other.indices;
        }

        LockFreeIndices(LockFreeIndices&& other) noexcept {
            u32 top = other.top.load(std::memory_order_relaxed);
            this->top.compare_exchange_weak(top, top, std::memory_order_release, std::memory_order_relaxed);
            indices = other.indices;
        }

        void push(u32 index);
        u32 pop();

    private:
        std::atomic<u32> top = { 0 };
        std::array<u32, 256> indices = {};
    };

    struct MemoryProvider {
        void* allocate(size_t size);
        void free(void* address, size_t size);
        void* reallocate(void* oldAddress, size_t oldSize, size_t newSize);

    private:
        static constexpr auto TAG = "MemoryProvider";
    };

    struct MemoryPoolStats {
        size_t blocks = 0;
        size_t used_blocks = 0;
        size_t reallocations = 0;
    };

    struct MemoryPool {

        void create(size_t block_count, size_t block_size);
        void destroy();

        u32 allocate();
        void free(u32 index);
        void* getAddress(u32 index) const;
        MemoryPoolStats getStats() const;

    private:
        void resize(size_t new_memory_size);

        void* memory = nullptr;
        size_t memory_size = 0;
        u32 current_block_index = 0;
        size_t block_size = 0;
        size_t realloc_count = 0;
        LockFreeIndices free_indices;
        MemoryProvider memory_provider;

        static constexpr auto TAG = "MemoryPool";
    };

    struct MemoryPoolTable {

        void reserve(size_t capacity);
        void destroy();
        MemoryPool& getOrAdd(size_t block_count, size_t block_size);
        void log();

    private:
        std::unordered_map<size_t, MemoryPool> pools;
        std::mutex mutex;

        static constexpr auto TAG = "MemoryPoolTable";
    };

    struct MemoryArena {

        void create(size_t size);
        void destroy();
        void* allocate(size_t size, size_t alignment = alignof(std::max_align_t));
        void reset();

    private:
        void* memory = nullptr;
        size_t size = 0;
        size_t offset = 0;
        MemoryProvider memory_provider;

        static constexpr auto TAG = "MemoryArena";
    };

    struct LockMemoryArena {

        void create(size_t size);
        void destroy();
        void* allocate(size_t size, size_t alignment = alignof(std::max_align_t));

    private:
        MemoryArena arena;
        std::mutex mutex;
    };

    struct MemoryArenaTable {

        void reserve(size_t capacity);
        void destroy();
        MemoryArena& getOrAdd(size_t typeId, size_t size);
        void log();

    private:
        std::unordered_map<size_t, MemoryArena> arenas;
        std::mutex mutex;

        static constexpr auto TAG = "MemoryArenaTable";
    };

    struct MemoryManager {

        MemoryManager();
        ~MemoryManager();

        static MemoryManager& getInstance();
        MemoryPool& getMemoryPool(size_t block_size);
        MemoryArena& getMemoryArena(size_t typeId, size_t size);
        void log();

    private:
        MemoryPoolTable poolTable;
        MemoryArenaTable arenaTable;
    };

    template<typename T>
    struct Ptr {
        u32 index = BLOCK_INDEX_NULL;

        Ptr() = default;

        ~Ptr() = default;

        Ptr(u32 index) : index(index) {}

        // can copy
        Ptr(const Ptr& other) : index(other.index) {}

        Ptr& operator=(const Ptr& other) {
            index = other.index;
            return *this;
        }

        Ptr& operator=(Ptr& other) {
            index = other.index;
            return *this;
        }

        // can move
        Ptr(Ptr&& other) noexcept : index(other.index), pool(other.pool) {}

        Ptr& operator=(Ptr&& other) noexcept {
            index = other.index;
            return *this;
        }

        template<typename... Args>
        void New(Args &&... args);
        void Delete();

        T* Get() const;

        T& operator*() const noexcept { return *Get(); }
        T* operator->() const noexcept { return Get(); }
        explicit operator bool() const noexcept { return Get(); }

        template<typename U, std::enable_if_t<std::is_convertible_v<T&, U>, int> = 0>
        operator U() const {
            return static_cast<U>(**this);
        }

    protected:
        MemoryPool& pool = MemoryManager::getInstance().getMemoryPool(sizeof(T));
    };

    template<typename T>
    template<typename ... Args>
    void Ptr<T>::New(Args &&...args) {
        if (index != BLOCK_INDEX_NULL) {
            Delete();
        }
        index = pool.allocate();
        new (static_cast<T*>(pool.getAddress(index))) T(std::forward<Args>(args)...);
    }

    template<typename T>
    void Ptr<T>::Delete() {
        if (index != BLOCK_INDEX_NULL) {
            static_cast<T*>(pool.getAddress(index))->~T();
            pool.free(index);
            index = BLOCK_INDEX_NULL;
        }
    }

    template<typename T>
    T* Ptr<T>::Get() const {
        return static_cast<T*>(pool.getAddress(index));
    }

    struct MemoryHeapBlock {
        size_t offset;
        size_t size;
        Ptr<MemoryHeapBlock> next;

        MemoryHeapBlock(size_t offset = 9, size_t size = 0, const Ptr<MemoryHeapBlock>& next = {})
        : offset(offset), size(size), next(next) {}
    };

    struct MemoryHeap {

        void create(size_t size);
        void destroy();

        size_t allocate(size_t size);
        void free(size_t offset, size_t size);
        void log();

    private:
        void mergeFreeBlocks() const;

        size_t size = 0;
        Ptr<MemoryHeapBlock> head;
        MemoryProvider provider;
    };

    template<typename T, size_t type_id = sizeof(T), size_t arena_size = 1024>
    struct STLArenaAllocator {
        using value_type = T;

        MemoryArena& arena = MemoryManager::getInstance().getMemoryArena(type_id, arena_size);

        STLArenaAllocator() = default;

        STLArenaAllocator(MemoryArena& arena) noexcept : arena(arena) {}

        template<typename U>
        STLArenaAllocator(const STLArenaAllocator<U, type_id, arena_size>& other) noexcept : arena(other.arena) {}

        T* allocate(std::size_t n) {
            return static_cast<T*>(arena.allocate(n * sizeof(T), alignof(T)));
        }

        void deallocate(T* p, std::size_t n) noexcept {
            // do nothing
        }

        template<typename U>
        struct rebind { using other = STLArenaAllocator<U, type_id, arena_size>; };

        bool operator==(const STLArenaAllocator& other) {
            return &arena == &other.arena;
        }

        bool operator!=(const STLArenaAllocator& other) {
            return !(*this == other);
        }
    };

    template<typename T, size_t type_id = sizeof(T), size_t arena_size = 1024>
    using Vector = std::vector<T, STLArenaAllocator<T, type_id, arena_size>>;

    template<typename K, typename V, size_t type_id = sizeof(K) + sizeof(V), size_t arena_size = 1024>
    using HashTable = std::unordered_map<K, V, STLArenaAllocator<std::pair<const K, V>, type_id, arena_size>>;

    template<typename T, size_t type_id = sizeof(T), size_t arena_size = 1024>
    using Set = std::set<T, STLArenaAllocator<T, type_id, arena_size>>;

    template<typename T, size_t type_id = sizeof(T), size_t arena_size = 1024>
    using HashSet = std::unordered_set<T, STLArenaAllocator<T, type_id, arena_size>>;

    template<size_t type_id = sizeof(char), size_t arena_size = 1024>
    using BaseString = std::basic_string<char, std::char_traits<char>, STLArenaAllocator<char, type_id, arena_size>>;

    using String = BaseString<>;

#endif //ALLOCATORS_HPP