#pragma once

#include <iterator>

namespace cppiter::rng::iter::util {

template<typename I>
using value_t = typename std::iterator_traits<I>::value_type;

template<typename I>
using reference_t = typename std::iterator_traits<I>::reference;

template<typename I>
using category_t = typename std::iterator_traits<I>::iterator_category;

template<typename I>
using pointer_t = typename std::iterator_traits<I>::pointer;

template<typename I>
using difference_t = typename std::iterator_traits<I>::difference_type;

}    // namespace cppiter::rng::iter::util