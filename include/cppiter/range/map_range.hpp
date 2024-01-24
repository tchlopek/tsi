#pragma once

#include "iterator/map_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename range_t, typename map_fn>
class map_range
  : public util::range_facade<map_range<range_t, map_fn>>
  , public util::range_traits<
      iter::map_iterator<util::iterator_t<range_t>, map_fn>,
      iter::map_iterator<util::const_iterator_t<range_t>, map_fn>> {
  friend class util::range_accessor;

public:
  map_range(range_t&& range, const map_fn& fn)
    : m_range{ std::move(range) }
    , m_fn{ fn } {
  }

  map_range(range_t&& range, map_fn&& fn)
    : m_range{ std::move(range) }
    , m_fn{ std::move(fn) } {
  }

private:
  auto make_begin() {
    return typename map_range::iterator{ m_range.begin(), &m_fn };
  }

  auto make_end() {
    return typename map_range::iterator{ m_range.end(), &m_fn };
  }

  auto make_const_begin() const {
    return typename map_range::const_iterator{ m_range.cbegin(), &m_fn };
  }

  auto make_const_end() const {
    return typename map_range::const_iterator{ m_range.cend(), &m_fn };
  }

  range_t m_range;
  map_fn m_fn;
};

}    // namespace cppiter::rng
