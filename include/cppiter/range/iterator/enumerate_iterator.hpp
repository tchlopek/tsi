#pragma once

#include <functional>
#include <type_traits>

#include "util/category_types.hpp"
#include "util/iterator_facade.hpp"
#include "util/iterator_traits.hpp"

namespace cppiter::rng::iter {

template<typename iter_t>
struct enumerate_iterator_traits {
  using iterator_category = std::conditional_t<
    std::is_same_v<util::category_t<iter_t>, util::bi>,
    util::fi,
    util::category_t<iter_t>>;
  using value_type = std::pair<std::ptrdiff_t, util::value_t<iter_t>>;
  using reference = std::pair<std::ptrdiff_t, util::reference_t<iter_t>>;
  using pointer = std::pair<std::ptrdiff_t, util::pointer_t<iter_t>>;
  using difference_type = util::difference_t<iter_t>;
};

template<typename iter_t>
class enumerate_iterator
  : public util::iterator_facade<
      enumerate_iterator<iter_t>,
      enumerate_iterator_traits<iter_t>> {
  friend class util::iterator_accessor;

public:
  enumerate_iterator() = default;
  enumerate_iterator(const iter_t& it, std::ptrdiff_t index)
    : m_it{ it }
    , m_index{ index } {
  }

private:
  bool equal(const enumerate_iterator& other) const {
    return m_it == other.m_it;
  }

  void increment() {
    ++m_it;
    ++m_index;
  }

  void decrement() {
    --m_it;
    --m_index;
  }

  util::reference_t<enumerate_iterator_traits<iter_t>> dereference() const {
    return { m_index, std::ref(*m_it) };
  }

  template<typename diff_t>
  void advance(diff_t n) {
    m_it += n;
    m_index += n;
  }

  auto distance_to(const enumerate_iterator& other) const {
    return m_it - other.m_it;
  }

  bool less(const enumerate_iterator& other) const {
    return m_it < other.m_it;
  }

  iter_t m_it;
  std::ptrdiff_t m_index = 0;
};

}    // namespace cppiter::rng::iter
