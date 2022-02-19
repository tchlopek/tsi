#pragma once

#include "util/iterator_facade.hpp"

namespace cppiter::rng::iter {

namespace detail {
using namespace util;

template<typename Iter, typename Category>
class take_iterator_impl;

template<typename Iter>
class take_iterator_impl<Iter, std::forward_iterator_tag> {
public:
    take_iterator_impl(Iter iter, difference_t<Iter> index) :
        iter{ iter }, index{ index }
    {}

    bool equal(const take_iterator_impl& other) const {
        return iter == other.iter || index == other.index;
    }

    void increment() {
        ++index;
        ++iter;
    }

    reference_t<Iter> dereference() const {
        return *iter;
    }

    Iter iter;
    difference_t<Iter> index;
};

template<typename Iter>
class take_iterator_impl<Iter, std::bidirectional_iterator_tag> :
    public take_iterator_impl<Iter, std::forward_iterator_tag> {

    using Base = take_iterator_impl<Iter, std::forward_iterator_tag>;

public:
    using Base::take_iterator_impl;

    void decrement() {
        --Base::index;
        --Base::iter;
    }
};

template<typename Iter>
class take_iterator_impl<Iter, std::random_access_iterator_tag> {
public:
    take_iterator_impl(Iter iter) : iter{ iter }
    {}

    bool equal(const take_iterator_impl& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
    }

    void decrement() {
        --iter;
    }

    reference_t<Iter> dereference() const {
        return *iter;
    }

    void advance(difference_t<Iter> n) {
        iter += n;
    }

    difference_t<Iter> distance_to(const take_iterator_impl& other) const {
        return iter - other.iter;
    }

    Iter iter;
};

}

template<typename Iter>
class take_iterator :
    public util::iterator_facade<take_iterator<Iter>>,
    private detail::take_iterator_impl<Iter, util::category_t<Iter>> {

    friend class util::iterator_accessor;

public:
    using detail::take_iterator_impl<Iter, util::category_t<Iter>>::take_iterator_impl;
};

}
