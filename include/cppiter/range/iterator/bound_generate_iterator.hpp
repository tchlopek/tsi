#pragma once

#include <cstddef>
#include <iterator>

#include "util/iterator_facade.hpp"

namespace cppiter::rng::iter {

namespace detail {

template<typename T>
struct bound_generate_iterator_traits
  : util::iterator_traits_facade<
      T,
      std::random_access_iterator_tag,
      T,
      T,
      std::add_pointer_t<T>,
      std::ptrdiff_t> {};

}    // namespace detail

template<typename T>
class bound_generate_iterator
  : public util::iterator_facade<
      bound_generate_iterator<T>,
      detail::bound_generate_iterator_traits<T>> {
  friend class util::iterator_accessor;

public:
  bound_generate_iterator() = default;
  explicit bound_generate_iterator(const T& v)
    : v{ v } {
  }

private:
  bool equal(const bound_generate_iterator& other) const {
    return v == other.v;
  }

  void increment() {
    ++v;
  }

  void decrement() {
    --v;
  }

  T dereference() const {
    return v;
  }

  void advance(std::ptrdiff_t n) {
    v += n;
  }

  std::ptrdiff_t distance_to(const bound_generate_iterator& other) const {
    return v - other.v;
  }

  bool less(const bound_generate_iterator& other) const {
    return v < other.v;
  }

  mutable T v;
};

}    // namespace cppiter::rng::iter
