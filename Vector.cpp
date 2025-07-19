//
// Created by Vivian Lopez on 19/07/2025.
//

#include "Vector.h"
#include <iostream>

int main() {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);

    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << "\n";
    }

    return 0;
}