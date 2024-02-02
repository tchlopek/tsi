#pragma once

#include "iterator/step_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename range_t>
class step_range
  : public util::range_facade<step_range<range_t>>
  , public util::range_traits<
      iter::step_iterator<util::iterator_t<range_t>, step_range<range_t>>,
      iter::
        step_iterator<util::const_iterator_t<range_t>, const step_range<range_t>>> {
  friend class util::range_accessor;

  template<typename, typename, typename>
  friend class iter::detail::step_iterator_impl;

public:
  step_range(range_t&& range, std::ptrdiff_t n)
    : m_range{ std::move(range) }
    , m_step{ n } {
  }

private:
  auto make_begin() {
    return typename step_range::iterator{ m_range.begin(), this };
  }

  auto make_end() {
    return typename step_range::iterator{ m_range.end(), this };
  }

  auto make_const_begin() const {
    return typename step_range::const_iterator{ m_range.cbegin(), this };
  }

  auto make_const_end() const {
    return typename step_range::const_iterator{ m_range.cend(), this };
  }

private:
  range_t m_range;
  std::ptrdiff_t m_step;
};

}    // namespace cppiter::rng
