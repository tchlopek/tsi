#pragma once

#include "iterator/unique_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename range_t>
class unique_range
  : public util::range_facade<unique_range<range_t>>
  , public util::range_traits<
      iter::unique_iterator<util::iterator_t<range_t>, unique_range<range_t>>,
      iter::unique_iterator<
        util::const_iterator_t<range_t>,
        const unique_range<range_t>>> {
  friend class util::range_accessor;

  template<typename, typename>
  friend class iter::unique_iterator;

public:
  explicit unique_range(range_t&& range)
    : m_range{ std::move(range) } {
  }

private:
  auto make_begin() {
    return typename unique_range::iterator{ m_range.begin(), this };
  }

  auto make_end() {
    return typename unique_range::iterator{ m_range.end(), this };
  }

  auto make_const_begin() const {
    return typename unique_range::const_iterator{ m_range.cbegin(), this };
  }

  auto make_const_end() const {
    return typename unique_range::const_iterator{ m_range.cend(), this };
  }

  range_t m_range;
};

}    // namespace cppiter::rng
