#include "util.h"
#include <iostream>

void printVec(vector<int> v) {
    for (int num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void printVecVec(vector<vector<int>> v) {
    for (auto x: v) {
        printVec(x);
    }
    std::cout << std::endl;
}

