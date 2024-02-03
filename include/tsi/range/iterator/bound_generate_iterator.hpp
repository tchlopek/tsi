#pragma once

#include <cstddef>
#include <iterator>

#include "util/iterator_facade.hpp"

namespace tsi::rng::iter {

template<typename val_t>
struct bound_generate_iterator_traits {
  using iterator_category = std::random_access_iterator_tag;
  using value_type = val_t;
  using reference = val_t;
  using pointer = std::add_pointer_t<std::add_const_t<val_t>>;
  using difference_type = std::ptrdiff_t;
};

template<typename val_t>
class bound_generate_iterator
  : public util::iterator_facade<
      bound_generate_iterator<val_t>,
      bound_generate_iterator_traits<val_t>> {
  friend class util::iterator_accessor;

public:
  bound_generate_iterator() = default;
  explicit bound_generate_iterator(const val_t& v)
    : m_val{ v } {
  }

private:
  bool equal(const bound_generate_iterator& other) const {
    return m_val == other.m_val;
  }

  void increment() {
    ++m_val;
  }

  void decrement() {
    --m_val;
  }

  auto dereference() const {
    return m_val;
  }

  void advance(std::ptrdiff_t n) {
    m_val += n;
  }

  std::ptrdiff_t distance_to(const bound_generate_iterator& other) const {
    return m_val - other.m_val;
  }

  bool less(const bound_generate_iterator& other) const {
    return m_val < other.m_val;
  }

  mutable val_t m_val;
};

}    // namespace tsi::rng::iter
