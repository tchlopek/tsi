#pragma once

#include "iterator_helper.hpp"

namespace cppiter::range::iter {

class derived_access {
public:
    template<typename I>
    static bool equal(const I& lhs, const I& rhs) {
        return lhs.equal(rhs);
    }

    template<typename I>
    static detail::reference_t<I> dereference(I& iter) {
        return iter.dereference();
    }

    template<typename I>
    static void increment(I& iter) {
        iter.increment();
    }

    template<typename I>
    static void decrement(I& iter) {
        iter.decrement();
    }

    template<typename I>
    static void advance(I& iter, detail::difference_t<I> n) {
        iter.advance(n);
    }

    template<typename I>
    static detail::difference_t<I> distance_to(const I& lhs, const I& rhs) {
        return lhs.distance_to(rhs);
    }
};

template<typename DerivedIterator, typename Traits>
class iterator_facade_impl_base {
    using InnerIterator = detail::wrapped_iterator_t<DerivedIterator>;
    using IteratorTraits = detail::conditional_iterator_traits_t<Traits, InnerIterator>; 

public:
    using value_type = detail::value_t<IteratorTraits>;
    using difference_type = detail::difference_t<IteratorTraits>;
    using pointer = detail::pointer_t<IteratorTraits>;
    using reference = detail::reference_t<IteratorTraits>;

    DerivedIterator& derived() {
        return *static_cast<DerivedIterator*>(this);
    }

    const DerivedIterator& derived() const {
        return *static_cast<const DerivedIterator*>(this);
    }
};

template<typename DerivedIterator, typename Traits, typename Category>
class iterator_facade_impl;

template<typename DerivedIterator, typename Traits>
class iterator_facade_impl<DerivedIterator, Traits, std::forward_iterator_tag> :
    public iterator_facade_impl_base<DerivedIterator, Traits> {
    using Base = iterator_facade_impl_base<DerivedIterator, Traits>;

protected:
    using Base::derived;

public:
    using iterator_category = std::forward_iterator_tag;

    typename Base::reference operator*() const {
        return derived_access::dereference(derived());
    }

    typename Base::pointer operator->() const {
        return std::addressof(derived_access::dereference(derived()));
    }

    DerivedIterator& operator++() {
        derived_access::increment(derived());
        return derived();
    }

    DerivedIterator operator++(int) {
        auto current = derived();
        derived_access::increment(derived());
        return current;
    }

    bool operator==(const DerivedIterator& other) const {
        return derived_access::equal(derived(), other);
    }
    
    bool operator!=(const DerivedIterator& other) const {
        return !(derived() == other);
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
        derived_access::decrement(derived());
        return derived();
    }

    DerivedIterator operator--(int) {
        auto current = derived();
        derived_access::decrement(derived());
        return current;
    }
};

template<typename DerivedIterator, typename Traits>
class iterator_facade_impl<DerivedIterator, Traits, std::random_access_iterator_tag> :
    public iterator_facade_impl<DerivedIterator, Traits, std::bidirectional_iterator_tag> {
    using Base = iterator_facade_impl<DerivedIterator, Traits, std::bidirectional_iterator_tag>;

protected:
    using Base::derived;

public:
    using iterator_category = std::random_access_iterator_tag;

    DerivedIterator& operator+=(typename Base::difference_type n) {
        derived_access::advance(derived(), n);
        return derived();
    }

    DerivedIterator& operator-=(typename Base::difference_type n) {
        derived_access::advance(derived(), -n);
        return derived();
    }

    DerivedIterator operator+(typename Base::difference_type n) const {
        auto current = derived();
        derived_access::advance(current, n);
        return current;
    }

    DerivedIterator operator-(typename Base::difference_type n) const {
        auto current = derived();
        derived_access::advance(current, -n);
        return current;
    }

    typename Base::difference_type operator-(const DerivedIterator& other) const {
        return derived_access::distance_to(derived(), other);
    }

    typename Base::reference operator[](typename Base::difference_type n) const {
        return derived_access::dereference(*this + n);
    }
};

template<typename DerivedIterator, typename Traits = void>
class iterator_facade :
    public iterator_facade_impl<
        DerivedIterator,
        Traits,
        typename detail::conditional_iterator_traits_t<
            Traits,
            detail::wrapped_iterator_t<DerivedIterator>>::iterator_category> {
    DerivedIterator& derived() = delete;
    const DerivedIterator& derived() const = delete;
};

}
