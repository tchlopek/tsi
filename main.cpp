#include <iostream>
#include <vector>
#include "range/filter_range.hpp"

int main() {
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    int a[] = { 7, 56, 4, 32, 11 };
    auto r1 = filter(a, [](int v){ return v % 2 == 1; });

    for (auto& v : r1) {
        std::cout << v << std::endl;
    }

    return 0;
}