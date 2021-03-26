#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base, typename F>
struct map_iterator_traits {
    using iterator_category = category_t<Base>;
    using reference = std::invoke_result_t<F, reference_t<Base>>;
    using difference_type = difference_t<Base>;
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

    friend class derived_access;

public:
    map_iterator(BaseIter iter, Func func) : iter{ iter }, func{ func }
    {}

private:
    bool equal(const map_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
    }

    void decrement() {
        --iter;
    }

    typename BaseType::reference dereference() const {
        return func(*iter);
    }

    void advance(typename BaseType::difference_type n) {
        iter += n;
    }

    typename BaseType::difference_type distance_to(const map_iterator& other) const {
        return iter - other.iter;
    }

    BaseIter iter;
    Func func;
};

}
