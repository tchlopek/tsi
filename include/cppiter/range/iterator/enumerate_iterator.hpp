#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Iter>
struct enumerate_iterator_traits : iterator_traits_facade<
    Iter,
    std::conditional_t<
        std::is_same_v<category_t<Iter>, std::bidirectional_iterator_tag>,
        std::forward_iterator_tag,
        category_t<Iter>>,
    std::pair<difference_t<Iter>, value_t<Iter>>,
    std::pair<difference_t<Iter>, reference_t<Iter>>,
    std::pair<difference_t<Iter>, pointer_t<Iter>>>
{};

}

template<typename Iter>
class enumerate_iterator :
    public iterator_facade<enumerate_iterator<Iter>, detail::enumerate_iterator_traits<Iter>> {

    friend class iterator_accessor;

public:
    enumerate_iterator(Iter iter, difference_t<Iter> index) : iter{ iter }, index{ index }
    {}

private:
    bool equal(const enumerate_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
        ++index;
    }

    void decrement() {
        --iter;
        --index;
    }

    reference_t<detail::enumerate_iterator_traits<Iter>> dereference() const {
        return { index, std::ref(*iter) };
    }

    void advance(difference_t<Iter> n) {
        iter += n;
        index += n;
    }

    difference_t<Iter> distance_to(const enumerate_iterator& other) const {
        return iter - other.iter;
    }

    Iter iter;
    difference_t<Iter> index;
};

}
