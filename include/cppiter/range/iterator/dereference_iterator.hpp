#pragma once

#include <iterator>

#include "util/iterator_facade.hpp"
#include "util/iterator_traits.hpp"

namespace cppiter::rng::iter {

template<typename iter_t>
struct dereference_iterator_traits : public std::iterator_traits<iter_t> {
  using reference = decltype(*std::declval<util::reference_t<iter_t>>());
  using value_type = std::remove_cv_t<std::remove_reference_t<reference>>;
  using pointer = std::add_pointer_t<reference>;
};

template<typename iter_t>
class dereference_iterator
  : public util::iterator_facade<
      dereference_iterator<iter_t>,
      dereference_iterator_traits<iter_t>> {
  friend class util::iterator_accessor;

public:
  dereference_iterator() = default;
  explicit dereference_iterator(const iter_t& it)
    : m_it{ it } {
  }

private:
  bool equal(const dereference_iterator& other) const {
    return m_it == other.m_it;
  }

  void increment() {
    ++m_it;
  }

  void decrement() {
    --m_it;
  }

  decltype(auto) dereference() const {
    return **m_it;
  }

  template<typename diff_t>
  void advance(diff_t n) {
    m_it += n;
  }

  auto distance_to(const dereference_iterator& other) const {
    return m_it - other.m_it;
  }

  bool less(const dereference_iterator& other) const {
    return m_it < other.m_it;
  }

  iter_t m_it;
};

}    // namespace cppiter::rng::iter
