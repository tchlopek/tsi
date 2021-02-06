#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/take_iterator.hpp"

namespace cppiter::range {

template<typename R>
class take_range :
    public range_facade<iter::take_iterator<detail::range_iterator_t<R>>> {
    using BaseRange = range_facade<iter::take_iterator<detail::range_iterator_t<R>>>;

public:
    take_range(
        detail::range_iterator_t<R> begin,
        detail::range_iterator_t<R> end,
        std::size_t n) :
            BaseRange{ { begin, end, n }, { end, end, n } }
    {}
};

}
