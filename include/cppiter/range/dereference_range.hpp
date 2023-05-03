#pragma once

#include "iterator/dereference_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::rng {

template<typename R>
class dereference_range
  : public util::range_facade<
      iter::dereference_iterator<util::range_iterator_t<R>>> {
  using RngIt = util::range_iterator_t<R>;
  using DerefIt = iter::dereference_iterator<RngIt>;

public:
  dereference_range(RngIt begin, RngIt end)
    : util::range_facade<DerefIt>{ DerefIt{ begin }, DerefIt{ end } } {
  }
};

}    // namespace cppiter::rng
