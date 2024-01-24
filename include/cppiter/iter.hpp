#pragma once

#include <type_traits>

// #include "cppiter/range/iterator/bound_generate_iterator.hpp"
// #include "range/generate_range.hpp"
#include "range/range_factory.hpp"

namespace cppiter {

template<typename range_t>
auto iter(range_t&& range) {
  return rng::range_factory{ std::move(range) };
}

template<typename range_t>
auto iter(const range_t& range) {
  return rng::range_factory{ range };
}

/*template<typename T>
auto gen(const T& v) {
  return rng::range_factory{ rng::generate_range<T>{ v } };
}

template<typename T1, typename T2>
auto range(T1&& b, T2&& e) {
  using _T1 = std::remove_cv_t<std::remove_reference_t<T1>>;
  using _T2 = std::remove_cv_t<std::remove_reference_t<T2>>;
  using common_t = std::common_type_t<_T1, _T2>;
  return rng::range_factory{ rng::util::range_facade{
    rng::iter::bound_generate_iterator{ common_t(std::forward<T1>(b)) },
    rng::iter::bound_generate_iterator{ common_t(std::forward<T2>(e)) } } };
}*/

}    // namespace cppiter
