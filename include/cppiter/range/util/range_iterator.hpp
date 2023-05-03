#pragma once

#include <type_traits>

namespace cppiter::rng::util {

template<typename R>
struct range_iterator {
  using type = typename R::iterator;
};

template<typename R>
struct range_iterator<const R> {
  using type = typename R::const_iterator;
};

template<typename Value, std::size_t Size>
struct range_iterator<Value[Size]> {
  using type = std::decay_t<Value[Size]>;
};

template<typename R>
using range_iterator_t = typename range_iterator<R>::type;

}    // namespace cppiter::rng::util
