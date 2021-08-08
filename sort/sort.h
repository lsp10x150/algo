#ifndef GRAPH_SORTS_H
#define GRAPH_SORTS_H
#include <iostream>
#include <memory>
#include <functional>

namespace sort::detail {
    template<typename T>
    void swap(T* arr, size_t q, size_t p) {
        T temp = arr[q];
        arr[q] = arr[p];
        arr[p] = temp;
    }

    template<typename T>
    void swap(T* q, T* p) {
        T temp = *q;
        *q = *p;
        *p = temp;
    }

    template<typename T>
    bool less(const T& q, const T& p) {
        return q < p;
    }
    template<typename T>
    bool reverse_less(const T& q, const T& p) {
        return less<T>(p, q);
    }

    template<typename T, typename Pred>
    T* extremum(T* begin, T* end, Pred pred) {
        T* min = begin;
        for (;begin != end; begin++)
            if (pred(*begin, *min))
                min = begin;
        return min;
    }
    template<typename T, typename Pred = decltype(detail::less<T>)>
    void merge(T* arr, size_t l, size_t m, size_t h,
               std::unique_ptr<T[]>& aux,
               Pred pred) {
        size_t i = l, j = m+1;
        for (size_t k = l; k <= h; ++k)
            aux[k] = arr[k];
        for (size_t k = l; k <= h; ++k) {
            if      (i > m)                 arr[k] = aux[j++];
            else if (j > h)                 arr[k] = aux[i++];
            else if (pred(aux[j], aux[i]))  arr[k] = aux[j++];
            else                            arr[k] = aux[i++];
        }
    }
    template<typename T, typename Pred = decltype(detail::less<T>)>
    void merge_sort(T* arr, size_t l, size_t h,
                    std::unique_ptr<T[]>& aux,
                    Pred pred) {
        if (h <= l) return;
        size_t m = l + (h - l)/2;
        merge_sort(arr, l, m, aux, pred);
        merge_sort(arr, m+1, h, aux, pred);
        merge(arr, l, m, h, aux, pred);
    }
    template<typename T, typename Pred = decltype(detail::less<T>)>
    size_t partition(T* arr, int l, int h, Pred pred) {
        int i = l, j = h+1;
        T v = arr[l];
        while (true) {
            while (pred(arr[++i], v)) if (i == h) break;
            while (pred(v, arr[--j])) if (j == l) break;
            if (i >= j) break;
            detail::swap(arr, i, j);
        }
        detail::swap(arr, l, j);
        return j;
    }
    template<typename T, typename Pred = decltype(detail::less<T>)>
    void quick_sort(T* arr, int l, int h, Pred pred) {
        if (h <= l) return;
        int j = partition(arr, l, h, pred);
        quick_sort(arr, l, j-1, pred);
        quick_sort(arr, j+1, h, pred);
    }
    template<typename T, typename Pred = decltype(detail::less<T>)>
    void quick_sort_3way(T* arr, int l, int h, Pred pred) {
        if (h <= l) return;
        int lt = l, i = l+1, gt = h; //! @note t - stands for threshold
        T v = arr[l];
        while (i <= gt) {
            if (arr[i] < v) detail::swap(arr, lt++, i++);
            else {
                if (arr[i] != v) detail::swap(arr, i, gt--);
                else i++;
            }
        }
        quick_sort_3way(arr, l, lt - 1, pred);
        quick_sort_3way(arr, gt + 1, h, pred);
    }
}
namespace sort {
    template<typename T, typename Pred = decltype(detail::less<T>)>
    void bubble(T *arr, size_t size,
                Pred pred = detail::less<T>) {
        bool inversion = true;
        while (inversion) {
            for (size_t i = 1; i < size; ++i) {
                inversion = false;
                for (size_t j = 1; j < size; ++j)
                    if (pred(arr[j], arr[j-1])) {
                        detail::swap(arr + j - 1, arr + j);
                        inversion = true;
                    }
            }
        }
    }

    template<typename T, typename Pred = decltype(detail::less<T>)>
    void selection(T *arr, size_t size,
                   Pred pred = detail::less<T>) {
        for (int i = 0; i < size; ++i)
            detail::swap(arr + i, detail::extremum(arr + i, arr + size, pred));
    }

    template<typename T, typename Pred = decltype(detail::less<T>)>
    void insertion(T *arr, size_t size,
                   Pred pred = detail::less<T>) {
        for (size_t i = 1; i < size; ++i)
            for (size_t j = i; j > 0 && pred(arr[j], arr[j-1]); --j)
                detail::swap(arr + j - 1, arr + j);
    }

    template<typename T, typename Pred = decltype(detail::less<T>)>
    void shell(T *arr, size_t size,
               Pred pred = detail::less<T>) {
        size_t step = 1;
        while (3 * step + 1 < size) step = 3 * step + 1;
        while (step >= 1) {
            for (size_t i = step; i < size; i += step)
                for (size_t j = i; j > 0 && pred(arr[j], arr[j - step]); j -= step)
                    detail::swap(arr + j - step, arr + j);
            step /= 3;
        }
    }

    template<typename T, typename Pred = decltype(detail::less<T>)>
    void merge(T *arr, size_t size,
               Pred pred = detail::less<T>) {
        auto aux = std::make_unique<T[]>(size);
        detail::merge_sort(arr, 0, size - 1, aux, pred);
    }

    template<typename T, typename Pred = decltype(detail::less<T>)>
    void quick(T *arr, size_t size,
               Pred pred = detail::less<T>) {
        detail::quick_sort(arr, 0, size - 1, pred);
    }

    template<typename T, typename Pred = decltype(detail::less<T>)>
    void quick3way(T *arr, size_t size,
                   Pred pred = detail::less<T>) {
        detail::quick_sort_3way(arr, 0, size - 1, pred);
    }
}
#endif //GRAPH_SORTS_H
