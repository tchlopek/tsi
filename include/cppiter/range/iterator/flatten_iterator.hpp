#pragma once

#include <cppiter/range/util/range_iterator.hpp>

#include "util/category_types.hpp"
#include "util/iterator_facade.hpp"
#include "util/min_category.hpp"

namespace cppiter::rng::iter {

namespace util {
template<typename iter_t>
using inner_iterator_t = rng::util::iterator_t<reference_t<iter_t>>;
}

template<typename iter_t>
struct flatten_iterator_traits
  : public std::iterator_traits<util::inner_iterator_t<iter_t>> {
  using iterator_category = util::min_category_t<
    util::category_t<iter_t>,
    util::
      min_category_t<util::category_t<util::inner_iterator_t<iter_t>>, util::bi>>;
};

template<typename iter_t, typename range_t>
class flatten_iterator
  : public util::iterator_facade<
      flatten_iterator<iter_t, range_t>,
      flatten_iterator_traits<iter_t>> {
  friend class util::iterator_accessor;

public:
  flatten_iterator() = default;
  flatten_iterator(
    const iter_t& base,
    const util::inner_iterator_t<iter_t>& inner,
    range_t* range
  )
    : m_base{ base }
    , m_inner{ inner }
    , m_range{ range } {
    while (m_base != base_end()) {
      if (!m_base->empty()) {
        m_inner = m_base->begin();
        break;
      }
      ++m_base;
    }
  }

private:
  bool equal(const flatten_iterator& other) const {
    return m_inner == other.m_inner;
  }

  decltype(auto) dereference() const {
    return *m_inner;
  }

  void increment() {
    ++m_inner;
    while (m_inner == m_base->end()) {
      if (++m_base == base_end()) {
        m_inner = {};
        break;
      }
      m_inner = m_base->begin();
    }
  }

  void decrement() {
    if (m_base == base_end()) {
      --m_base;
      m_inner = m_base->end();
    }
    while (m_base != base_begin() && m_inner == m_base->begin()) {
      --m_base;
      m_inner = m_base->end();
    }
    --m_inner;
  }

  auto base_begin() const {
    return m_range->m_range.begin();
  }

  auto base_end() const {
    return m_range->m_range.end();
  }

  iter_t m_base;
  util::inner_iterator_t<iter_t> m_inner;
  range_t* m_range = nullptr;
};

}    // namespace cppiter::rng::iter
