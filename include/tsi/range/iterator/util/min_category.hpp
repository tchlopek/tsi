#pragma once

#include <iterator>

#include "category_types.hpp"

namespace tsi::rng::iter::util {

using ii = std::input_iterator_tag;
using oi = std::output_iterator_tag;

namespace detail {
template<typename cat_t>
constexpr std::size_t category_rank = 0;
template<>
inline constexpr std::size_t category_rank<ii> = 1;
template<>
inline constexpr std::size_t category_rank<oi> = 2;
template<>
inline constexpr std::size_t category_rank<fi> = 3;
template<>
inline constexpr std::size_t category_rank<bi> = 4;
template<>
inline constexpr std::size_t category_rank<ri> = 5;
}    // namespace detail

template<typename cat1, typename cat2>
struct min_category {
  using type = std::conditional_t<
    (detail::category_rank<cat1> < detail::category_rank<cat2>),
    cat1,
    cat2>;
};

template<typename cat1, typename cat2>
using min_category_t = typename min_category<cat1, cat2>::type;

}    // namespace tsi::rng::iter::util