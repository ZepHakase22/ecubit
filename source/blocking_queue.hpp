#if !defined(BLOCKING_QUEUE_HPP)
#define BLOCKING_QUEUE_HPP

#include <iostream>
#include <algorithm>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

template<typename T>
class blocking_queue {
private:
    size_t capacity;
    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable _not_full;
    std::condition_variable _not_empty;

public:
    inline blocking_queue(size_t capacity_) : capacity(capacity_) {
        // empty
    }

    inline void set_capacity(size_t capacity_) {
        capacity = capacity_;
    }
    inline size_t size() const {
        std::unique_lock<std::mutex> lock(_mutex);
        return _queue.size();
    }

    inline bool empty() const {
        std::unique_lock<std::mutex> lock(_mutex);
        return _queue.empty();
    }

    inline void push(const T& elem) {
        {
            std::unique_lock<std::mutex> lock(_mutex);

            // wait while the queue is full
            while (_queue.size() >= capacity) {
                _not_full.wait(lock);
            }
            _queue.push(elem);
        }
        _not_empty.notify_all();
    }

   inline const T& popAndFront() {
        {
            std::unique_lock<std::mutex> lock(_mutex);

            // wait while the queue is empty
            while (_queue.size() == 0) {
                _not_empty.wait(lock);
            }
            const T& elem = _queue.front();
            _queue.pop();
            return elem;
        }
        _not_full.notify_one();
    }

    inline void pop() {
        {
            std::unique_lock<std::mutex> lock(_mutex);

            // wait while the queue is empty
            while (_queue.size() == 0) {
                _not_empty.wait(lock);
            }
            _queue.pop();
        }
        _not_full.notify_one();
    }


    inline const T& front() {
        std::unique_lock<std::mutex> lock(_mutex);

        // wait while the queue is empty
        while (_queue.size() == 0) {
            _not_empty.wait(lock);
        }
        return _queue.front();
    }
};

#endif //BLOCKING_QUEUE_HPP