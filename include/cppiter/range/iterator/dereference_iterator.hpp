#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename I>
struct dereference_iterator_traits : iterator_traits_facade<
    I,
    category_t<I>,
    std::remove_reference_t<decltype(*std::declval<value_t<I>>())>,
    decltype(*std::declval<value_t<I>>()),
    std::add_pointer_t<std::remove_reference_t<decltype(*std::declval<value_t<I>>())>>>
{};

}

template<typename I>
class dereference_iterator :
    public iterator_facade<dereference_iterator<I>, detail::dereference_iterator_traits<I>> {

    friend class derived_access;

public:
    explicit dereference_iterator(I iter) : iter{ iter }
    {}

private:
    bool equal(const dereference_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
    }

    void decrement() {
        --iter;
    }

    reference_t<detail::dereference_iterator_traits<I>> dereference() const {
        return **iter;
    }

    void advance(difference_t<I> n) {
        iter += n;
    }

    difference_t<I> distance_to(const dereference_iterator& other) const {
        return iter - other.iter;
    }

    I iter;
};

}