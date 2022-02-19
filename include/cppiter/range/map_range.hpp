#pragma once

#include "iterator/map_iterator.hpp"

#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::rng {

template<typename R, typename F>
class map_range : public util::range_facade<iter::map_iterator<util::range_iterator_t<R>, F>> {
    using RngIt = util::range_iterator_t<R>;
    using MapIt = iter::map_iterator<RngIt, F>;

public:
    map_range(RngIt begin, RngIt end, F func) :
        util::range_facade<MapIt>{ MapIt{ begin, func }, MapIt{ end, func } }
    {}
};

}
