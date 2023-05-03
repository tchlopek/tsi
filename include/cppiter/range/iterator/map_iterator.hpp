#pragma once

#include "util/iterator_facade.hpp"

namespace cppiter::rng::iter {

namespace detail {
using namespace util;

template<typename Iter, typename Func>
struct map_iterator_traits
  : iterator_traits_facade<
      Iter,
      category_t<Iter>,
      std::decay_t<std::invoke_result_t<Func, reference_t<Iter>>>,
      std::invoke_result_t<Func, reference_t<Iter>>,
      std::add_pointer_t<std::invoke_result_t<Func, reference_t<Iter>>>> {};

}    // namespace detail

template<typename Iter, typename Func>
class map_iterator
  : public util::iterator_facade<
      map_iterator<Iter, Func>,
      detail::map_iterator_traits<Iter, Func>> {
  friend class util::iterator_accessor;

public:
  map_iterator(Iter iter, Func func)
    : iter{ iter }
    , func{ func } {
  }

private:
  bool equal(const map_iterator& other) const {
    return iter == other.iter;
  }

  void increment() {
    ++iter;
  }

  void decrement() {
    --iter;
  }

  util::reference_t<detail::map_iterator_traits<Iter, Func>> dereference() const {
    return func(*iter);
  }

  void advance(util::difference_t<Iter> n) {
    iter += n;
  }

  util::difference_t<Iter> distance_to(const map_iterator& other) const {
    return iter - other.iter;
  }

  bool less(const map_iterator& other) const {
    return iter < other.iter;
  }

  Iter iter;
  Func func;
};

}    // namespace cppiter::rng::iter
