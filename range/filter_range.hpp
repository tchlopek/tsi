#pragma once

#include "range_facade.hpp"
#include "range_traits.hpp"

#include "iterator/filter_iterator.hpp"

template<typename R, typename P>
class filter_range : public range_facade<filter_iterator<typename range_traits<R>::iterator, P>> {
    using BaseRange = range_facade<filter_iterator<typename range_traits<R>::iterator, P>>;

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