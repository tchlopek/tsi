#pragma once

#include <type_traits>

#include "util/iterator_facade.hpp"

namespace tsi::rng::iter {

template<typename iter_t, typename map_fn>
struct map_iterator_traits : public std::iterator_traits<iter_t> {
  using reference = std::invoke_result_t<map_fn, typename iter_t::reference>;
  using value_type = std::decay_t<reference>;
  using pointer = std::add_pointer_t<reference>;
};

template<typename iter_t, typename map_fn>
class map_iterator
  : public util::iterator_facade<
      map_iterator<iter_t, map_fn>,
      map_iterator_traits<iter_t, map_fn>> {
  friend class util::iterator_accessor;

public:
  map_iterator() = default;
  map_iterator(const iter_t& it, const map_fn* fn)
    : m_it{ it }
    , m_fn{ fn } {
  }

private:
  bool equal(const map_iterator& other) const {
    return m_it == other.m_it;
  }

  void increment() {
    ++m_it;
  }

  void decrement() {
    --m_it;
  }

  decltype(auto) dereference() const {
    return (*m_fn)(*m_it);
  }

  template<typename diff_t>
  void advance(diff_t n) {
    m_it += n;
  }

  auto distance_to(const map_iterator& other) const {
    return m_it - other.m_it;
  }

  bool less(const map_iterator& other) const {
    return m_it < other.m_it;
  }

  iter_t m_it;
  const map_fn* m_fn = nullptr;
};

}    // namespace tsi::rng::iter
