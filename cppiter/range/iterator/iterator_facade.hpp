#pragma once
#include <iterator>

namespace cppiter::range::iter {

namespace detail {

template<typename IteratorWrapper>
struct inner_iterator;

template<template<typename...> class IteratorWrapper, typename InnerIterator, typename... Ts>
struct inner_iterator<IteratorWrapper<InnerIterator, Ts...>> {
    using type = InnerIterator;
};

template<typename IteratorWrapper>
using inner_iterator_t = typename inner_iterator<IteratorWrapper>::type;

template<typename ExternalTraits, typename DefaultTraits>
using conditional_iterator_traits_t = std::iterator_traits<
    typename std::conditional_t<
        std::is_same_v<ExternalTraits, void>,
        DefaultTraits,
        ExternalTraits>>;

}

template<typename DerivedIterator, typename Traits, typename Category>
class iterator_facade_impl;

template<typename DerivedIterator, typename Traits>
class iterator_facade_impl<DerivedIterator, Traits, std::forward_iterator_tag> {
    using InnerIterator = detail::inner_iterator_t<DerivedIterator>;
    using IteratorTraits = detail::conditional_iterator_traits_t<Traits, InnerIterator>;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename IteratorTraits::value_type;
    using difference_type = typename IteratorTraits::difference_type;
    using pointer = typename IteratorTraits::pointer;
    using reference = typename IteratorTraits::reference;

    reference operator*() {
        return derived().dereference();
    }

    DerivedIterator& operator++() {
        derived().increment();
        return derived();
    }

    DerivedIterator operator++(int) {
        auto current = derived();
        derived().increment();
        return current;
    }

    bool operator==(const DerivedIterator& other) const {
        return derived().equal(other);
    }
    
    bool operator!=(const DerivedIterator& other) const {
        return !derived().equal(other);
    }

    DerivedIterator& derived() {
        return *static_cast<DerivedIterator*>(this);
    }

    const DerivedIterator& derived() const {
        return *static_cast<const DerivedIterator*>(this);
    }
};

template<typename DerivedIterator, typename Traits>
class iterator_facade_impl<DerivedIterator, Traits, std::bidirectional_iterator_tag> :
    public iterator_facade_impl<DerivedIterator, Traits, std::forward_iterator_tag> {

protected:
    using iterator_facade_impl<DerivedIterator, Traits, std::forward_iterator_tag>::derived;

public:
    using iterator_category = std::bidirectional_iterator_tag;

    DerivedIterator& operator--() {
        derived().decrement();
        return derived();
    }

    DerivedIterator operator--(int) {
        auto current = derived();
        derived().decrement();
        return current;
    }
};

template<typename DerivedIterator, typename Traits>
class iterator_facade_impl<DerivedIterator, Traits, std::random_access_iterator_tag> :
    public iterator_facade_impl<DerivedIterator, Traits, std::bidirectional_iterator_tag> {
    using Base = iterator_facade_impl<DerivedIterator, Traits, std::bidirectional_iterator_tag>;
    using Base::derived;

public:
    using iterator_category = std::random_access_iterator_tag;

    DerivedIterator& operator+=(typename Base::difference_type n) {
        derived().advance(n);
        return derived();
    }

    DerivedIterator& operator-=(typename Base::difference_type n) {
        derived().advance(-n);
        return derived();
    }

    DerivedIterator operator+(typename Base::difference_type n) const {
        auto current = derived();
        current.advance(n);
        return current;
    }

    DerivedIterator operator-(typename Base::difference_type n) const {
        auto current = derived();
        current.advance(-n);
        return current;
    }

    typename Base::difference_type operator-(const DerivedIterator& other) const {
        return derived().distance_to(other);
    }
};

template<typename DerivedIterator, typename Traits = void>
class iterator_facade :
    public iterator_facade_impl<
        DerivedIterator,
        Traits,
        typename detail::conditional_iterator_traits_t<
            Traits,
            detail::inner_iterator_t<DerivedIterator>>::iterator_category> {
    DerivedIterator& derived() = delete;
    const DerivedIterator& derived() const = delete;
};

}
