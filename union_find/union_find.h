#include <memory>
#include <iostream>
#include <numeric>
#include <algorithm>

#ifndef ALGO_UNION_FIND_H
#define ALGO_UNION_FIND_H

struct QuickFind {
private:
    std::unique_ptr<int[]>  id  {nullptr};
    size_t                  N   {0};
public:
    explicit QuickFind(std::istream& is) {
        int i = 0, p = 0, q = 0;
        is >> N;
        const auto initial_size = N;
        id = std::make_unique<int[]>(N);
        std::iota(id.get(), id.get() + N, 0);
        while (is >> p >> q) {
            if (p < 0 || p > initial_size - 1 || q < 0 || q > initial_size - 1)
                throw std::out_of_range("Index provided is out of boundaries");
            if (connected(p, q)) continue;
            Union(p, q);
        }
    }
    [[nodiscard]]
    bool connected(int p, int q) const noexcept {
        return find(p) == find(q);
    }
    [[nodiscard]]
    size_t components() const noexcept {
        return N;
    }
private:
    [[nodiscard]]
    int find(int idx) const {
        return id[idx];
    }
    void Union(int p, int q) {
        int pID = find(p);
        int qID = find(q);
        if (pID == qID) return;
        for (int i = 0; i < N; ++i) {
            if (id[i] == pID)
                id[i] = qID;
        }
        N--;
    }
};

struct QuickUnion {
private:
    std::unique_ptr<int[]>  id  {nullptr};
    size_t                  N   {0};
public:
    explicit QuickUnion(std::istream& is) {
        int i = 0, j = 0, p = 0, q = 0;
        is >> N;
        const auto initial_size = N;
        id = std::make_unique<int[]>(N);
        std::iota(id.get(), id.get() + N, 0);
        while (is >> p >> q) {
            if (p < 0 || p > initial_size - 1 || q < 0 || q > initial_size - 1)
                throw std::out_of_range("Index provided is out of boundaries");
            if (connected(p, q)) continue;
            Union(p, q);
        }
    }
    [[nodiscard]]
    bool connected(int p, int q) const noexcept {
        return find(p) == find(q);
    }
    [[nodiscard]]
    size_t components() const noexcept {
        return N;
    }
private:
    [[nodiscard]]
    int find(int p) const {
        while (p != id[p])
            p = id[p];
        return p;
    }
    void Union(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot)
            return;
        id[pRoot] = qRoot;
        N--;
    }
};

struct WeightedQuickUnion {
private:
    std::unique_ptr<int[]>  id  {nullptr};
    std::unique_ptr<int[]>  sz  {nullptr};
    size_t                  N   {0};
public:
    explicit WeightedQuickUnion(std::istream& is) {
        int i = 0, j = 0, p = 0, q = 0;
        std::cin >> N;
        const auto initial_size = N;
        id = std::make_unique<int[]>(N);
        sz = std::make_unique<int[]>(N);
        std::iota(id.get(), id.get() + N, 0);
        std::fill(sz.get(), sz.get() + N, 1);
        while (is >> p >> q) {
            if (p < 0 || p > initial_size - 1 || q < 0 || q > initial_size - 1)
                throw std::out_of_range("Index provided is out of boundaries");
            if (connected(p, q)) continue;
            Union(p, q);
        }
    }
    [[nodiscard]]
    bool connected(int p, int q) const noexcept {
        return find(p) == find(q);
    }
    [[nodiscard]]
    size_t components() const noexcept {
        return N;
    }
private:
    [[nodiscard]]
    int find(int p) const {
        while (p != id[p])
            p = id[p];
        return p;
    }
    void Union(int p, int q) {
        int i = find(p);
        int j = find(q);
        if (i == j)
            return;
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
        N--;
    }
};
#endif //ALGO_UNION_FIND_H
