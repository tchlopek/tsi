#pragma once

#include <numeric>

#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"
#include "util/range_traits.hpp"

/*#include "dereference_range.hpp"
#include "enumerate_range.hpp"
#include "filter_range.hpp"
#include "flatten_range.hpp"
#include "replace_range.hpp"
#include "reverse_range.hpp"
#include "skip_range.hpp"
#include "stride_range.hpp"
#include "take_range.hpp"
#include "unique_range.hpp"*/
#include "map_range.hpp"

namespace cppiter::rng {

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

  template<typename map_fn>
  auto map(map_fn&& fn) {
    return range_factory<map_range<range_t, map_fn>>{ std::in_place,
                                                      std::move(m_range),
                                                      std::forward<map_fn>(fn) };
  }

  /*auto deref() {
    return range_factory<dereference_range<R>>{ { begin(), end() } };
  }

  auto enumerate(typename R::difference_type index = {}) {
    return range_factory<enumerate_range<R>>{ { begin(), end(), index } };
  }

  template<typename P>
  auto filter(P pred) {
    return range_factory<filter_range<R, P>>{ { begin(), end(), pred } };
  }

  auto flatten() {
    return range_factory<flatten_range<R>>{ { begin(), end() } };
  }



  template<typename P>
  auto replace(P pred, const typename R::value_type& newVal) {
    return range_factory<replace_range<R, P>>{
      { begin(), end(), pred, newVal }
    };
  }

  auto replace(
    const typename R::value_type& oldVal,
    const typename R::value_type& newVal
  ) {
    const auto pred = [oldVal](const auto& current) {
      return oldVal == current;
    };
    return range_factory<replace_range<R, decltype(pred)>>{
      { begin(), end(), pred, newVal }
    };
  }

  auto reverse() {
    return range_factory<reverse_range<R>>{ { begin(), end() } };
  }

  auto skip(typename R::difference_type n) {
    return range_factory<skip_range<R>>{ { begin(), end(), n } };
  }

  auto stride(typename R::difference_type n) {
    return range_factory<stride_range<R>>{ { begin(), end(), n } };
  }

  auto take(typename R::difference_type n) {
    return range_factory<take_range<R>>{ { begin(), end(), n } };
  }

  auto unique() {
    return range_factory<unique_range<R>>{ { begin(), end() } };
  }

  template<typename T>
  T collect() {
    return T{ begin(), end() };
  }

  template<template<typename...> class C>
  auto collect() {
    using VT = typename util::range_facade<util::range_iterator_t<R>>::value_type;
    return C<VT>{ begin(), end() };
  }

  template<typename val_t, typename binop_t>
  val_t fold(val_t&& init, binop_t&& binop) {
    return std::accumulate(
      begin(),
      end(),
      std::forward<val_t>(init),
      std::forward<binop_t>(binop)
    );
  }*/

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

}    // namespace cppiter::rng
