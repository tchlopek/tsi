#pragma once

#include "range_facade.hpp"

#include "iterator/dereference_iterator.hpp"

namespace cppiter::range {

template<typename R>
class dereference_range : public range_facade<iter::dereference_iterator<range_iterator_t<R>>> {
    using RngIt = range_iterator_t<R>;
    using DerefIt = iter::dereference_iterator<RngIt>;

public:
    dereference_range(RngIt begin, RngIt end) :
        range_facade<DerefIt>{ DerefIt{ begin }, DerefIt{ end } }
    {}
};

}
