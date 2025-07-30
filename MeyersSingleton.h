//
// Created by Vivian Lopez on 30/07/2025.
//

#ifndef MEYERSSINGLETON_H
#define MEYERSSINGLETON_H
#include <iostream>
#include <ostream>


class MeyersSingleton {
public:
    static MeyersSingleton* getInstance() {
        static MeyersSingleton instance;
        return &instance;
    }

    static void doSomething() {
        std::cout << "do something called" << std::endl;
    }

    MeyersSingleton(cosnt MeyersSingleton&) = delete;
    MeyersSingleton& operator=(const MeyersSingleton&) = delete;
    MeyersSingleton(MeyersSingleton&&) = delete;
    MeyersSingleton& operator=(MeyersSingleton&&) = delete;
private:
    MeyersSingleton() {
        std::cout << "MeyersSingleton constructor" << std::endl;
    }
};



#endif //MEYERSSINGLETON_H
