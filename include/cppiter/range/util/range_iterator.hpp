#pragma once

#include <type_traits>

namespace cppiter::rng::util {

template<typename R>
using iterator_t = decltype(std::begin(std::declval<R&>()));

template<typename R>
using const_iterator_t = decltype(std::cbegin(std::declval<R&>()));

}    // namespace cppiter::rng::util
