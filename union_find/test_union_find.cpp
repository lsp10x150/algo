//
// Created by lsp10 on 8/7/21.
//
#include <sstream>
#include <string_view>
#include <gtest/gtest.h>
#include "union_find.h"

constexpr std::string_view test_str =
R"(10
4 3
3 8
6 5
9 4
2 1
8 9
5 0
7 2
6 1
1 0
6 7)";

TEST(test_union_find, quick_find) {
    std::stringstream ss(test_str.data());
    QuickFind qf(ss);
    EXPECT_EQ(qf.connected(3, 9), true);
}

TEST(test_union_find, quick_union) {
    std::stringstream ss(test_str.data());
    QuickUnion qu(ss);
    EXPECT_EQ(qu.connected(3, 9), true);
}

TEST(test_union_find, weighted_quick_union) {
    std::stringstream ss(test_str.data());
    WeightedQuickUnion wqu(ss);
    EXPECT_EQ(wqu.connected(3, 9), true);
}
