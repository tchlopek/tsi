#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"

#include "iterator/enumerate_iterator.hpp"

namespace cppiter::range {

template<typename R>
class enumerate_range :
    public range_facade<iter::enumerate_iterator<range_iterator_t<R>>> {
    using BaseRange = range_facade<iter::enumerate_iterator<range_iterator_t<R>>>;

public:
    enumerate_range(
        range_iterator_t<R> begin,
        range_iterator_t<R> end,
        typename BaseRange::difference_type index) :
            BaseRange{ { begin, index }, { end, index } }
    {}
};

}
