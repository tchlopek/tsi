#pragma once

#include "iterator/filter_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename range_t, typename pred_t>
class filter_range
  : public util::range_facade<filter_range<range_t, pred_t>>
  , public util::range_traits<
      iter::filter_iterator<util::iterator_t<range_t>, filter_range<range_t, pred_t>>,
      iter::filter_iterator<
        util::const_iterator_t<range_t>,
        filter_range<range_t, pred_t>>> {
  friend class util::range_accessor;

  template<typename, typename>
  friend class iter::filter_iterator;

public:
  template<typename predicate>
  filter_range(range_t&& range, predicate&& fn)
    : m_range{ std::move(range) }
    , m_fn{ std::forward<predicate>(fn) } {
  }

private:
  auto make_begin() {
    return typename filter_range::iterator{ m_range.begin(), this };
  }

  auto make_end() {
    return typename filter_range::iterator{ m_range.end(), this };
  }

  auto make_const_begin() const {
    return typename filter_range::const_iterator{ m_range.cbegin(), this };
  }

  auto make_const_end() const {
    return typename filter_range::const_iterator{ m_range.cend(), this };
  }

  range_t m_range;
  pred_t m_fn;
};

}    // namespace cppiter::rng
