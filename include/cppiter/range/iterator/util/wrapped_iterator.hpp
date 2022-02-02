#pragma once

namespace cppiter::range::iter::util {

template<typename IteratorWrapper>
struct wrapped_iterator;

template<template<typename...> class IteratorWrapper, typename InnerIterator, typename... Ts>
struct wrapped_iterator<IteratorWrapper<InnerIterator, Ts...>> {
    using type = InnerIterator;
};

template<typename IteratorWrapper>
using wrapped_iterator_t = typename wrapped_iterator<IteratorWrapper>::type;

}
