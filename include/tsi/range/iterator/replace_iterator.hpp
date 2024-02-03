#pragma once

#include <type_traits>

#include "util/iterator_facade.hpp"

namespace tsi::rng::iter {

template<typename iter_t>
struct replace_iterator_traits : public std::iterator_traits<iter_t> {
  using reference = std::add_lvalue_reference_t<
    std::add_const_t<util::value_t<iter_t>>>;
  using pointer = std::add_pointer_t<reference>;
};

template<typename iter_t, typename range_t>
class replace_iterator
  : public util::iterator_facade<
      replace_iterator<iter_t, range_t>,
      replace_iterator_traits<iter_t>> {
  friend class util::iterator_accessor;

public:
  replace_iterator() = default;
  replace_iterator(const iter_t& it, range_t* range)
    : m_it{ it }
    , m_range{ range } {
  }

private:
  bool equal(const replace_iterator& other) const {
    return m_it == other.m_it;
  }

  void increment() {
    ++m_it;
  }

  void decrement() {
    --m_it;
  }

  util::reference_t<replace_iterator_traits<iter_t>> dereference() const {
    return m_range->m_pred(*m_it) ? m_range->m_val : *m_it;
  }

  template<typename diff_t>
  void advance(diff_t n) {
    m_it += n;
  }

  auto distance_to(const replace_iterator& other) const {
    return m_it - other.m_it;
  }

  bool less(const replace_iterator& other) const {
    return m_it < other.m_it;
  }

  iter_t m_it;
  range_t* m_range = nullptr;
};

}    // namespace tsi::rng::iter
