#pragma once

#include "iterator/dereference_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename range_t>
class dereference_range
  : public util::range_facade<dereference_range<range_t>>
  , public util::range_traits<
      iter::dereference_iterator<util::iterator_t<range_t>>,
      iter::dereference_iterator<util::const_iterator_t<range_t>>> {
  friend class util::range_accessor;

public:
  explicit dereference_range(range_t&& range)
    : m_range{ std::move(range) } {
  }

private:
  auto make_begin() {
    return typename dereference_range::iterator{ m_range.begin() };
  }

  auto make_end() {
    return typename dereference_range::iterator{ m_range.end() };
  }

  auto make_const_begin() const {
    return typename dereference_range::const_iterator{ m_range.cbegin() };
  }

  auto make_const_end() const {
    return typename dereference_range::const_iterator{ m_range.cend() };
  }

  range_t m_range;
};

}    // namespace cppiter::rng
