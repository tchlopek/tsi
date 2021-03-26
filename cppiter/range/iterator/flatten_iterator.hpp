#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename I>
using inner_iterator_t = range::detail::range_iterator_t<iter::detail::value_t<I>>;

template<typename BaseIter>
struct flatten_iterator_traits {
    using iterator_category = min_iterator_category_t<
        iterator_category_t<BaseIter>,
        min_iterator_category_t<
            iterator_category_t<inner_iterator_t<BaseIter>>,
            std::bidirectional_iterator_tag>>;
    using reference = reference_t<inner_iterator_t<BaseIter>>;
    using difference_type = difference_t<inner_iterator_t<BaseIter>>;
    using value_type = value_t<inner_iterator_t<BaseIter>>;
    using pointer = pointer_t<inner_iterator_t<BaseIter>>;
};

template<typename BaseIter>
struct flatten_iterator_base {
    flatten_iterator_base(BaseIter iter, BaseIter end, inner_iterator_t<BaseIter> inner) :
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

    BaseIter baseIter;
    BaseIter baseEnd;
    inner_iterator_t<BaseIter> innerIter;
};

template<typename BaseIter, typename Category>
class flatten_iterator_impl;

template<typename BaseIter>
class flatten_iterator_impl<BaseIter, std::forward_iterator_tag> :
    public iterator_facade<
        flatten_iterator_impl<BaseIter, std::forward_iterator_tag>,
        flatten_iterator_traits<BaseIter>>,
    private flatten_iterator_base<BaseIter> {

    friend class iter::derived_access;

public:
    flatten_iterator_impl(BaseIter iter, BaseIter end, inner_iterator_t<BaseIter> inner) :
        flatten_iterator_base<BaseIter>{ iter, end, inner }
    {}
};

template<typename BaseIter>
class flatten_iterator_impl<BaseIter, std::bidirectional_iterator_tag> :
    public iterator_facade<
        flatten_iterator_impl<BaseIter, std::bidirectional_iterator_tag>,
        flatten_iterator_traits<BaseIter>>,
    private flatten_iterator_base<BaseIter> {

    using Base = flatten_iterator_base<BaseIter>;

    friend class iter::derived_access;

public:
    flatten_iterator_impl(BaseIter begin, BaseIter end, BaseIter iter, inner_iterator_t<BaseIter> inner) :
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

    BaseIter baseBegin;
};

}

template<typename BaseIter>
class flatten_iterator : 
    public detail::flatten_iterator_impl<
        BaseIter, typename detail::flatten_iterator_traits<BaseIter>::iterator_category> {
public:
    using detail::flatten_iterator_impl<
        BaseIter, typename detail::flatten_iterator_traits<BaseIter>::iterator_category>::
            flatten_iterator_impl;
};

}
