//
// Created by Vivian Lopez on 12/07/2025.
//

#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H

#include <iostream>
#include <concepts>
#include <utility>

template<typename T, typename Deleter = std::default_delete<T>> // Optional Deleter can be provided
requires std::invocable<Deleter, T*>    // Allows compiler to give a clear error in case deleter is not of the correct type
// (Uses C++20 Concept-based constraint)
class UniquePtr {
private:
    T* ptr;
    Deleter deleter;

public:
    // Constructors
    // Making sure that the Deleter constructor doesn't throw to be extra safe
    // constexpr allows for constructor to be evaluated at compile time -> better performance
    constexpr UniquePtr() noexcept(std::is_nothrow_default_constructible_v<Deleter>) : ptr(nullptr), deleter(Deleter{}) {}
    // explicit prevents conversion of raw pointers to UniquePtr to avoid things like double delete when a caller may think
    // ownership of the pointer hasn't been transferred for example.
    explicit UniquePtr(T* p) noexcept(std::is_nothrow_default_constructible_v<Deleter>) : ptr(p), deleter(Deleter{}) {}

    // Move Constructor
    // std::exchange replace the first arg with the second arg and returns the old value
    UniquePtr(UniquePtr&& other) noexcept   // other is a rvalue not universal reference
        : ptr(std::exchange(other.ptr, nullptr)), deleter(std::move(other.deleter)) {}

    // Move Assignment
    // Return a reference to avoid copy or move
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        // Need the if check so we don't accidentally move from ourselves and lose the object forever
        if (this != other) {
            reset();    // Need to delete the current pointer so we don't leave dangling pointers
            ptr = std::exchange(other.ptr, nullptr);
            deleter = std::move(other.deleter);
        }
        return *this;   // Dereference this to get the object itself
    }

    // Delete copy operations (not allowed with unique pointer)
    // These operations are invalid so the function will never be called so naming the parameters is unnecessary to
    // Copy operations use const parameters because they aren't modified
    UniquePtr(const UniquePtr&) = delete;   // Copy Constructor
    UniquePtr& operator=(const UniquePtr&) = delete;    // Copy Assignment

    // Destructor
    // Cannot have return type or parameters
    ~UniquePtr() {
        reset();
    }

    // Modifiers
    void reset(T* p = nullptr) {
        if (ptr) deleter(ptr);
        ptr = p;
    }

    // Ignoring the result of this function will cause a dangling pointer and lost ownership
    [[nodiscard]] T* release() noexcept {
        return std::exchange(ptr, nullptr);
    }

    // Swap is to exchange two objects with destroying them
    void swap(UniquePtr& other) noexcept {
        std::swap(ptr, other.ptr);
        std::swap(deleter, other.deleter);
    }

    // Observers
    [[nodiscard]] T* get() const noexcept { return ptr; }
    // explicit needed because bool() implicitly converts when UniquePtr used as a bool
    // and we don't want to be able to do things like: int a = UniquePtr(&b) + 1
    [[nodiscard]] explicit operator bool() const noexcept { return ptr != nullptr; }

    T& operator*() const noexcept { return *ptr(); }
    T* operator->() const noexcept { return ptr; }
};

// Custom swap specialization
// Valuable for stl algorithms which need to find a swap to be used effectively, otherwise it might use a slower
// worse implementation than the swap above
template <typename T, typename D>
void swap(UniquePtr<T, D>& lhs, UniquePtr<T, D>& rhs) {
    lhs.swap(rhs);
}


#endif //UNIQUEPTR_H
