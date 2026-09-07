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
#include <condition_variable>
#include <mutex>
#include <array>
#include <functional>
#include <thread>
#include "types.hpp"

template<typename T, size_t size>
struct ConcurrentQueue {

    void push(const T& data);
    void pop(T& data);
    bool isEmpty() const;
    bool isFull() const;
    size_t getSize() const { return size; }

private:
    u32 tail = 0;
    u32 head = 0;
    std::array<T, size> queue = {};
    std::mutex mutex;
    std::condition_variable notFull;
    std::condition_variable notEmpty;
};

template<typename T, size_t size>
void ConcurrentQueue<T, size>::push(const T &data) {
    std::unique_lock lock(mutex);
    notFull.wait(lock, [this]() { return !isFull(); });
    queue[head] = data;
    head = (head + 1) % size;
    notEmpty.notify_one();
}

template<typename T, size_t size>
void ConcurrentQueue<T, size>::pop(T& data) {
    std::unique_lock lock(mutex);
    notEmpty.wait(lock, [this]() { return !isEmpty(); });
    data = queue[tail];
    tail = (tail + 1) % size;
    notFull.notify_one();
}

template<typename T, size_t size>
bool ConcurrentQueue<T, size>::isEmpty() const {
    return tail == head;
}

template<typename T, size_t size>
bool ConcurrentQueue<T, size>::isFull() const {
    return (head + 1) % size == tail;
}

struct Task {
    std::function<void()> task = {};
    size_t scheduledTime = 0;
};

struct ThreadPool {

    ThreadPool(u32 size);
    ~ThreadPool();

    void submit(const Task& task);

private:
    void runLoop();

    bool running = false;
    ConcurrentQueue<Task, 100> taskQueue;
};

#endif //THREAD_POOL_HPP
