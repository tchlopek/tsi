#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/unique_iterator.hpp"

namespace cppiter::range {

template<typename R>
class unique_range : public range_facade<iter::unique_iterator<range_iterator_t<R>>> {
    using UniqueIt = iter::unique_iterator<range_iterator_t<R>>;

public:
    unique_range(range_iterator_t<R> begin, range_iterator_t<R> end) :
        range_facade<UniqueIt>{ UniqueIt{ begin, end }, UniqueIt{ end, end } }
    {}
};

}