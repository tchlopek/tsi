#pragma once

#include "range_facade.hpp"

#include "iterator/enumerate_iterator.hpp"

namespace cppiter::range {

template<typename R>
class enumerate_range : public range_facade<iter::enumerate_iterator<range_iterator_t<R>>> {
    using RngIt = range_iterator_t<R>;
    using EnumIt = iter::enumerate_iterator<RngIt>;

public:
    enumerate_range(RngIt begin, RngIt end, typename R::difference_type index) :
        range_facade<EnumIt>{ EnumIt{ begin, index }, EnumIt{ end, index } }
    {}
};

}
