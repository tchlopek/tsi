#pragma once

#include "iterator/take_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename range_t>
class take_range
  : public util::range_facade<take_range<range_t>>
  , public util::range_traits<
      iter::take_iterator<util::iterator_t<range_t>>,
      iter::take_iterator<util::const_iterator_t<range_t>>> {
  friend class util::range_accessor;

  static constexpr bool is_ri = std::is_same_v<
    iter::util::category_t<iter::take_iterator<util::iterator_t<range_t>>>,
    iter::util::ri>;
  static constexpr bool is_ri_const = std::is_same_v<
    iter::util::category_t<iter::take_iterator<util::const_iterator_t<range_t>>>,
    iter::util::ri>;

public:
  take_range(range_t&& range, std::ptrdiff_t n)
    : m_range{ std::move(range) }
    , m_count{ n } {
  }

private:
  template<typename iter_t>
  auto get_end(iter_t&& f, iter_t&& l) const {
    return f + std::min(l - f, m_count);
  }

  auto make_begin() {
    if constexpr (is_ri) {
      return typename take_range::iterator{ m_range.begin() };
    } else {
      return typename take_range::iterator{ m_range.begin(), 0 };
    }
  }

  auto make_end() {
    if constexpr (is_ri) {
      return
        typename take_range::iterator{ get_end(m_range.begin(), m_range.end()) };
    } else {
      return typename take_range::iterator{ m_range.end(), m_count };
    }
  }

  auto make_const_begin() const {
    if constexpr (is_ri_const) {
      return typename take_range::const_iterator{ m_range.begin() };
    } else {
      return typename take_range::const_iterator{ m_range.begin(), 0 };
    }
  }

  auto make_const_end() const {
    if constexpr (is_ri_const) {
      return typename take_range::const_iterator{
        get_end(m_range.cbegin(), m_range.cend())
      };
    } else {
      return typename take_range::const_iterator{ m_range.cend(), m_count };
    }
  }

  range_t m_range;
  std::ptrdiff_t m_count;
};

}    // namespace cppiter::rng
