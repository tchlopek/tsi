#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"

#include "iterator/filter_iterator.hpp"

namespace cppiter::range {

template<typename R, typename P>
class filter_range :
    public range_facade<iter::filter_iterator<detail::range_iterator_t<R>, P>> {
    using BaseRange = range_facade<iter::filter_iterator<detail::range_iterator_t<R>, P>>;

public:
    filter_range(R& range, P pred) :
        BaseRange { 
            { std::begin(range), std::end(range), pred },
            { std::end(range), std::end(range), pred }
        }
    {}
};

template<typename R, typename P>
filter_range<R, P> filter(R& range, P pred) {
    return { range, pred };
}

template<typename R, typename P>
filter_range<const R, P> filter(const R& range, P pred) {
    return { range, pred };
}

}
