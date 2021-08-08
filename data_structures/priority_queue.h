#ifndef ALGO_PRIORITY_QUEUE_H
#define ALGO_PRIORITY_QUEUE_H
#include <limits>
#include <type_traits>

namespace data_structures {
    template<typename T, bool Min>
    struct CompPolicy;

    template<typename T>
    struct CompPolicy<T, false> {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
        static inline const T reverse_extremum = std::numeric_limits<T>::lowest();

        bool comp(const T &lhs, const T &rhs) const {
            return lhs < rhs;
        }
    };

    template<typename T>
    struct CompPolicy<T, true> {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
        static inline const T reverse_extremum = std::numeric_limits<T>::max();

        bool comp(const T &lhs, const T &rhs) const {
            return rhs < lhs;
        }
    };

    template<typename T, bool Min = false>
    struct PriorityQueue : CompPolicy<T, Min> {
    private:
        std::unique_ptr<T[]> pq_{};
        size_t size_, capacity_;

        void swim(size_t k) {
            while (k > 1 && this->comp(pq_[k / 2], pq_[k])) {
                exch(k, k / 2);
                k /= 2;
            }
        }

        void sink(size_t k) {
            while (2 * k <= size_) {
                int j = 2 * k;
                if (j < size_ && this->comp(pq_[j], pq_[j + 1])) j++;    // choose larger child
                if (!(this->comp(pq_[k], pq_[j]))) break;              // everything's fine = do nothing
                exch(k,
                     j);                                            // exchange parent with larger child (sink parent)
                k = j;                                                 // repeat for new position
            }
        }

        void exch(int i, int j) {
            T temp = pq_[i];
            pq_[i] = pq_[j];
            pq_[j] = temp;
        }

    public:
        explicit PriorityQueue(size_t capacity)
                : pq_{new T[capacity]},
                  size_(0),
                  capacity_(capacity) {
            for (int i = 0; i < capacity_; i++)
                pq_[i] = T{this->reverse_extremum};
        }

        PriorityQueue<T, Min> &
        insert(T a) {
            pq_[++size_] = a;
            swim(size_);
            return *this;
        }

        const T &peek() const {
            auto extr = 0;
            for (int i = 1; i < size_; i++) {
                if (this->comp(pq_[extr], pq_[i])) extr = i;
            }
            return pq_[extr];
        }

        T pop() {
            if (empty()) throw std::out_of_range("queue is empty");
            T max = pq_[1];
            exch(1, size_--);
            pq_[size_ + 1] = this->reverse_extremum;
            sink(1);
            return max;
        }

        [[nodiscard]]
        bool empty() const {
            return size_ == 0;
        }

        [[nodiscard]]
        size_t size() const {
            return size_;
        }

        [[nodiscard]]
        size_t capacity() const {
            return capacity_;
        }
    };

    template<typename T>
    using MinPriorityQueue = PriorityQueue<T, true>;
    template<typename T>
    using MaxPriorityQueue = PriorityQueue<T, false>;
}
#endif //ALGO_PRIORITY_QUEUE_H
