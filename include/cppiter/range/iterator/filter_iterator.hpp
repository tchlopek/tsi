#pragma once

#include "util/iterator_facade.hpp"
#include "util/min_category.hpp"

namespace cppiter::rng::iter {

template<typename iter_t>
struct filter_iterator_traits : public std::iterator_traits<iter_t> {
  using iterator_category = util::
    min_category_t<util::category_t<iter_t>, util::bi>;
};

template<typename iter_t, typename range_t>
class filter_iterator
  : public util::iterator_facade<
      filter_iterator<iter_t, range_t>,
      filter_iterator_traits<iter_t>> {
  friend class util::iterator_accessor;

public:
  filter_iterator() = default;
  filter_iterator(const iter_t& it, const range_t* range)
    : m_it{ it }
    , m_range{ range } {
  }

private:
  bool equal(const filter_iterator& other) const {
    align_position();
    return m_it == other.m_it;
  }

  void increment() {
    ++m_it;
    align_position();
  }

  void decrement() {
    while (m_it != parent_begin() && !m_range->m_fn(*--m_it)) {
    }
  }

  decltype(auto) dereference() const {
    return *m_it;
  }

  void align_position() const {
    while (m_it != parent_end() && !m_range->m_fn(*m_it)) {
      ++m_it;
    }
  }

  auto parent_begin() const {
    return m_range->m_range.begin();
  }

  auto parent_end() const {
    return m_range->m_range.end();
  }

  mutable iter_t m_it;
  const range_t* m_range = nullptr;
};

}    // namespace cppiter::rng::iter
