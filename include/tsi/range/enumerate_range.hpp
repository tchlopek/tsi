#pragma once

#include "iterator/enumerate_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace tsi::rng {

template<typename range_t>
class enumerate_range
  : public util::range_facade<enumerate_range<range_t>>
  , public util::range_traits<
      iter::enumerate_iterator<util::iterator_t<range_t>>,
      iter::enumerate_iterator<util::const_iterator_t<range_t>>> {
  friend class util::range_accessor;

public:
  enumerate_range(range_t&& range, std::ptrdiff_t index)
    : m_range{ std::move(range) }
    , m_index{ index } {
  }

private:
  auto make_begin() {
    return typename enumerate_range::iterator{ m_range.begin(), m_index };
  }

  auto make_end() {
    return typename enumerate_range::iterator{ m_range.end(), m_index };
  }

  auto make_const_begin() const {
    return
      typename enumerate_range::const_iterator{ m_range.cbegin(), m_index };
  }

  auto make_const_end() const {
    return typename enumerate_range::const_iterator{ m_range.cend(), m_index };
  }

  range_t m_range;
  std::ptrdiff_t m_index;
};

}    // namespace tsi::rng
