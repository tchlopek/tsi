#pragma once

#include <iterator>

#include "util/iterator_facade.hpp"

namespace cppiter::rng::iter {

template<typename iter_t>
struct unique_iterator_traits : public std::iterator_traits<iter_t> {
  using iterator_category = std::forward_iterator_tag;
};

template<typename iter_t, typename range_t>
class unique_iterator
  : public util::iterator_facade<
      unique_iterator<iter_t, range_t>,
      unique_iterator_traits<iter_t>> {
  friend class util::iterator_accessor;

public:
  unique_iterator() = default;
  unique_iterator(const iter_t& it, range_t* range)
    : m_it{ it }
    , m_range{ range } {
  }

private:
  bool equal(const unique_iterator& other) const {
    return m_it == other.m_it;
  }

  void increment() {
    const auto& beginVal = dereference();
    while (++m_it != end() && dereference() == beginVal)
      ;
  }

  decltype(auto) dereference() const {
    return *m_it;
  }

  auto end() const {
    return m_range->m_range.end();
  }

  iter_t m_it;
  range_t* m_range = nullptr;
};

}    // namespace cppiter::rng::iter
