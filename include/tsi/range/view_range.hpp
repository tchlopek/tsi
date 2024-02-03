#pragma once

#include "iterator/step_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace tsi::rng {

template<typename iter_t>
class view_range
  : public util::range_facade<view_range<iter_t>>
  , public util::range_traits<iter_t, iter_t> {
  friend class util::range_accessor;

public:
  view_range(iter_t&& first, iter_t&& last)
    : m_first{ std::move(first) }
    , m_last{ std::move(last) } {
  }

private:
  auto make_begin() {
    return m_first;
  }

  auto make_end() {
    return m_last;
  }

  auto make_const_begin() const {
    return m_first;
  }

  auto make_const_end() const {
    return m_last;
  }

private:
  iter_t m_first;
  iter_t m_last;
};

}    // namespace tsi::rng
