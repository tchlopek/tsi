#pragma once

#include "iterator/iterator_helper.hpp"

namespace cppiter::range {

template<typename Derived>
class range_facade_impl_base {
    using Iterator = iter::detail::inner_iterator_t<Derived>;

public:
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using const_reference = reference;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using const_pointer = pointer;
    using iterator = Iterator;
    using const_iterator = Iterator;

    Derived& derived() {
        return *static_cast<Derived*>(this);
    }

    const Derived& derived() const {
        return *static_cast<const Derived*>(this);
    }
};

template<typename Derived, typename Category>
class range_facade_impl;

template<typename Derived>
class range_facade_impl<Derived, std::forward_iterator_tag> :
    public range_facade_impl_base<Derived> {
protected:
    using range_facade_impl_base<Derived>::derived;
};

template<typename Derived>
class range_facade_impl<Derived, std::bidirectional_iterator_tag> :
    public range_facade_impl<Derived, std::forward_iterator_tag> {
protected:
    using range_facade_impl<Derived, std::forward_iterator_tag>::derived;
};

template<typename Derived>
class range_facade_impl<Derived, std::random_access_iterator_tag> :
    public range_facade_impl<Derived, std::bidirectional_iterator_tag> {
    using Base = range_facade_impl<Derived, std::bidirectional_iterator_tag>;

protected:
    using range_facade_impl<Derived, std::bidirectional_iterator_tag>::derived;

public:
    typename Base::reference operator[](typename Base::difference_type n) const {
        return *(derived().begin() + n);
    }

    std::size_t size() const {
        return std::distance(derived().begin(), derived().end());
    }


};

template<typename Iterator>
class range_facade :
    public range_facade_impl<range_facade<Iterator>, typename Iterator::iterator_category> {

public:
    range_facade(Iterator begin, Iterator end) : b{ begin }, e{ end }
    {}

    Iterator begin() const {
        return b;
    }

    Iterator end() const {
        return e;
    }

private:
    Iterator b;
    Iterator e;
};

}
