#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"

namespace cppiter::range {

template<typename R>
class reverse_range : public range_facade<std::reverse_iterator<range_iterator_t<R>>> {
    using RngIt = range_iterator_t<R>;
    using RevIt = std::reverse_iterator<RngIt>;

public:
    reverse_range(RngIt begin, RngIt end) :
        range_facade<RevIt>{ RevIt{ end }, RevIt{ begin } }
    {}
};

}
