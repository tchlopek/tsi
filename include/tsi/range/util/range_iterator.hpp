#pragma once

#include <iterator>
#include <type_traits>

namespace tsi::rng::util {

template<typename range_t>
using iterator_t = decltype(std::begin(std::declval<range_t&>()));

template<typename range_t>
using const_iterator_t = decltype(std::cbegin(std::declval<range_t&>()));

}    // namespace tsi::rng::util
