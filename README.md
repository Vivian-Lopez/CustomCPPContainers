# 🚀 CustomCPPContainers

**A showcase of hand-crafted C++ containers and utilities, built to deeply understand STL internals, modern C++ standards (C++20), memory management, and performance-critical design.**

> 🎯 **Goal**: Master core system-level design and create clean, modern, and safe C++ implementations.

---

## ✅ Status Dashboard

| Container / Concept           | Status      | Highlights                                                | Modern C++ Features Used                        |
|------------------------------|-------------|------------------------------------------------------------|-------------------------------------------------|
| `unique_ptr` (Smart Pointer) | ✅ Implemented | Ownership, RAII, move semantics                             | `std::move`, `std::exchange`, `concepts`, `explicit` |
| `Vector`                     | ✅ Implemented | Dynamic resizing, capacity management                      | `std::allocator`, `constexpr`, `span`           |
| `shared_ptr / weak_ptr`      | ✅ Implemented | Reference counting, cycle awareness                        | `enable_shared_from_this`, `atomic ops`        |
| `LRU Cache`                  | ⬜ Planned     | Doubly linked list + hash map                              | `unordered_map`, `list`, C++20 `ranges`         |
| `Stack / Queue`              | ⬜ Planned     | Wrapper around custom containers                           | Templates, move support                         |
| `Deque`                      | ⬜ Planned     | Block structure, amortized insert/remove                   | Custom memory pool                              |
| `Memory Pool`                | ⬜ Planned     | Manual memory management for fixed-size allocations        | `aligned_storage`, `placement new`, `concepts`  |
| `Trie`                       | ⬜ Planned     | Prefix tree, memory-efficient string storage               | UTF-8 support, `string_view`                    |
| `Thread-Safe Queue`          | ⬜ Planned     | Mutex + condition_variable + atomic optimization           | `std::mutex`, `std::atomic`, C++20 barriers     |

---

## 🧠 Why I'm Doing This

- 🔍 **Deep understanding**: Go beyond usage and reimplement STL-inspired structures.
- 🚀 **Modern C++ mastery**: Concepts, `constexpr`, allocators, template deduction, etc.
- ❤️ **Passion project**: Because building these from scratch is fun :)

---

## 💡 Future Ideas

- Custom deleters + allocator support
- Lock-free data structures (Michael-Scott queue)
- STL algorithm rewrites (`sort`, `accumulate`) via template metaprogramming
- JSON Parser / Allocator-aware containers

---

## 📚 Tech Stack

- **Compiler**: `g++ 13+` or `clang++ 16+`
- **Standard**: `-std=c++20` with optional backports
- **Tools**: Valgrind, AddressSanitizer, GoogleTest for benchmarking
