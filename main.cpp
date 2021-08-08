#include <iostream>
#include <vector>
#include "sort/sort.h"

int main() {
    std::vector<int> vn {10, 11, 12, 13, 14, 15,16 ,7, 7, 19, 20, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    sort::quick3way(vn.data(), vn.size());
    for (auto i : vn) std::cout << i << ' ';
    std::cout << '\n';
}
