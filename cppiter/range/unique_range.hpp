#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/unique_iterator.hpp"

namespace cppiter::range {

template<typename R>
class unique_range :
    public range_facade<iter::unique_iterator<detail::range_iterator_t<R>>> {
    using BaseRange = range_facade<iter::unique_iterator<detail::range_iterator_t<R>>>;

public:
    unique_range(detail::range_iterator_t<R> begin, detail::range_iterator_t<R> end) :
        BaseRange{ { begin, end }, { end, end } }
    {}
};

}
