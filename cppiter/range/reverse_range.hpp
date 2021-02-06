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
    reverse_range(detail::range_iterator_t<R> begin, detail::range_iterator_t<R> end) :
        BaseRange{ ReverseIterator{ end }, ReverseIterator{ begin } }
    {}
};

}
