#pragma once

#include "iterator/take_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::rng {

template<typename R>
class take_range
  : public util::range_facade<iter::take_iterator<util::range_iterator_t<R>>> {
  using RngIt = util::range_iterator_t<R>;
  using TakeIt = iter::take_iterator<RngIt>;
  using Diff = iter::util::difference_t<RngIt>;

public:
  take_range(RngIt begin, RngIt end, Diff n)
    : take_range{ begin, end, n, iter::util::category_t<RngIt>{} } {
  }

private:
  take_range(RngIt begin, RngIt end, Diff n, std::forward_iterator_tag)
    : util::range_facade<TakeIt>{ TakeIt{ begin, 0 }, TakeIt{ end, n } } {
  }

  take_range(RngIt begin, RngIt end, Diff n, std::bidirectional_iterator_tag)
    : util::range_facade<TakeIt>{ TakeIt{ begin, 0 }, TakeIt{ end, n } } {
  }

  take_range(RngIt begin, RngIt end, Diff n, std::random_access_iterator_tag)
    : util::range_facade<TakeIt>{ TakeIt{ begin },
                                  TakeIt{ begin + std::min(end - begin, n) } } {
  }
};

}    // namespace cppiter::rng
