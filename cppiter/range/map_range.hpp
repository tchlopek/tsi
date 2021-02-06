#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/map_iterator.hpp"

namespace cppiter::range {

template<typename R, typename F>
class map_range :
    public range_facade<iter::map_iterator<detail::range_iterator_t<R>, F>> {
    using BaseRange = range_facade<iter::map_iterator<detail::range_iterator_t<R>, F>>;

public:
    map_range(detail::range_iterator_t<R> begin, detail::range_iterator_t<R> end, F func) :
        BaseRange{ { begin, func }, { end, func } }
    {}
};

}
