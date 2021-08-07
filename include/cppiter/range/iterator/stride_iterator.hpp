#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Iter, typename Category>
class stride_iterator_impl;

template<typename Iter>
class stride_iterator_impl<Iter, std::forward_iterator_tag> :
    public iterator_facade<stride_iterator_impl<Iter, std::forward_iterator_tag>> {

    friend class iter::derived_access;

public:
    stride_iterator_impl(Iter iter, Iter end, difference_t<Iter> step) :
        iter{ iter }, end{ end }, step{ step }
    {}

private:
    bool equal(const stride_iterator_impl& other) const {
        return iter == other.iter;
    }

    void increment() {
        for (difference_t<Iter> i = 0; iter != end && i != step; ++i, ++iter);
    }

    reference_t<Iter> dereference() const {
        return *iter;
    }

    Iter iter;
    Iter end;
    difference_t<Iter> step;
};

template<typename Iter>
class stride_iterator_impl<Iter, std::bidirectional_iterator_tag> :
    public iterator_facade<stride_iterator_impl<Iter, std::bidirectional_iterator_tag>> {

    friend class iter::derived_access;

public:
    stride_iterator_impl(Iter iter, difference_t<Iter> index, difference_t<Iter> step) :
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

    reference_t<Iter> dereference() const {
        std::advance(iter, offset);
        index += offset;
        offset = 0;
        return *iter;
    }

    mutable Iter iter;
    mutable difference_t<Iter> offset;
    mutable difference_t<Iter> index;
    difference_t<Iter> step;
};

template<typename Iter>
class stride_iterator_impl<Iter, std::random_access_iterator_tag>:
    public iterator_facade<stride_iterator_impl<Iter, std::random_access_iterator_tag>> {

    friend class iter::derived_access;

public:
    stride_iterator_impl(Iter begin, Iter iter, difference_t<Iter> step) :
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

    reference_t<Iter> dereference() const {
        iter = begin + index;
        return *iter;
    }

    void advance(difference_t<Iter> n) {
        index += step * n;
    }

    difference_t<Iter> distance_to(const stride_iterator_impl& other) const {
        return (other.index - index) / step;
    }

    Iter begin;
    mutable Iter iter;
    difference_t<Iter> index;
    difference_t<Iter> step;
};

}

template<typename Iter>
class stride_iterator : public detail::stride_iterator_impl<Iter, category_t<Iter>> {
public:
    using detail::stride_iterator_impl<Iter, category_t<Iter>>::stride_iterator_impl;
};

}
