#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Iter>
struct replace_iterator_traits {
    using iterator_category = category_t<Iter>;
    using reference = add_ref_const_t<reference_t<Iter>>;
    using difference_type = difference_t<Iter>;
    using value_type = value_t<Iter>;
    using pointer = add_ref_const_t<pointer_t<Iter>>;
};

}

template<typename Iter, typename Pred>
class replace_iterator :
    public iterator_facade<replace_iterator<Iter, Pred>, detail::replace_iterator_traits<Iter>> {

    friend class derived_access;

public:
    replace_iterator(Iter iter, Pred pred, const value_t<Iter>& newVal) :
        iter{ iter }, newVal{ newVal }, pred{ pred }
    {}

private:
    bool equal(const replace_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
    }

    void decrement() {
        --iter;
    }

    reference_t<detail::replace_iterator_traits<Iter>> dereference() const {
        return pred(*iter) ? newVal : *iter;
    }

    void advance(difference_t<Iter> n) {
        iter += n;
    }

    difference_t<Iter> distance_to(const replace_iterator& other) const {
        return iter - other.iter;
    }

    Iter iter;
    value_t<Iter> newVal;
    Pred pred;
};

}
