#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

template<typename BaseIter, typename Category>
class stride_iterator;

template<typename BaseIter>
class stride_iterator<BaseIter, std::forward_iterator_tag> :
    public iterator_facade<stride_iterator<BaseIter, std::forward_iterator_tag>> {
    using BaseType = iterator_facade<stride_iterator<BaseIter, std::forward_iterator_tag>>;

    friend class derived_access;

public:
    stride_iterator(BaseIter iter, BaseIter end, detail::difference_t<BaseType> step) :
        iter{ iter }, end{ end }, step{ step }
    {}

private:
    bool equal(const stride_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        for (detail::difference_t<BaseType> i = 0; iter != end && i != step; ++i, ++iter);
    }

    typename BaseType::reference dereference() const {
        return *iter;
    }

    BaseIter iter;
    BaseIter end;
    detail::difference_t<BaseType> step;
};

template<typename BaseIter>
class stride_iterator<BaseIter, std::bidirectional_iterator_tag> :
    public iterator_facade<stride_iterator<BaseIter, std::bidirectional_iterator_tag>> {
    using BaseType = iterator_facade<stride_iterator<
        BaseIter,
        std::bidirectional_iterator_tag>>;

    friend class derived_access;

public:
    stride_iterator(
        BaseIter iter,
        detail::difference_t<BaseType> index,
        detail::difference_t<BaseType> step) :
        iter{ iter }, offset{}, index{ index }, step{ step } {
        if (step > 0 && index % step != 0) {
            this->index += step - index % step;
        }
    }

private:
    bool equal(const stride_iterator& other) const {
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
    mutable detail::difference_t<BaseType> offset;
    mutable detail::difference_t<BaseType> index;
    detail::difference_t<BaseType> step;
};

template<typename BaseIter>
class stride_iterator<BaseIter, std::random_access_iterator_tag>:
    public iterator_facade<stride_iterator<BaseIter, std::random_access_iterator_tag>> {
    using BaseType = iterator_facade<stride_iterator<
        BaseIter,
        std::random_access_iterator_tag>>;

    friend class derived_access;

public:
    stride_iterator(BaseIter begin, BaseIter iter, detail::difference_t<BaseType> step) :
        begin{ begin }, iter{ iter }, index{ iter - begin }, step{ step } {
        if (step > 0 && index % step != 0) {
            this->index += step - index % step;
        }
    }

private:
    bool equal(const stride_iterator& other) const {
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

    typename BaseType::difference_type distance_to(const stride_iterator& other) const {
        return (other.index - index) / step;
    }

    BaseIter begin;
    mutable BaseIter iter;
    detail::difference_t<BaseType> index;
    detail::difference_t<BaseType> step;
};

}
