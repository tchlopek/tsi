#pragma once

#include "iterator/flatten_iterator.hpp"

#include "range_facade.hpp"

namespace cppiter::range {

template<typename R>
class flatten_range : public range_facade<iter::flatten_iterator<range_iterator_t<R>>> {
    using RngIt = range_iterator_t<R>;
    using FlatIt = iter::flatten_iterator<RngIt>;

public:
    flatten_range(RngIt begin, RngIt end) :
        flatten_range{ begin, end, iter::util::category_t<FlatIt>{} }
    {}

private:
    flatten_range(RngIt begin, RngIt end, std::forward_iterator_tag) :
        range_facade<FlatIt>{
            FlatIt{ begin, end, begin->begin() },
            FlatIt{ end, end, {} }
        }
    {}

    template<typename C>
    flatten_range(RngIt begin, RngIt end, C) :
        range_facade<FlatIt>{
            FlatIt{ begin, end, begin, begin->begin() },
            FlatIt{ begin, end, end, {} }
        }
    {}
};

}
