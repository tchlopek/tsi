#pragma once

#include <algorithm>
#include <numeric>
#include <optional>

#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

#include "dereference_range.hpp"
#include "enumerate_range.hpp"
#include "filter_range.hpp"
#include "flatten_range.hpp"
#include "map_range.hpp"
#include "replace_range.hpp"
#include "reverse_range.hpp"
#include "skip_range.hpp"
#include "step_range.hpp"
#include "take_range.hpp"
#include "unique_range.hpp"

namespace tsi::rng {

template<typename range_t>
class range_factory
  : public util::range_facade<range_factory<range_t>>
  , public util::
      range_traits<util::iterator_t<range_t>, util::const_iterator_t<range_t>> {
  friend class util::range_accessor;

public:
  template<typename... arg_ts>
  range_factory(std::in_place_t, arg_ts&&... args)
    : m_range{ std::forward<arg_ts>(args)... } {
  }

  explicit range_factory(const range_t& range)
    : m_range{ range } {
  }

  explicit range_factory(range_t&& range)
    : m_range{ std::move(range) } {
  }

  template<typename pred_t>
  bool any(pred_t&& pred) {
    return std::any_of(
      m_range.begin(),
      m_range.end(),
      std::forward<pred_t>(pred)
    );
  }

  template<typename pred_t>
  bool all(pred_t&& pred) {
    return std::all_of(
      m_range.begin(),
      m_range.end(),
      std::forward<pred_t>(pred)
    );
  }

  template<typename collect_t>
  collect_t collect() {
    return collect_t{ m_range.begin(), m_range.end() };
  }

  template<template<typename...> class collect_tpl>
  auto collect() {
    using value_type = typename range_t::value_type;
    return collect_tpl<value_type>{ m_range.begin(), m_range.end() };
  }

  auto deref() {
    return range_factory<dereference_range<range_t>>{ std::in_place,
                                                      std::move(m_range) };
  }

  auto enumerate(std::ptrdiff_t index = 0) {
    return range_factory<enumerate_range<range_t>>{ std::in_place,
                                                    std::move(m_range),
                                                    index };
  }

  template<typename map_fn>
  auto map(map_fn&& fn) {
    return range_factory<map_range<range_t, map_fn>>{ std::in_place,
                                                      std::move(m_range),
                                                      std::forward<map_fn>(fn) };
  }

  template<typename pred_t>
  auto filter(pred_t&& pred) {
    return range_factory<filter_range<range_t, pred_t>>{
      std::in_place,
      std::move(m_range),
      std::forward<pred_t>(pred)
    };
  }

  auto flatten() {
    return range_factory<flatten_range<range_t>>{ std::in_place,
                                                  std::move(m_range) };
  }

  template<typename val_t, typename binop_t>
  val_t fold(val_t&& init, binop_t&& binop) {
    return std::accumulate(
      m_range.begin(),
      m_range.end(),
      std::forward<val_t>(init),
      std::forward<binop_t>(binop)
    );
  }

  template<typename binop_t>
  auto reduce(binop_t&& binop) {
    std::optional<typename range_t::value_type> res;
    if (!m_range.empty()) {
      const auto b = m_range.begin();
      res = std::accumulate(
        std::next(b),
        m_range.end(),
        *b,
        std::forward<binop_t>(binop)
      );
    }
    return res;
  }

  template<typename pred_t, typename value_t>
  auto replace(pred_t&& pred, value_t&& val) {
    return range_factory<replace_range<range_t, pred_t>>{
      std::in_place,
      std::move(m_range),
      std::forward<pred_t>(pred),
      std::forward<value_t>(val)
    };
  }

  auto reverse() {
    return range_factory<reverse_range<range_t>>{ std::in_place,
                                                  std::move(m_range) };
  }

  auto skip(std::ptrdiff_t n) {
    return range_factory<skip_range<range_t>>{ std::in_place,
                                               std::move(m_range),
                                               n };
  }

  auto step(std::ptrdiff_t n) {
    return range_factory<step_range<range_t>>{ std::in_place,
                                               std::move(m_range),
                                               n };
  }

  auto take(std::ptrdiff_t n) {
    return range_factory<take_range<range_t>>{ std::in_place,
                                               std::move(m_range),
                                               n };
  }

  auto unique() {
    return range_factory<unique_range<range_t>>{ std::in_place,
                                                 std::move(m_range) };
  }

private:
  auto make_begin() {
    return m_range.begin();
  }

  auto make_end() {
    return m_range.end();
  }

  auto make_const_begin() const {
    return m_range.cbegin();
  }

  auto make_const_end() const {
    return m_range.cend();
  }

  range_t m_range;
};

}    // namespace tsi::rng
