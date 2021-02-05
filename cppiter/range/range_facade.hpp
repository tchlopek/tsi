#pragma once

namespace cppiter::range {

template<typename Iterator>
struct range_types_facade {
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using iterator = Iterator;
    using const_iterator = Iterator;
};

template<typename Derived>
class range_facade_impl_base {
public:
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
protected:
    using range_facade_impl<Derived, std::bidirectional_iterator_tag>::derived;

public:
    std::size_t size() const {
        return std::distance(derived().begin(), derived().end());
    }
};

template<typename Iterator>
class range_facade :
    public range_types_facade<Iterator>,
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
