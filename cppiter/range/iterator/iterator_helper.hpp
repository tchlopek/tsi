#pragma once

#include <iterator>

namespace cppiter::range::iter {

namespace detail {

template<typename IteratorWrapper>
struct wrapped_iterator;

template<template<typename...> class IteratorWrapper, typename InnerIterator, typename... Ts>
struct wrapped_iterator<IteratorWrapper<InnerIterator, Ts...>> {
    using type = InnerIterator;
};

template<typename IteratorWrapper>
using wrapped_iterator_t = typename wrapped_iterator<IteratorWrapper>::type;

/* ========================================================================= */

template<typename C> constexpr std::size_t iterator_category_rank;
template<> constexpr std::size_t iterator_category_rank<std::input_iterator_tag> = 0;
template<> constexpr std::size_t iterator_category_rank<std::output_iterator_tag> = 1;
template<> constexpr std::size_t iterator_category_rank<std::forward_iterator_tag> = 2;
template<> constexpr std::size_t iterator_category_rank<std::bidirectional_iterator_tag> = 3;
template<> constexpr std::size_t iterator_category_rank<std::random_access_iterator_tag> = 4;

}

template<typename C1, typename C2>
struct min_iterator_category {
    using type = std::conditional_t<
        (detail::iterator_category_rank<C1> < detail::iterator_category_rank<C2>),
        C1,
        C2>;
};

template<typename C1, typename C2>
using min_iterator_category_t = typename min_iterator_category<C1, C2>::type;

/* ========================================================================= */

template<typename T>
struct add_ref_const;

template<typename T>
struct add_ref_const<T&> {
    using type = const T&;
};

template<typename T>
struct add_ref_const<const T&> {
    using type = const T&;
};

template<typename T>
struct add_ref_const<T*> {
    using type = const T*;
};

template<typename T>
struct add_ref_const<const T*> {
    using type = const T*;
};

template<typename T>
using add_ref_const_t = typename add_ref_const<T>::type;

/* ========================================================================= */

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

/* ========================================================================= */

namespace detail {

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

}
