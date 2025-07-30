//
// Created by Vivian Lopez on 30/07/2025.
//

#pragma once

// Simplified version of std::shared_ptr. Manages a dynamically allocated object T* obj and keeps track of
// how many SmartPtrs share the same object using a RefCounter

class RefCounter {
public:
    RefCounter() : m_counter(1) {}
    RefCounter(const RefCounter&) = delete;
    RefCounter& operator=(const RefCounter&) = delete;

    void increment() { ++m_counter; }
    void decrement() { --m_counter; }
    int get() const { return m_counter; };

private:
    int m_counter;
};

template<typename T>
class SharedPtr {
public:
    explicit SharedPtr(T* raw = nullptr) : obj(raw), counter(nullptr) {
        // Only need a RefCounter if obj is not nullptr
        if (obj != nullptr) {
            counter = new RefCounter();
        }
    }

    SharedPtr(const SharedPtr& other) : obj(other.obj), counter(other.counter) {
        // if we copy a SmartPtr with no obj then we don't need to increment
        if (counter) {
            counter->increment();
        }
    }

    SharedPtr& operator=(const SharedPtr& other) {
        // Check for copy assignment to self
        if (this != &other) {
            release();

            obj = other.obj;
            counter = other.counter;

            // Again check if we need to increment
            if (counter) {
                counter->increment();
            }

        }

        return *this;
    }

    ~SharedPtr() {
        release();
    };

    int use_count() const {
        return counter ? counter->get() : 0;
    };
    T& operator*() const {
        assert(obj && "Dereferencing nullptr");
        return *obj;
    };
    T* operator->() const {
        assert(obj && "Accessing member of nullptr");
        return obj;
    };
    T* get() const {
        return obj;
    };

private:
    T* obj;
    RefCounter* counter;

    void release() {
        // If we have a counter to decrement, do so and then check if it is zero then delete and set nullptr if needed
        if (counter) {
            counter->decrement();
            if (counter->get() == 0) {
                delete obj;
                delete counter;
            }
            obj = nullptr;
            counter = nullptr;
        }
    };
};
