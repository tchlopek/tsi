#include <iostream>
#include <vector>
#include <forward_list>
#include <list>
#include "range/filter_range.hpp"

int main() {
    std::forward_list<int> fl1{ 6, 1, 5, 3, 4, 9, 7 };
    std::list<int> l1{ 6, 1, 5, 3, 4, 9, 7 };
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    int a[] = { 7, 56, 4, 32, 11 };
    auto r1 = filter(v1, [](int v){ return v % 2 == 1; });
    for (auto& v : r1) {
        std::cout << v << std::endl;
    }

    return 0;
}