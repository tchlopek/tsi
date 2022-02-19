#pragma once

#include "iterator_traits_facade.hpp"
#include "wrapped_iterator.hpp"

namespace cppiter::rng::iter::util {

class iterator_accessor {
public:
    template<typename I>
    static bool equal(const I& lhs, const I& rhs) {
        return lhs.equal(rhs);
    }

    template<typename I>
    static reference_t<I> dereference(I& iter) {
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
    static void advance(I& iter, difference_t<I> n) {
        iter.advance(n);
    }

    template<typename I>
    static difference_t<I> distance_to(const I& lhs, const I& rhs) {
        return lhs.distance_to(rhs);
    }

    template<typename I>
    static bool less(const I& lhs, const I& rhs) {
        return lhs.less(rhs);
    }
};

template<typename DerivedIterator, typename Traits>
class iterator_facade_impl_base : public Traits {
public:
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

    reference_t<Base> operator*() const {
        return iterator_accessor::dereference(derived());
    }

    pointer_t<Base> operator->() const {
        return std::addressof(iterator_accessor::dereference(derived()));
    }

    DerivedIterator& operator++() {
        iterator_accessor::increment(derived());
        return derived();
    }

    DerivedIterator operator++(int) {
        auto current = derived();
        iterator_accessor::increment(derived());
        return current;
    }

    bool operator==(const DerivedIterator& other) const {
        return iterator_accessor::equal(derived(), other);
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
        iterator_accessor::decrement(derived());
        return derived();
    }

    DerivedIterator operator--(int) {
        auto current = derived();
        iterator_accessor::decrement(derived());
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

    DerivedIterator& operator+=(difference_t<Base> n) {
        iterator_accessor::advance(derived(), n);
        return derived();
    }

    DerivedIterator& operator-=(difference_t<Base> n) {
        iterator_accessor::advance(derived(), -n);
        return derived();
    }

    DerivedIterator operator+(difference_t<Base> n) const {
        auto current = derived();
        iterator_accessor::advance(current, n);
        return current;
    }

    DerivedIterator operator-(difference_t<Base> n) const {
        auto current = derived();
        iterator_accessor::advance(current, -n);
        return current;
    }

    difference_t<Base> operator-(const DerivedIterator& other) const {
        return iterator_accessor::distance_to(derived(), other);
    }

    reference_t<Base> operator[](difference_t<Base> n) const {
        return iterator_accessor::dereference(*this + n);
    }

    bool operator<(const DerivedIterator& other) const {
        return iterator_accessor::less(derived(), other);
    }

    bool operator>(const DerivedIterator& other) const {
        return iterator_accessor::less(other, derived());
    }

    bool operator<=(const DerivedIterator& other) const {
        return !(*this > other);
    }

    bool operator>=(const DerivedIterator& other) const {
        return !(*this < other);
    }
};

template<
    typename Derived,
    typename Traits = iterator_traits_facade<wrapped_iterator_t<Derived>>>
class iterator_facade : public iterator_facade_impl<Derived, Traits, category_t<Traits>>
{};

}
