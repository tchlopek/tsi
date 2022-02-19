#pragma once

#include <cppiter/range/util/range_iterator.hpp>

#include "util/iterator_facade.hpp"
#include "util/min_iterator_category.hpp"

namespace cppiter::rng::iter {

namespace detail {
using namespace util;

template<typename I>
using inner_iterator_t = rng::util::range_iterator_t<value_t<I>>;

template<typename Iter>
struct flatten_iterator_traits : iterator_traits_facade<
    inner_iterator_t<Iter>,
    min_iterator_category_t<
        category_t<Iter>,
        min_iterator_category_t<
            category_t<inner_iterator_t<Iter>>,
            std::bidirectional_iterator_tag>>>
{};

template<typename Iter, typename C>
class flatten_iterator_impl;

template<typename Iter>
class flatten_iterator_impl<Iter, std::forward_iterator_tag> {
public:
    flatten_iterator_impl(Iter iter, Iter end, inner_iterator_t<Iter> inner) :
        baseIter{ iter }, baseEnd{ end }, innerIter{ inner } {
        while (baseIter != baseEnd && baseIter->empty()) {
            ++baseIter;
        }
        if (baseIter != baseEnd) {
            innerIter = baseIter->begin();
        }
    }

    bool equal(const flatten_iterator_impl& other) const {
        return innerIter == other.innerIter;
    }

    decltype(auto) dereference() const {
        return *innerIter;
    }

    void increment() {
        ++innerIter;
        while (innerIter == baseIter->end()) {
            if (++baseIter == baseEnd) {
                innerIter = {};
                break;
            }
            innerIter = baseIter->begin();
        }
    }

    Iter baseIter;
    Iter baseEnd;
    inner_iterator_t<Iter> innerIter;
};

template<typename Iter>
class flatten_iterator_impl<Iter, std::bidirectional_iterator_tag> :
    public flatten_iterator_impl<Iter, std::forward_iterator_tag> {

    using Base = flatten_iterator_impl<Iter, std::forward_iterator_tag>;

public:
    flatten_iterator_impl(Iter begin, Iter end, Iter iter, inner_iterator_t<Iter> inner) :
        Base{ iter, end, inner }, baseBegin{ begin }
    {}

    void decrement() {
        if (Base::baseIter == Base::baseEnd) {
            --Base::baseIter;
            Base::innerIter = Base::baseIter->end();
        }
        while (Base::baseIter != baseBegin && Base::innerIter == Base::baseIter->begin()) {
            --Base::baseIter;
            Base::innerIter = Base::baseIter->end();
        }
        --Base::innerIter;
    }

    Iter baseBegin;
};

}

template<typename I>
class flatten_iterator : 
    public util::iterator_facade<flatten_iterator<I>, detail::flatten_iterator_traits<I>>,
    private detail::flatten_iterator_impl<I, util::category_t<detail::flatten_iterator_traits<I>>> {

    friend class util::iterator_accessor;

public:
    using detail::flatten_iterator_impl<I, util::category_t<detail::flatten_iterator_traits<I>>>::
        flatten_iterator_impl;
};

}
