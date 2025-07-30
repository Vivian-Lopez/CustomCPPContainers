//
// Created by Vivian Lopez on 30/07/2025.
//

#pragma once

#include <iostream>
#include <memory>
#include <mutex>

class Singleton {
public:
    static Singleton& getInstance() {
        std::call_once(m_onceFlag, []{m_Instance = std::make_unique<Singleton>();});
        return *m_Instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

private:
    Singleton() {
        std::cout << "Constructor Called" << std::endl;
    }

    inline static std::unique_ptr<Singleton> m_Instance;
    inline static std::once_flag m_onceFlag;
    inline static int count = 0;
};
