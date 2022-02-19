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

template<
    typename Iter,
    typename Category = category_t<Iter>,
    typename Value = value_t<Iter>,
    typename Reference = reference_t<Iter>,
    typename Pointer = pointer_t<Iter>,
    typename Difference = difference_t<Iter>>
struct iterator_traits_facade {
    using iterator_category = Category;
    using value_type = Value;
    using reference = Reference;
    using pointer = Pointer;
    using difference_type = Difference;
};

}