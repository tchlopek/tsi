#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base, typename F>
struct map_iterator_traits {
    using iterator_category = typename std::iterator_traits<Base>::iterator_category;
    using reference = std::invoke_result_t<F, typename Base::reference>;
    using difference_type = typename std::iterator_traits<Base>::difference_type;
    using value_type = std::decay_t<reference>;
    using pointer = std::add_pointer_t<reference>;
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
    map_iterator(BaseIter iter, Func func) : iter{ iter }, func{ func }
    {}

    bool equal(const map_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
    }

    void decrement() {
        --iter;
    }

    typename BaseType::reference dereference() {
        return func(*iter);
    }

    void advance(typename BaseType::difference_type n) {
        iter += n;
    }

    typename BaseType::difference_type distance_to(const map_iterator& other) const {
        return iter - other.iter;
    }

private:
    BaseIter iter;
    Func func;
};

}
