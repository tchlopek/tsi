#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base, typename F>
struct map_iterator_traits {
    using iterator_category = typename std::iterator_traits<Base>::iterator_category;
    using reference = typename std::result_of<F(typename Base::reference)>::type;
    using difference_type = typename std::iterator_traits<Base>::difference_type;
    using value_type = typename std::decay<reference>::type;
    using pointer = typename std::add_pointer<reference>::type;
};

}

template<typename BaseIter, typename Func>
class map_iterator : public iterator_facade<
    map_iterator<BaseIter, Func>,
    detail::map_iterator_traits<BaseIter, Func>> {
    using BaseType = iterator_facade<
        map_iterator<BaseIter, Func>,
        detail::map_iterator_traits<BaseIter, Func>>;

public:
    map_iterator(BaseIter begin, Func func) : begin{ begin }, func{ func }
    {}

    bool equal(const map_iterator& other) const {
        return begin == other.begin;
    }

    void increment() {
        ++begin;
    }

    void decrement() {
        --begin;
    }

    typename BaseType::reference dereference() {
        return func(*begin);
    }

    void advance(typename BaseType::difference_type n) {
        begin += n;
    }

    typename BaseType::difference_type distance_to(const map_iterator& other) const {
        return begin - other.begin;
    }

private:
    BaseIter begin;
    Func func;
};

}
