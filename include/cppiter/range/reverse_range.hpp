#pragma once

#include <iterator>

#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename range_t>
class reverse_range
  : public util::range_facade<reverse_range<range_t>>
  , public util::range_traits<
      std::reverse_iterator<util::iterator_t<range_t>>,
      std::reverse_iterator<util::const_iterator_t<range_t>>> {
  friend class util::range_accessor;

public:
  explicit reverse_range(range_t&& range)
    : m_range{ std::move(range) } {
  }

private:
  auto make_begin() {
    return typename reverse_range::iterator{ m_range.end() };
  }

  auto make_end() {
    return typename reverse_range::iterator{ m_range.begin() };
  }

  auto make_const_begin() const {
    return typename reverse_range::const_iterator{ m_range.cend() };
  }

  auto make_const_end() const {
    return typename reverse_range::const_iterator{ m_range.cbegin() };
  }

  range_t m_range;
};

}    // namespace cppiter::rng
