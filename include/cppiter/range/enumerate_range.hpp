#pragma once

#include "iterator/enumerate_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::rng {

template<typename R>
class enumerate_range
  : public util::range_facade<iter::enumerate_iterator<util::range_iterator_t<R>>> {
  using RngIt = util::range_iterator_t<R>;
  using EnumIt = iter::enumerate_iterator<RngIt>;

public:
  enumerate_range(RngIt begin, RngIt end, typename R::difference_type index)
    : util::range_facade<EnumIt>{ EnumIt{ begin, index },
                                  EnumIt{ end, index } } {
  }
};

}    // namespace cppiter::rng
