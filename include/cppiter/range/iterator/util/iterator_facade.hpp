#pragma once

#include "iterator_traits.hpp"

namespace cppiter::rng::iter::util {

using fi = std::forward_iterator_tag;
using bi = std::bidirectional_iterator_tag;
using ri = std::random_access_iterator_tag;

class iterator_accessor {
public:
  template<typename I>
  static bool equal(const I& lhs, const I& rhs) {
    return lhs.equal(rhs);
  }

  template<typename I>
  static decltype(auto) dereference(I& iter) {
    return iter.dereference();
  }

  template<typename I>
  static void increment(I& iter) {
    iter.increment();
  }

  template<typename I>
  static void decrement(I& iter) {
    iter.decrement();
  }

  template<typename I, typename diff_t>
  static void advance(I& iter, diff_t n) {
    iter.advance(n);
  }

  template<typename I>
  static auto distance_to(const I& lhs, const I& rhs) {
    return lhs.distance_to(rhs);
  }

  template<typename I>
  static bool less(const I& lhs, const I& rhs) {
    return lhs.less(rhs);
  }
};

template<typename iter_t>
class iterator_facade_impl_base {
public:
  iter_t& derived() {
    return *static_cast<iter_t*>(this);
  }

  const iter_t& derived() const {
    return *static_cast<const iter_t*>(this);
  }
};

template<typename iter_t, typename traits_t, typename cat_t>
class iterator_facade_impl;

template<typename iter_t, typename traits_t>
class iterator_facade_impl<iter_t, traits_t, fi>
  : public iterator_facade_impl_base<iter_t> {
protected:
  using iterator_facade_impl_base<iter_t>::derived;

public:
  decltype(auto) operator*() const {
    return iterator_accessor::dereference(derived());
  }

  auto operator->() const {
    return std::addressof(iterator_accessor::dereference(derived()));
  }

  iter_t& operator++() {
    iterator_accessor::increment(derived());
    return derived();
  }

  iter_t operator++(int) {
    auto current = derived();
    iterator_accessor::increment(derived());
    return current;
  }

  bool operator==(const iter_t& other) const {
    return iterator_accessor::equal(derived(), other);
  }

  bool operator!=(const iter_t& other) const {
    return !(derived() == other);
  }
};

template<typename iter_t, typename traits_t>
class iterator_facade_impl<iter_t, traits_t, bi>
  : public iterator_facade_impl<iter_t, traits_t, fi> {
protected:
  using iterator_facade_impl_base<iter_t>::derived;

public:
  iter_t& operator--() {
    iterator_accessor::decrement(derived());
    return derived();
  }

  iter_t operator--(int) {
    auto current = derived();
    iterator_accessor::decrement(derived());
    return current;
  }
};

template<typename iter_t, typename traits_t>
class iterator_facade_impl<iter_t, traits_t, ri>
  : public iterator_facade_impl<iter_t, traits_t, bi> {
private:
  using iterator_facade_impl_base<iter_t>::derived;

public:
  iter_t& operator+=(difference_t<traits_t> n) {
    iterator_accessor::advance(derived(), n);
    return derived();
  }

  iter_t& operator-=(difference_t<traits_t> n) {
    iterator_accessor::advance(derived(), -n);
    return derived();
  }

  iter_t operator+(difference_t<traits_t> n) const {
    auto current = derived();
    iterator_accessor::advance(current, n);
    return current;
  }

  iter_t operator-(difference_t<traits_t> n) const {
    auto current = derived();
    iterator_accessor::advance(current, -n);
    return current;
  }

  difference_t<traits_t> operator-(const iter_t& other) const {
    return iterator_accessor::distance_to(derived(), other);
  }

  reference_t<traits_t> operator[](difference_t<traits_t> n) const {
    return iterator_accessor::dereference(*this + n);
  }

  bool operator<(const iter_t& other) const {
    return iterator_accessor::less(derived(), other);
  }

  bool operator>(const iter_t& other) const {
    return iterator_accessor::less(other, derived());
  }

  bool operator<=(const iter_t& other) const {
    return !(*this > other);
  }

  bool operator>=(const iter_t& other) const {
    return !(*this < other);
  }
};

template<typename iter_t, typename traits_t>
class iterator_facade
  : public iterator_facade_impl<iter_t, traits_t, category_t<traits_t>>
  , public traits_t {};
}    // namespace cppiter::rng::iter::util
