#pragma once

#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::rng {

template<typename R>
class reverse_range
  : public util::range_facade<std::reverse_iterator<util::range_iterator_t<R>>> {
  using RngIt = util::range_iterator_t<R>;
  using RevIt = std::reverse_iterator<RngIt>;

public:
  reverse_range(RngIt begin, RngIt end)
    : util::range_facade<RevIt>{ RevIt{ end }, RevIt{ begin } } {
  }
};

}    // namespace cppiter::rng
