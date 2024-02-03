#pragma once

#include <type_traits>

#include "util/category_types.hpp"
#include "util/iterator_facade.hpp"
#include "util/min_category.hpp"

namespace tsi::rng::iter {

namespace detail {

template<typename iter_t>
struct step_iterator_traits : public std::iterator_traits<iter_t> {
  using iterator_category = std::conditional_t<
    std::is_same_v<util::category_t<iter_t>, util::bi>,
    util::fi,
    util::category_t<iter_t>>;
};

template<typename iter_t, typename range_t, typename cat_t>
class step_iterator_impl {
public:
  step_iterator_impl() = default;
  step_iterator_impl(const iter_t& it, range_t* range)
    : m_it{ it }
    , m_range{ range } {
  }

  bool equal(const step_iterator_impl& other) const {
    return m_it == other.m_it;
  }

  void increment() {
    for (std::ptrdiff_t i = 0; m_it != get_end() && i != get_step(); ++i, ++m_it)
      ;
  }

  decltype(auto) dereference() const {
    return *m_it;
  }

  auto get_end() const {
    return m_range->m_range.end();
  }

  std::ptrdiff_t get_step() const {
    return m_range->m_step;
  }

  iter_t m_it;
  range_t* m_range = nullptr;
};

template<typename iter_t, typename range_t>
class step_iterator_impl<iter_t, range_t, util::ri> {
public:
  step_iterator_impl() = default;
  step_iterator_impl(const iter_t& it, range_t* range)
    : m_it{ it }
    , m_range{ range }
    , m_index{ m_it - get_begin() } {
    if (get_step() > 0 && m_index % get_step() != 0) {
      m_index += get_step() - m_index % get_step();
    }
  }

  bool equal(const step_iterator_impl& other) const {
    return m_index == other.m_index;
  }

  void increment() {
    m_index += get_step();
  }

  void decrement() {
    m_index -= get_step();
  }

  decltype(auto) dereference() const {
    m_it = get_begin() + m_index;
    return *m_it;
  }

  template<typename diff_t>
  void advance(diff_t n) {
    m_index += get_step() * n;
  }

  auto distance_to(const step_iterator_impl& other) const {
    return (other.m_index - m_index) / get_step();
  }

  bool less(const step_iterator_impl& other) const {
    return m_index < other.m_index;
  }

  auto get_begin() const {
    return m_range->m_range.begin();
  }

  auto get_end() const {
    return m_range->m_range.end();
  }

  std::ptrdiff_t get_step() const {
    return m_range->m_step;
  }

  mutable iter_t m_it;
  range_t* m_range = nullptr;
  std::ptrdiff_t m_index;
};

}    // namespace detail

template<typename iter_t, typename range_t>
class step_iterator
  : public util::iterator_facade<
      step_iterator<iter_t, range_t>,
      detail::step_iterator_traits<iter_t>>
  , private detail::step_iterator_impl<
      iter_t,
      range_t,
      util::category_t<detail::step_iterator_traits<iter_t>>> {
  friend class util::iterator_accessor;

  using base_t = detail::step_iterator_impl<
    iter_t,
    range_t,
    util::category_t<detail::step_iterator_traits<iter_t>>>;

public:
  using base_t::step_iterator_impl;
};

}    // namespace tsi::rng::iter
