#pragma once

#include "iterator/util/iterator_traits_facade.hpp"
#include "iterator/util/wrapped_iterator.hpp"

namespace cppiter::range {

template<typename R>
class range_facade_impl_base {
    using Iterator = iter::util::wrapped_iterator_t<R>;

public:
    using value_type = iter::util::value_t<Iterator>;
    using difference_type = iter::util::difference_t<Iterator>;
    using reference = iter::util::reference_t<Iterator>;
    using const_reference = reference;
    using pointer = iter::util::pointer_t<Iterator>;
    using const_pointer = pointer;
    using iterator = Iterator;
    using const_iterator = Iterator;

    R& derived() {
        return *static_cast<R*>(this);
    }

    const R& derived() const {
        return *static_cast<const R*>(this);
    }
};

template<typename R, typename C>
class range_facade_impl;

template<typename R>
class range_facade_impl<R, std::forward_iterator_tag> :
    public range_facade_impl_base<R> {
protected:
    using range_facade_impl_base<R>::derived;

public:
    std::size_t size() const {
        return std::distance(derived().begin(), derived().end());
    }
};

template<typename R>
class range_facade_impl<R, std::bidirectional_iterator_tag> :
    public range_facade_impl<R, std::forward_iterator_tag> {
protected:
    using range_facade_impl<R, std::forward_iterator_tag>::derived;
};

template<typename R>
class range_facade_impl<R, std::random_access_iterator_tag> :
    public range_facade_impl<R, std::bidirectional_iterator_tag> {
    using Base = range_facade_impl<R, std::bidirectional_iterator_tag>;

protected:
    using range_facade_impl<R, std::bidirectional_iterator_tag>::derived;

public:
    typename Base::reference operator[](typename Base::difference_type n) const {
        return *(derived().begin() + n);
    }
};

template<typename I>
class range_facade : public range_facade_impl<range_facade<I>, iter::util::category_t<I>> {
public:
    range_facade(I begin, I end) : b{ begin }, e{ end }
    {}

    I begin() const {
        return b;
    }

    I end() const {
        return e;
    }

    bool empty() const {
        return b == e;
    }

private:
    I b;
    I e;
};

}
