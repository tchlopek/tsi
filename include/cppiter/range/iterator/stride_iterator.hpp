#pragma once

#include "util/iterator_facade.hpp"

namespace cppiter::rng::iter {

namespace detail {
using namespace util;

template<typename I>
struct stride_iterator_traits
  : iterator_traits_facade<
      I,
      std::conditional_t<
        std::is_same_v<category_t<I>, std::bidirectional_iterator_tag>,
        std::forward_iterator_tag,
        category_t<I>>> {};

template<typename I, typename C>
class stride_iterator_impl {
public:
  stride_iterator_impl(I iter, I end, difference_t<I> step)
    : iter{ iter }
    , end{ end }
    , step{ step } {
  }

  bool equal(const stride_iterator_impl& other) const {
    return iter == other.iter;
  }

  void increment() {
    for (difference_t<I> i = 0; iter != end && i != step; ++i, ++iter)
      ;
  }

  reference_t<I> dereference() const {
    return *iter;
  }

  I iter;
  I end;
  difference_t<I> step;
};

template<typename I>
class stride_iterator_impl<I, std::random_access_iterator_tag> {
public:
  stride_iterator_impl(I begin, I iter, difference_t<I> step)
    : begin{ begin }
    , iter{ iter }
    , index{ iter - begin }
    , step{ step } {
    if (step > 0 && index % step != 0) {
      this->index += step - index % step;
    }
  }

  bool equal(const stride_iterator_impl& other) const {
    return index == other.index;
  }

  void increment() {
    index += step;
  }

  void decrement() {
    index -= step;
  }

  reference_t<I> dereference() const {
    iter = begin + index;
    return *iter;
  }

  void advance(difference_t<I> n) {
    index += step * n;
  }

  difference_t<I> distance_to(const stride_iterator_impl& other) const {
    return (other.index - index) / step;
  }

  bool less(const stride_iterator_impl& other) const {
    return index < other.index;
  }

  I begin;
  mutable I iter;
  difference_t<I> index;
  difference_t<I> step;
};

}    // namespace detail

template<typename I>
class stride_iterator
  : public util::
      iterator_facade<stride_iterator<I>, detail::stride_iterator_traits<I>>
  , private detail::stride_iterator_impl<
      I,
      util::category_t<detail::stride_iterator_traits<I>>> {
  friend class util::iterator_accessor;

public:
  using detail::stride_iterator_impl<
    I,
    util::category_t<detail::stride_iterator_traits<I>>>::stride_iterator_impl;
};

}    // namespace cppiter::rng::iter
