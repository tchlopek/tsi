#pragma once

#include "range_facade.hpp"
#include "range_traits.hpp"

template<typename R>
class reverse_range : public range_facade<std::reverse_iterator<typename range_traits<R>::iterator>> {
    using ReverseIterator = std::reverse_iterator<typename range_traits<R>::iterator>;
    using BaseRange = range_facade<ReverseIterator>;

public:
    reverse_range(R& range) :
        BaseRange {
            ReverseIterator{ std::end(range) },
            ReverseIterator{ std::begin(range) }
        }
    {}
};

template<typename R>
reverse_range<R> reverse(R& range) {
    return { range };
}

template<typename R>
reverse_range<const R> reverse(const R& range) {
    return { range };
}