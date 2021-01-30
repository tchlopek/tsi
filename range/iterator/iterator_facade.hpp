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

template<typename DerivedIterator>
class iterator_facade {
    using inner_iterator = detail::inner_iterator_t<DerivedIterator>;

public:
    using iterator_category = typename std::iterator_traits<inner_iterator>::iterator_category;
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

    DerivedIterator& operator--() {
        derived().decrement();
        return derived();
    }

    DerivedIterator operator--(int) {
        auto current = derived();
        derived().decrement();
        return current;
    }

    DerivedIterator& operator+=(difference_type n) {
        derived().advance(n);
        return derived();
    }

    DerivedIterator& operator-=(difference_type n) {
        derived().advance(-n);
        return derived();
    }

    DerivedIterator operator+(difference_type n) const {
        auto current = derived();
        current.advance(n);
        return current;
    }

    DerivedIterator operator-(difference_type n) const {
        auto current = derived();
        current.advance(-n);
        return current;
    }

    difference_type operator-(const DerivedIterator& other) const {
        return derived().distance_to(other);
    }

    bool operator==(const DerivedIterator& other) const {
        return derived().equal(other);
    }
    
    bool operator!=(const DerivedIterator& other) const {
        return !derived().equal(other);
    }

private:
    DerivedIterator& derived() {
        return *static_cast<DerivedIterator*>(this);
    }

    const DerivedIterator& derived() const {
        return *static_cast<const DerivedIterator*>(this);
    }
};