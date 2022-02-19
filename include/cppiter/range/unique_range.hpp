#pragma once

#include "iterator/unique_iterator.hpp"

#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::rng {

template<typename R>
class unique_range : public util::range_facade<iter::unique_iterator<util::range_iterator_t<R>>> {
    using UniqueIt = iter::unique_iterator<util::range_iterator_t<R>>;

public:
    unique_range(util::range_iterator_t<R> begin, util::range_iterator_t<R> end) :
        util::range_facade<UniqueIt>{ UniqueIt{ begin, end }, UniqueIt{ end, end } }
    {}
};

}
