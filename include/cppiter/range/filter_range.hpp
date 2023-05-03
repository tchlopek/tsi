#pragma once

#include "iterator/filter_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::rng {

template<typename R, typename P>
class filter_range
  : public util::range_facade<iter::filter_iterator<util::range_iterator_t<R>, P>> {
  using RngIt = util::range_iterator_t<R>;
  using FilterIt = iter::filter_iterator<RngIt, P>;

public:
  filter_range(RngIt begin, RngIt end, P pred)
    : filter_range{ begin, end, pred, iter::util::category_t<RngIt>{} } {
  }

private:
  filter_range(RngIt begin, RngIt end, P pred, std::forward_iterator_tag)
    : util::range_facade<FilterIt>{ FilterIt{ begin, end, pred },
                                    FilterIt{ end, end, pred } } {
  }

  template<typename Cat>
  filter_range(RngIt begin, RngIt end, P pred, Cat)
    : util::range_facade<FilterIt>{
      FilterIt{ begin, std::pair{ begin, end }, pred },
      FilterIt{ end, std::pair{ begin, end }, pred }
    } {
  }
};

}    // namespace cppiter::rng
