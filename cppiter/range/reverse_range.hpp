#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"

namespace cppiter::range {

template<typename R>
class reverse_range :
    public range_facade<std::reverse_iterator<detail::range_iterator_t<R>>> {
    using ReverseIterator = std::reverse_iterator<detail::range_iterator_t<R>>;
    using BaseRange = range_facade<ReverseIterator>;

public:
    explicit reverse_range(R& range) :
        BaseRange {
            ReverseIterator{ std::end(range) },
            ReverseIterator{ std::begin(range) }
        }
    {}
};

template<typename R>
reverse_range<R> reverse(R& range) {
    return reverse_range<R>{ range };
}

template<typename R>
reverse_range<const R> reverse(const R& range) {
    return reverse_range<R>{ range };
}

}
