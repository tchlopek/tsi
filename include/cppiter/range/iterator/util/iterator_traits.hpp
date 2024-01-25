#pragma once

#include <iterator>

namespace cppiter::rng::iter::util {

template<typename iter_t>
using value_t = typename std::iterator_traits<iter_t>::value_type;

template<typename iter_t>
using reference_t = typename std::iterator_traits<iter_t>::reference;

template<typename iter_t>
using category_t = typename std::iterator_traits<iter_t>::iterator_category;

template<typename iter_t>
using pointer_t = typename std::iterator_traits<iter_t>::pointer;

template<typename iter_t>
using difference_t = typename std::iterator_traits<iter_t>::difference_type;

}    // namespace cppiter::rng::iter::util