#pragma once

#include <iterator>

#include "util/iterator_facade.hpp"

namespace tsi::rng::iter {

template<typename val_t>
struct unbound_generate_iterator_traits {
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = val_t;
  using reference = val_t;
  using pointer = std::add_pointer_t<std::add_const_t<val_t>>;
  using difference_type = std::ptrdiff_t;
};

template<typename val_t>
class unbound_generate_iterator
  : public util::iterator_facade<
      unbound_generate_iterator<val_t>,
      unbound_generate_iterator_traits<val_t>> {
  friend class util::iterator_accessor;

public:
  unbound_generate_iterator() = default;
  explicit unbound_generate_iterator(const val_t& v)
    : m_val{ v } {
  }

private:
  bool equal(const unbound_generate_iterator&) const {
    return false;
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

  val_t m_val;
};

}    // namespace tsi::rng::iter
