#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename I>
struct filter_iterator_traits : iterator_traits_facade<
    I,
    min_iterator_category_t<category_t<I>, std::bidirectional_iterator_tag>>
{};

template<typename I, typename P, typename C>
class filter_iterator_impl;

template<typename I, typename P>
class filter_iterator_impl<I, P, std::forward_iterator_tag> {
public:
    filter_iterator_impl(I iter, I end, P pred) :
        iter{ iter }, end{ end }, pred{ pred } {
    }

    bool equal(const filter_iterator_impl& other) const {
        align_position();
        return iter == other.iter;
    }

    void increment() {
        ++iter;
        align_position();
    }

    reference_t<I> dereference() const {
        return *iter;
    }

    void align_position() const {
        while (iter != end && !pred(dereference())) {
            ++iter;
        }
    }

    mutable I iter;
    I end;
    P pred;
};

template<typename I, typename P>
class filter_iterator_impl<I, P, std::bidirectional_iterator_tag> {
public:
    filter_iterator_impl(I iter, std::pair<I, I> bounds, P pred) :
        iter{ iter }, bounds{ bounds }, pred{ pred } {
    }

    bool equal(const filter_iterator_impl& other) const {
        align_position();
        return iter == other.iter;
    }

    void increment() {
        ++iter;
        align_position();
    }

    void decrement() {
        while (iter != bounds.first && !pred(*--iter)) {
        }
    }

    reference_t<I> dereference() const {
        return *iter;
    }

    void align_position() const {
        while (iter != bounds.second && !pred(*iter)) {
            ++iter;
        }
    }

    mutable I iter;
    std::pair<I, I> bounds;
    P pred;
};

}

template<typename I, typename P>
class filter_iterator :
    public iterator_facade<filter_iterator<I, P>, detail::filter_iterator_traits<I>>,
    private detail::filter_iterator_impl<I, P, category_t<detail::filter_iterator_traits<I>>> {

    friend class iter::iterator_accessor;

public:
    using detail::filter_iterator_impl<I, P, category_t<detail::filter_iterator_traits<I>>>::
        filter_iterator_impl;
};

}
