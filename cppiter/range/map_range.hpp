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
    map_range(R& range, F func) :
        BaseRange { { std::begin(range), func }, { std::end(range), func } }
    {}
};

template<typename R, typename F>
map_range<R, F> map(R& range, F func) {
    return { range, func };
}

template<typename R, typename F>
map_range<const R, F> map(const R& range, F func) {
    return { range, func };
}

}
