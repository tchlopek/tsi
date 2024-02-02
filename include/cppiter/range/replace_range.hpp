#pragma once

#include "iterator/replace_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename range_t, typename pred_t>
class replace_range
  : public util::range_facade<replace_range<range_t, pred_t>>
  , public util::range_traits<
      iter::replace_iterator<
        util::iterator_t<range_t>,
        replace_range<range_t, pred_t>>,
      iter::replace_iterator<
        util::const_iterator_t<range_t>,
        const replace_range<range_t, pred_t>>> {
  friend class util::range_accessor;

  template<typename, typename>
  friend class iter::replace_iterator;

public:
  template<typename predicate, typename value>
  replace_range(range_t&& range, predicate&& pred, value&& val)
    : m_range{ std::move(range) }
    , m_pred{ std::forward<predicate>(pred) }
    , m_val{ std::forward<value>(val) } {
  }

private:
  auto make_begin() {
    return typename replace_range::iterator{ m_range.begin(), this };
  }

  auto make_end() {
    return typename replace_range::iterator{ m_range.end(), this };
  }

  auto make_const_begin() const {
    return typename replace_range::const_iterator{ m_range.cbegin(), this };
  }

  auto make_const_end() const {
    return typename replace_range::const_iterator{ m_range.cend(), this };
  }

  range_t m_range;
  pred_t m_pred;
  typename range_t::value_type m_val;
};

}    // namespace cppiter::rng
