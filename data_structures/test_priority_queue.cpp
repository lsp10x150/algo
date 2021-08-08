#include <gtest/gtest.h>
#include "priority_queue.h"
using namespace data_structures;

TEST(test_priority_queue, MaxPQ) {
    MaxPriorityQueue<int> maxpq(10);
    maxpq.insert(1)
        .insert(2)
        .insert(3)
        .insert(4)
        .insert(5);

    auto min = maxpq.pop();
    std::cerr << min << ' ';
    EXPECT_EQ(min, 5);
    min = maxpq.pop();
    std::cerr << min << ' ';
    EXPECT_EQ(min, 4);
    min = maxpq.pop();
    std::cerr << min << ' ';
    EXPECT_EQ(min, 3);
    min = maxpq.pop();
    std::cerr << min << ' ';
    EXPECT_EQ(min, 2);
    min = maxpq.pop();
    std::cerr << min << ' ';
    EXPECT_EQ(min, 1);
    EXPECT_THROW(maxpq.pop(), std::out_of_range);
}

TEST(test_priority_queue, MinPQ) {
    MinPriorityQueue<int> minpq(10);
    minpq.insert(1)
            .insert(2)
            .insert(3)
            .insert(4)
            .insert(5);

    auto min = minpq.pop();
    std::cerr << min << ' ';
    EXPECT_EQ(min, 1);
    min = minpq.pop();
    std::cerr << min << ' ';
    EXPECT_EQ(min, 2);
    min = minpq.pop();
    std::cerr << min << ' ';
    EXPECT_EQ(min, 3);
    min = minpq.pop();
    std::cerr << min << ' ';
    EXPECT_EQ(min, 4);
    min = minpq.pop();
    std::cerr << min << ' ';
    EXPECT_EQ(min, 5);
    EXPECT_THROW(minpq.pop(), std::out_of_range);
}