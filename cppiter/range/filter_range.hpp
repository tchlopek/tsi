#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"

#include "iterator/filter_iterator.hpp"

namespace cppiter::range {

template<typename R, typename P>
class filter_range :
    public range_facade<iter::filter_iterator<range_iterator_t<R>, P>> {
    using BaseRange = range_facade<iter::filter_iterator<range_iterator_t<R>, P>>;

public:
    filter_range(range_iterator_t<R> begin, range_iterator_t<R> end, P pred) :
        BaseRange{ { begin, end, pred }, { end, end, pred } }
    {}
};

}
