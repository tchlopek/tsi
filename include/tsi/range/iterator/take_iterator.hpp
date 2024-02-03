#pragma once

#include <type_traits>

#include "util/category_types.hpp"
#include "util/iterator_facade.hpp"
#include "util/min_category.hpp"

namespace tsi::rng::iter {

namespace detail {

template<typename iter_t>
struct take_iterator_traits : public std::iterator_traits<iter_t> {
  using iterator_category = std::conditional_t<
    std::is_same_v<util::category_t<iter_t>, util::bi>,
    util::fi,
    util::category_t<iter_t>>;
};

using namespace util;

template<typename iter_t, typename cat_t>
class take_iterator_impl {
public:
  take_iterator_impl() = default;
  take_iterator_impl(const iter_t& it, std::ptrdiff_t index)
    : m_it{ it }
    , m_index{ index } {
  }

  bool equal(const take_iterator_impl& other) const {
    return m_it == other.m_it || m_index == other.m_index;
  }

  void increment() {
    ++m_it;
    ++m_index;
  }

  decltype(auto) dereference() const {
    return *m_it;
  }

  iter_t m_it;
  ptrdiff_t m_index = 0;
};

template<typename iter_t>
class take_iterator_impl<iter_t, util::ri> {
public:
  take_iterator_impl(const iter_t& it)
    : m_it{ it } {
  }

  bool equal(const take_iterator_impl& other) const {
    return m_it == other.m_it;
  }

  void increment() {
    ++m_it;
  }

  void decrement() {
    --m_it;
  }

  decltype(auto) dereference() const {
    return *m_it;
  }

  template<typename diff_T>
  void advance(diff_T n) {
    m_it += n;
  }

  auto distance_to(const take_iterator_impl& other) const {
    return m_it - other.m_it;
  }

  bool less(const take_iterator_impl& other) const {
    return m_it < other.m_it;
  }

  iter_t m_it;
};

}    // namespace detail

template<typename iter_t>
class take_iterator
  : public util::iterator_facade<
      take_iterator<iter_t>,
      detail::take_iterator_traits<iter_t>>
  , private detail::take_iterator_impl<iter_t, util::category_t<iter_t>> {
  friend class util::iterator_accessor;

  using base_t = detail::take_iterator_impl<iter_t, util::category_t<iter_t>>;

public:
  using base_t::take_iterator_impl;
};

}    // namespace tsi::rng::iter
