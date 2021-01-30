#pragma once
#include <iterator>

namespace detail {

template<typename IteratorWrapper>
struct inner_iterator;

template<template<typename...> class IteratorWrapper, typename InnerIterator, typename... Ts>
struct inner_iterator<IteratorWrapper<InnerIterator, Ts...>> {
    using type = InnerIterator;
};

template<typename IteratorWrapper>
using inner_iterator_t = typename inner_iterator<IteratorWrapper>::type;

}

template<typename DerivedIterator, typename Category>
class iterator_facade_impl;

template<typename DerivedIterator>
class iterator_facade_impl<DerivedIterator, std::forward_iterator_tag> {
protected:
    using inner_iterator = detail::inner_iterator_t<DerivedIterator>;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename std::iterator_traits<inner_iterator>::value_type;
    using difference_type = typename std::iterator_traits<inner_iterator>::value_type;
    using pointer = typename std::iterator_traits<inner_iterator>::pointer;
    using reference = typename std::iterator_traits<inner_iterator>::reference;

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

template<typename DerivedIterator>
class iterator_facade_impl<DerivedIterator, std::bidirectional_iterator_tag> :
    public iterator_facade_impl<DerivedIterator, std::forward_iterator_tag> {

protected:
    using iterator_facade_impl<DerivedIterator, std::forward_iterator_tag>::derived;

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

template<typename DerivedIterator>
class iterator_facade_impl<DerivedIterator, std::random_access_iterator_tag> :
    public iterator_facade_impl<DerivedIterator, std::bidirectional_iterator_tag> {
    using Base = iterator_facade_impl<DerivedIterator, std::bidirectional_iterator_tag>;
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

template<typename DerivedIterator>
class iterator_facade :
    public iterator_facade_impl<
        DerivedIterator,
        typename std::iterator_traits<detail::inner_iterator_t<DerivedIterator>>::iterator_category> {
    DerivedIterator& derived() = delete;
    const DerivedIterator& derived() const = delete;
};
