#pragma once

#include <tuple>

#include "util/iterator_facade.hpp"
#include "util/iterator_traits.hpp"
#include "util/min_category.hpp"

namespace cppiter::rng::iter {

namespace detail {
template<typename... ts>
struct min_category;

template<typename t>
struct min_category<t> {
  using type = util::category_t<t>;
};

template<typename t, typename... ts>
struct min_category<t, ts...> {
  using type = util::
    min_category_t<util::category_t<t>, typename min_category<ts...>::type>;
};

template<std::size_t... is, typename iters_t>
bool pairwise_cmp_or(
  std::index_sequence<is...>,
  const iters_t& t1,
  const iters_t& t2
) {
  return ((std::get<is>(t1) == std::get<is>(t2)) || ...);
}

template<std::size_t i, typename iters_t>
std::ptrdiff_t pairwise_size_min(const iters_t& t1, const iters_t& t2) {
  if constexpr (i != std::tuple_size_v<iters_t> - 1) {
    return std::min(
      std::get<i>(t1) - std::get<i>(t2),
      pairwise_size_min<i + 1>(t1, t2)
    );
  } else {
    return std::get<i>(t1) - std::get<i>(t2);
  }
}
}    // namespace detail

template<typename... iter_ts>
struct zipped_iterator_traits {
  using iterator_category = typename detail::min_category<iter_ts...>::type;
  using value_type = std::tuple<typename iter_ts::value_type...>;
  using reference = std::tuple<typename iter_ts::reference...>;
  using pointer = std::tuple<typename iter_ts::pointer...>;
  using difference_type = std::ptrdiff_t;
};

template<typename... iter_ts>
class zipped_iterator
  : public util::iterator_facade<
      zipped_iterator<iter_ts...>,
      zipped_iterator_traits<iter_ts...>> {
  friend class util::iterator_accessor;

  static_assert(sizeof...(iter_ts) > 0);

public:
  zipped_iterator() = default;
  zipped_iterator(const iter_ts&... its)
    : m_its{ its... } {
  }

private:
  bool equal(const zipped_iterator& other) const {
    return detail::pairwise_cmp_or(
      std::make_index_sequence<sizeof...(iter_ts)>{},
      m_its,
      other.m_its
    );
  }

  void increment() {
    std::apply([](auto&... its) { (++its, ...); }, m_its);
  }

  void decrement() {
    std::apply([](auto&... its) { (--its, ...); }, m_its);
  }

  auto dereference() const {
    return std::apply(
      [](auto&... its) { return std::forward_as_tuple((*its)...); },
      m_its
    );
  }

  template<typename diff_t>
  void advance(diff_t n) {
    std::apply([&](auto&... its) { ((its += n), ...); }, m_its);
  }

  auto distance_to(const zipped_iterator& other) const {
    return detail::pairwise_size_min<0>(m_its, other.m_its);
  }

  bool less(const zipped_iterator& other) const {
    return m_its < other.m_its;
  }

  std::tuple<iter_ts...> m_its;
};

}    // namespace cppiter::rng::iter
