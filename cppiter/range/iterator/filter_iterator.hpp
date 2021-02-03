#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

template<typename BaseIter, typename Pred>
class filter_iterator : public iterator_facade<filter_iterator<BaseIter, Pred>> {
    using BaseType = iterator_facade<filter_iterator<BaseIter, Pred>>;

public:
    filter_iterator(BaseIter begin, BaseIter end, Pred pred) :
        begin{ begin }, end{ end }, predicate{ pred }
    {
        align_position();
    }

    bool equal(const filter_iterator& other) const {
        return begin == other.begin;
    }

    void increment() {
        ++begin;
        align_position();
    }

    void decrement() {
        do {
            --begin;
        } while (!predicate(dereference()));
    }

    typename BaseType::reference dereference() {
        return *begin;
    }

    typename BaseType::difference_type distance_to(const filter_iterator& other) const {
        auto tmp = *this;
        const auto sz = std::distance(tmp.begin, other.begin);
        typename BaseType::difference_type distance = 0;
        if (sz > 0) {
            while (tmp.begin != other.begin) {
                tmp.increment();
                --distance;
            }
        } else if (sz < 0) {
            while (tmp.begin != other.begin) {
                tmp.decrement();
                ++distance;
            }
        }
        return distance;
    }

private:
    void align_position() {
        while (begin != end && !predicate(dereference()))
            ++begin;
        }

    BaseIter begin;
    BaseIter end;
    Pred predicate;
};

}
