#pragma once

#include "iterator/flatten_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::rng {

template<typename R>
class flatten_range
  : public util::range_facade<iter::flatten_iterator<util::range_iterator_t<R>>> {
  using RngIt = util::range_iterator_t<R>;
  using FlatIt = iter::flatten_iterator<RngIt>;

public:
  flatten_range(RngIt begin, RngIt end)
    : flatten_range{ begin, end, iter::util::category_t<FlatIt>{} } {
  }

private:
  flatten_range(RngIt begin, RngIt end, std::forward_iterator_tag)
    : util::range_facade<FlatIt>{ FlatIt{ begin, end, begin->begin() },
                                  FlatIt{ end, end, {} } } {
  }

  template<typename C>
  flatten_range(RngIt begin, RngIt end, C)
    : util::range_facade<FlatIt>{ FlatIt{ begin, end, begin, begin->begin() },
                                  FlatIt{ begin, end, end, {} } } {
  }
};

}    // namespace cppiter::rng
