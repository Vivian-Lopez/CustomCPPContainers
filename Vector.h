//
// Created by Vivian Lopez on 19/07/2025.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>    // for std::out_of_range
#include <memory>   // for std::allocator
#include <utility>  // for std::move
#include <format>   // for std::format

template <typename T>
class Vector {
public:
    // Constructors
    Vector() : _data(nullptr), _size(0), _capacity(0) {}

    explicit Vector(size_t capacity) : _data(nullptr), _size(capacity), _capacity(capacity) {
        // Do an initial allocation
        for (size_t i = 0; i < capacity; ++i) {
            _allocator.construct(_data + i);
        }
    }

    // Destructor
    ~Vector() {
        for (size_t i = 0; i < _size; ++i) {
            std::destroy_at(_data + i);
        }
        _allocator.deallocate(_data, _capacity);
    }

    // Copy Constructor
    // Need to declare this, otherwise the complier would generate a default copy constructor which copies the pointers
    // not the data itself which could lead to double freeing.
    Vector(const Vector& other) : _data(_allocator.allocate(other._capacity)), _size(other._size), _capacity(other._capacity) {
        for (size_t i = 0; i < _size; ++i) {
            std::construct_at(_data + i);
        }
    }

    // Move Constructor
    Vector(Vector&& other) noexcept : _data(std::move(other._data)), _size(other._size), _capacity(other._capacity) {
        // Remember to null out other
        other._size = 0;
        other._capacity = 0;
        other._data = nullptr;
    }

    // Copy Assignment
    Vector& operator=(const Vector& other) {
        // Copy and swap idiom used which ensures Strong Exception Safety, avoids resource leaks (auto destructs temp)
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    // Move Assignment
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            clear();    // Destroys all current elements
            _allocator.deallocate(_data, _capacity);    // Frees all current memory

            // std::move not used here due to no performance gain when used on primitives
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;

            other._size = 0;
            other._capacity = 0;
            other._data = nullptr;

        }
        return *this;
    }

    // push_back has 2 overloads for perfect forwarding so it can handle lvalues (copy) and rvalues (move)
    // push_back
    void push_back(const T& value) {
        // Remember to check if we have reached capacity and need to reallocate
        if (_size == _capacity) {
            // Need to check if capacity is zero to avoid doubling zero which would yield a zero capacity
            reallocate(_capacity == 0 ? 1 : _capacity * 2);
        }
        std::construct_at(_data + _size, value);
        // Remember to maintain the size
        ++_size;
    }
    // push_back with rvalue
    void push_back(T&& value) {
        if (_size == _capacity) {
            reallocate(_capacity == 0 ? 1 : _capacity * 2);
        }
        std::construct_at(_data + _size, std::move(value));
        ++_size;
    }

    // pop_back
    void pop_back() {
        if (_size == 0) throw std::out_of_range("pop_back() on empty Vector");
        --_size;
        std::destroy_at(_data + _size);
    }

    // clear
    void clear() {
        for (size_t i = 0; i < _size; ++i) {
            std::destroy_at(_data + i);
        }
        _size = 0;
    }

    // operator[]
    const T& operator[](size_t index) const {
        return _data[index];
    }

    // at
    T& at(size_t index) {
        if (index >= _size) throw std::out_of_range(
            std::format("Vector::at() called with index: {}, greater than or equal to size: {}", index, _size)
        );
        return _data[index];
    }

    // cont at ?
    // Needed so that we can do read only access
    const T& at(size_t index) const {
        if (index >= _size) throw std::out_of_range(
            std::format("Vector::at() called with index: {}, greater than or equal to size: {}", index, _size)
        );
        return _data[index];
    }

    // size
    size_t size() const noexcept {
        return _size;
    }

    // capacity
    // Can't use constexpr here because the _capacity depends on the runtime state of the object!
    // Const is used here because it doesn't modify anything
    size_t capacity() const noexcept {
        return _capacity;
    }

    // empty
    bool empty() const noexcept {
        return _size == 0;
    }

    // swap
    void swap(Vector& other) {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

private:
    T* _data;
    size_t _size;
    size_t _capacity;
    std::allocator<T> _allocator;

    void reallocate(size_t new_capacity) {
        T* new_data = _allocator.allocate(new_capacity);
        for (size_t i = 0; i < _size; ++i) {
            std::construct_at(new_data + i, std::move(_data[i]));
        }
        _allocator.deallocate(_data, _capacity);
        _data = new_data;
        _capacity = new_capacity;
    }
};


#endif //VECTOR_H
