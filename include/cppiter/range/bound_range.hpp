#pragma once

#include "iterator/bound_generate_iterator.hpp"
#include "util/range_facade.hpp"
#include "util/range_traits.hpp"

namespace cppiter::rng {

template<typename val_t>
class bound_range
  : public util::range_facade<bound_range<val_t>>
  , public util::range_traits<
      iter::bound_generate_iterator<val_t>,
      iter::bound_generate_iterator<val_t>> {
  friend class util::range_accessor;

public:
  bound_range(const val_t& first, const val_t& last)
    : m_first{ first }
    , m_last{ last } {
  }

private:
  auto make_begin() {
    return typename bound_range::iterator{ m_first };
  }

  auto make_end() {
    return typename bound_range::iterator{ m_last };
  }

  auto make_const_begin() const {
    return typename bound_range::const_iterator{ m_first };
  }

  auto make_const_end() const {
    return typename bound_range::const_iterator{ m_last };
  }

  val_t m_first;
  val_t m_last;
};

}    // namespace cppiter::rng
