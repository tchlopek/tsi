#pragma once

#include "iterator/unbound_generate_iterator.hpp"
#include "util/range_facade.hpp"

namespace cppiter::rng {

template<typename val_t>
class generate_range
  : public util::range_facade<generate_range<val_t>>
  , public util::range_traits<
      iter::unbound_generate_iterator<val_t>,
      iter::unbound_generate_iterator<val_t>> {
  friend class util::range_accessor;

public:
  explicit generate_range(const val_t& v)
    : m_val{ v } {
  }

  std::size_t size() const = delete;

private:
  auto make_begin() {
    return typename generate_range::iterator{ m_val };
  }

  auto make_end() {
    return typename generate_range::iterator{ m_val };
  }

  auto make_const_begin() const {
    return typename generate_range::const_iterator{ m_val };
  }

  auto make_const_end() const {
    return typename generate_range::const_iterator{ m_val };
  }

  val_t m_val;
};

}    // namespace cppiter::rng
