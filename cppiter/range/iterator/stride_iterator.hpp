#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename BaseIter, typename Category>
class stride_iterator_impl;

template<typename BaseIter>
class stride_iterator_impl<BaseIter, std::forward_iterator_tag> :
    public iterator_facade<stride_iterator_impl<BaseIter, std::forward_iterator_tag>> {
    using BaseType = iterator_facade<stride_iterator_impl<BaseIter, std::forward_iterator_tag>>;

    friend class iter::derived_access;

public:
    stride_iterator_impl(BaseIter iter, BaseIter end, difference_t<BaseType> step) :
        iter{ iter }, end{ end }, step{ step }
    {}

private:
    bool equal(const stride_iterator_impl& other) const {
        return iter == other.iter;
    }

    void increment() {
        for (difference_t<BaseType> i = 0; iter != end && i != step; ++i, ++iter);
    }

    typename BaseType::reference dereference() const {
        return *iter;
    }

    BaseIter iter;
    BaseIter end;
    difference_t<BaseType> step;
};

template<typename BaseIter>
class stride_iterator_impl<BaseIter, std::bidirectional_iterator_tag> :
    public iterator_facade<stride_iterator_impl<BaseIter, std::bidirectional_iterator_tag>> {
    using BaseType = iterator_facade<
        stride_iterator_impl<BaseIter, std::bidirectional_iterator_tag>>;

    friend class iter::derived_access;

public:
    stride_iterator_impl(
        BaseIter iter,
        difference_t<BaseType> index,
        difference_t<BaseType> step) :
        iter{ iter }, offset{}, index{ index }, step{ step } {
        if (step > 0 && index % step != 0) {
            this->index += step - index % step;
        }
    }

private:
    bool equal(const stride_iterator_impl& other) const {
        return offset + index == other.offset + other.index;
    }

    void increment() {
        offset += step;
    }

    void decrement() {
        offset -= step;
    }

    typename BaseType::reference dereference() const {
        std::advance(iter, offset);
        index += offset;
        offset = 0;
        return *iter;
    }

    mutable BaseIter iter;
    mutable difference_t<BaseType> offset;
    mutable difference_t<BaseType> index;
    difference_t<BaseType> step;
};

template<typename BaseIter>
class stride_iterator_impl<BaseIter, std::random_access_iterator_tag>:
    public iterator_facade<stride_iterator_impl<BaseIter, std::random_access_iterator_tag>> {
    using BaseType = iterator_facade<
        stride_iterator_impl<BaseIter, std::random_access_iterator_tag>>;

    friend class iter::derived_access;

public:
    stride_iterator_impl(BaseIter begin, BaseIter iter, difference_t<BaseType> step) :
        begin{ begin }, iter{ iter }, index{ iter - begin }, step{ step } {
        if (step > 0 && index % step != 0) {
            this->index += step - index % step;
        }
    }

private:
    bool equal(const stride_iterator_impl& other) const {
        return index == other.index;
    }

    void increment() {
        index += step;
    }

    void decrement() {
        index -= step;
    }

    typename BaseType::reference dereference() const {
        iter = begin + index;
        return *iter;
    }

    void advance(typename BaseType::difference_type n) {
        index += step * n;
    }

    typename BaseType::difference_type distance_to(const stride_iterator_impl& other) const {
        return (other.index - index) / step;
    }

    BaseIter begin;
    mutable BaseIter iter;
    difference_t<BaseType> index;
    difference_t<BaseType> step;
};

}

template<typename BaseIter>
class stride_iterator : public detail::stride_iterator_impl<BaseIter, category_t<BaseIter>> {
public:
    using detail::stride_iterator_impl<BaseIter, category_t<BaseIter>>::stride_iterator_impl;
};

}
