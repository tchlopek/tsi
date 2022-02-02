#pragma once

#include "util/iterator_traits_facade.hpp"
#include "util/wrapped_iterator.hpp"

namespace cppiter::range::iter {

class iterator_accessor {
public:
    template<typename I>
    static bool equal(const I& lhs, const I& rhs) {
        return lhs.equal(rhs);
    }

    template<typename I>
    static util::reference_t<I> dereference(I& iter) {
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
    static void advance(I& iter, util::difference_t<I> n) {
        iter.advance(n);
    }

    template<typename I>
    static util::difference_t<I> distance_to(const I& lhs, const I& rhs) {
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

    util::reference_t<Base> operator*() const {
        return iterator_accessor::dereference(derived());
    }

    util::pointer_t<Base> operator->() const {
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

    DerivedIterator& operator+=(util::difference_t<Base> n) {
        iterator_accessor::advance(derived(), n);
        return derived();
    }

    DerivedIterator& operator-=(util::difference_t<Base> n) {
        iterator_accessor::advance(derived(), -n);
        return derived();
    }

    DerivedIterator operator+(util::difference_t<Base> n) const {
        auto current = derived();
        iterator_accessor::advance(current, n);
        return current;
    }

    DerivedIterator operator-(util::difference_t<Base> n) const {
        auto current = derived();
        iterator_accessor::advance(current, -n);
        return current;
    }

    util::difference_t<Base> operator-(const DerivedIterator& other) const {
        return iterator_accessor::distance_to(derived(), other);
    }

    util::reference_t<Base> operator[](util::difference_t<Base> n) const {
        return iterator_accessor::dereference(*this + n);
    }
};

template<
    typename Derived,
    typename Traits = util::iterator_traits_facade<util::wrapped_iterator_t<Derived>>>
class iterator_facade : public iterator_facade_impl<Derived, Traits, util::category_t<Traits>>
{};

}
