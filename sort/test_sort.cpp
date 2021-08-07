#include <gtest/gtest.h>
#include "sort.h"
#include <random>
#include <functional>

constexpr size_t test_size = 100;

template<typename T>
static std::vector<T> generate_some(int min, int max, size_t size = 100) {
    static std::random_device rd;
    static std::default_random_engine e(rd());
    static std::uniform_int_distribution<T> u(min, max);
    std::vector<T> res;
    res.reserve(size);
    std::generate_n(std::back_inserter(res), size, []{return u(e);});
    return res;
}

template<typename T>
static std::vector<T> generate_some(double min, double max, size_t size = 100) {
    static std::random_device rd;
    static std::default_random_engine e(rd());
    static std::uniform_real_distribution<T> u(min, max);
    std::vector<T> res;
    res.reserve(size);
    std::generate_n(std::back_inserter(res), size, []{return u(e);});
    return res;
}

template<typename Iter, typename Pred>
static bool sorted(Iter begin, Iter end, Pred comp) {
    while (begin != end - 1) {
        if (comp(*std::next(begin), *begin)) return false;
        begin++;
    }
    return true;
}

TEST(test_sort, selection_sort) {
    auto vi = generate_some<int>(-1000, 1000, test_size);
    auto vf = generate_some<double>(-1000.f, 1000.f, test_size);
    sort::selection(vi.data(), vi.size(), [](int a, int b){return a < b;});
    EXPECT_EQ(sorted(vi.begin(), vi.end(), [](int a, int b){return a < b;}), true);
    sort::selection(vf.data(), vf.size());
    EXPECT_EQ(sorted(vf.begin(), vf.end(), [](int a, int b){return a < b;}), true);
}

TEST(test_sort, bubble_sort) {
    auto vi = generate_some<int>(-1000, 1000, test_size);
    auto vf = generate_some<double>(-1000.f, 1000.f, test_size);
    sort::bubble(vi.data(), vi.size());
    EXPECT_EQ(sorted(vi.begin(), vi.end(), [](int a, int b){return a < b;}), true);
    sort::bubble(vf.data(), vf.size());
    EXPECT_EQ(sorted(vf.begin(), vf.end(), [](int a, int b){return a < b;}), true);
}

TEST(test_sort, insertion_sort) {
    auto vi = generate_some<int>(-1000, 1000, test_size);
    auto vf = generate_some<double>(-1000.f, 1000.f, test_size);
    sort::insertion(vi.data(), vi.size());
    EXPECT_EQ(sorted(vi.begin(), vi.end(), [](int a, int b){return a < b;}), true);
    sort::insertion(vf.data(), vf.size());
    EXPECT_EQ(sorted(vf.begin(), vf.end(), [](int a, int b){return a < b;}), true);
}

TEST(test_sort, shell_sort) {
    auto vi = generate_some<int>(-1000, 1000, test_size);
    auto vf = generate_some<double>(-1000.f, 1000.f, test_size);
    sort::shell(vi.data(), vi.size());
    EXPECT_EQ(sorted(vi.begin(), vi.end(), [](int a, int b){return a < b;}), true);
    sort::shell(vf.data(), vf.size());
    EXPECT_EQ(sorted(vf.begin(), vf.end(), [](int a, int b){return a < b;}), true);
}

TEST(test_sort, merge_sort) {
    auto vi = generate_some<int>(-1000, 1000, test_size);
    auto vf = generate_some<double>(-1000.f, 1000.f, test_size);
    sort::merge(vi.data(), vi.size());
    EXPECT_EQ(sorted(vi.begin(), vi.end(), [](int a, int b){return a < b;}), true);
    sort::merge(vf.data(), vf.size());
    EXPECT_EQ(sorted(vf.begin(), vf.end(), [](int a, int b){return a < b;}), true);
}

TEST(test_sort, quick_sort) {
    auto vi = generate_some<int>(-1000, 1000, test_size);
    auto vf = generate_some<double>(-1000.f, 1000.f, test_size);
    sort::quick(vi.data(), vi.size());
    EXPECT_EQ(sorted(vi.begin(), vi.end(), [](int a, int b){return a < b;}), true);
    sort::quick(vf.data(), vf.size());
    EXPECT_EQ(sorted(vf.begin(), vf.end(), [](int a, int b){return a < b;}), true);
}

TEST(test_sort, quick3way_sort) {
    auto vi = generate_some<int>(-1000, 1000, test_size);
    auto vf = generate_some<double>(-1000.f, 1000.f, test_size);
    sort::quick3way(vi.data(), vi.size());
    EXPECT_EQ(sorted(vi.begin(), vi.end(), [](int a, int b){return a < b;}), true);
    sort::quick3way(vf.data(), vf.size());
    EXPECT_EQ(sorted(vf.begin(), vf.end(), [](int a, int b){return a < b;}), true);
}