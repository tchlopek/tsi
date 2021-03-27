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
        return derived_access::dereference(derived());
    }

    pointer_t<Base> operator->() const {
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
    using Base::derived;

public:
    using iterator_category = std::random_access_iterator_tag;

    DerivedIterator& operator+=(difference_t<Base> n) {
        derived_access::advance(derived(), n);
        return derived();
    }

    DerivedIterator& operator-=(difference_t<Base> n) {
        derived_access::advance(derived(), -n);
        return derived();
    }

    DerivedIterator operator+(difference_t<Base> n) const {
        auto current = derived();
        derived_access::advance(current, n);
        return current;
    }

    DerivedIterator operator-(difference_t<Base> n) const {
        auto current = derived();
        derived_access::advance(current, -n);
        return current;
    }

    difference_t<Base> operator-(const DerivedIterator& other) const {
        return derived_access::distance_to(derived(), other);
    }

    reference_t<Base> operator[](difference_t<Base> n) const {
        return derived_access::dereference(*this + n);
    }
};

template<
    typename Derived,
    typename Traits = detail::iterator_traits_facade<detail::wrapped_iterator_t<Derived>>>
class iterator_facade : public iterator_facade_impl<Derived, Traits, category_t<Traits>>
{};

}
