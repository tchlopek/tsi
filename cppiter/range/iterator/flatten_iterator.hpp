#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename I>
using inner_iterator_t = range::range_iterator_t<value_t<I>>;

template<typename Iter>
struct flatten_iterator_traits {
    using iterator_category = min_iterator_category_t<
        category_t<Iter>,
        min_iterator_category_t<
            category_t<inner_iterator_t<Iter>>,
            std::bidirectional_iterator_tag>>;
    using reference = reference_t<inner_iterator_t<Iter>>;
    using difference_type = difference_t<inner_iterator_t<Iter>>;
    using value_type = value_t<inner_iterator_t<Iter>>;
    using pointer = pointer_t<inner_iterator_t<Iter>>;
};

template<typename Iter>
struct flatten_iterator_base {
    flatten_iterator_base(Iter iter, Iter end, inner_iterator_t<Iter> inner) :
        baseIter{ iter }, baseEnd{ end }, innerIter{ inner } {
        while (baseIter != baseEnd && baseIter->empty()) {
            ++baseIter;
        }
        if (baseIter != baseEnd) {
            innerIter = baseIter->begin();
        }
    }

    bool equal(const flatten_iterator_base& other) const {
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

template<typename Iter, typename Category>
class flatten_iterator_impl;

template<typename Iter>
class flatten_iterator_impl<Iter, std::forward_iterator_tag> :
    public iterator_facade<
        flatten_iterator_impl<Iter, std::forward_iterator_tag>,
        flatten_iterator_traits<Iter>>,
    private flatten_iterator_base<Iter> {

    friend class iter::derived_access;

public:
    flatten_iterator_impl(Iter iter, Iter end, inner_iterator_t<Iter> inner) :
        flatten_iterator_base<Iter>{ iter, end, inner }
    {}
};

template<typename Iter>
class flatten_iterator_impl<Iter, std::bidirectional_iterator_tag> :
    public iterator_facade<
        flatten_iterator_impl<Iter, std::bidirectional_iterator_tag>,
        flatten_iterator_traits<Iter>>,
    private flatten_iterator_base<Iter> {

    using Base = flatten_iterator_base<Iter>;

    friend class iter::derived_access;

public:
    flatten_iterator_impl(Iter begin, Iter end, Iter iter, inner_iterator_t<Iter> inner) :
        Base{ iter, end, inner }, baseBegin{ begin }
    {}

private:
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

template<typename Iter>
class flatten_iterator : 
    public detail::flatten_iterator_impl<Iter, category_t<detail::flatten_iterator_traits<Iter>>> {
public:
    using detail::flatten_iterator_impl<Iter, category_t<detail::flatten_iterator_traits<Iter>>>::
        flatten_iterator_impl;
};

}
