#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Inner>
struct flatten_iterator_traits {
    using iterator_category = detail::min_iterator_category_t<
        iterator_category_t<Inner>,
        std::bidirectional_iterator_tag>;
    using reference = reference_t<Inner>;
    using difference_type = difference_t<Inner>;
    using value_type = value_t<Inner>;
    using pointer = pointer_t<Inner>;
};

}

template<typename BaseIter, typename InnerIter, typename Category>
class flatten_iterator_impl;

template<typename BaseIter, typename InnerIter>
class flatten_iterator_impl<BaseIter, InnerIter, std::forward_iterator_tag> :
    public iterator_facade<
        flatten_iterator_impl<BaseIter, InnerIter, std::forward_iterator_tag>,
        detail::flatten_iterator_traits<InnerIter>> {
    using BaseType = iterator_facade<
        flatten_iterator_impl<BaseIter, InnerIter, std::forward_iterator_tag>,
        detail::flatten_iterator_traits<InnerIter>>;

    friend class derived_access;

public:
    flatten_iterator_impl(BaseIter iter, BaseIter end, InnerIter inner) :
        baseIter{ iter }, baseEnd{ end }, innerIter{ inner }
    {
        while (baseIter != baseEnd && baseIter->empty()) {
            ++baseIter;
        }
        if (baseIter != baseEnd) {
            innerIter = baseIter->begin();
        }
    }

private:
    bool equal(const flatten_iterator_impl& other) const {
        return innerIter == other.innerIter && baseIter == other.baseIter;
    }

    typename BaseType::reference dereference() const {
        return *innerIter;
    }

    void increment() {
        ++innerIter;
        while (innerIter == baseIter->end()) {
            ++baseIter;
            if (baseIter == baseEnd) {
                innerIter = {};
                break;
            }
            innerIter = baseIter->begin();
        }
    }

    BaseIter baseIter;
    BaseIter baseEnd;
    InnerIter innerIter;
};

template<typename BaseIter, typename InnerIter>
class flatten_iterator_impl<BaseIter, InnerIter, std::bidirectional_iterator_tag> :
    public iterator_facade<
        flatten_iterator_impl<BaseIter, InnerIter, std::bidirectional_iterator_tag>,
        detail::flatten_iterator_traits<InnerIter>> {
    using BaseType = iterator_facade<
        flatten_iterator_impl<BaseIter, InnerIter, std::bidirectional_iterator_tag>,
        detail::flatten_iterator_traits<InnerIter>>;

    friend class derived_access;

public:
    flatten_iterator_impl(BaseIter begin, BaseIter end, BaseIter iter, InnerIter inner) :
        baseBegin{ begin }, baseEnd{ end }, baseIter{ iter }, innerIter{ inner }
    {
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

    typename BaseType::reference dereference() const {
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

    void decrement() {
        while (baseIter == baseEnd || innerIter == baseIter->begin()) {
            if (baseIter == baseBegin) {
                break;
            }
            --baseIter;
            innerIter = baseIter->end();
        }
        --innerIter;
    }

private:
    BaseIter baseBegin;
    BaseIter baseEnd;
    BaseIter baseIter;
    InnerIter innerIter;
};

template<typename BaseIter, typename InnerIter>
class flatten_iterator : 
    public flatten_iterator_impl<
        BaseIter,
        InnerIter,
        detail::min_iterator_category_t<
            typename detail::flatten_iterator_traits<BaseIter>::iterator_category,
            typename detail::flatten_iterator_traits<InnerIter>::iterator_category>> {
public:
    using flatten_iterator_impl<
        BaseIter,
        InnerIter,
        detail::min_iterator_category_t<
            typename detail::flatten_iterator_traits<BaseIter>::iterator_category,
            typename detail::flatten_iterator_traits<InnerIter>::iterator_category>>::
            flatten_iterator_impl;
};

}
