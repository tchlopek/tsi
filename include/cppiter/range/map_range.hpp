#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/map_iterator.hpp"

namespace cppiter::range {

template<typename R, typename F>
class map_range : public range_facade<iter::map_iterator<range_iterator_t<R>, F>> {
    using RngIt = range_iterator_t<R>;
    using MapIt = iter::map_iterator<RngIt, F>;

public:
    map_range(RngIt begin, RngIt end, F func) :
        range_facade<MapIt>{ MapIt{ begin, func }, MapIt{ end, func } }
    {}
};

}
