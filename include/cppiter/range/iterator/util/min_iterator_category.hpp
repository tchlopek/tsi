#pragma once

#include <iterator>

namespace cppiter::range::iter::util {

namespace detail {
template<typename C> constexpr std::size_t iterator_category_rank;
template<> constexpr std::size_t iterator_category_rank<std::input_iterator_tag> = 0;
template<> constexpr std::size_t iterator_category_rank<std::output_iterator_tag> = 1;
template<> constexpr std::size_t iterator_category_rank<std::forward_iterator_tag> = 2;
template<> constexpr std::size_t iterator_category_rank<std::bidirectional_iterator_tag> = 3;
template<> constexpr std::size_t iterator_category_rank<std::random_access_iterator_tag> = 4;
}

template<typename C1, typename C2>
struct min_iterator_category {
    using type = std::conditional_t<
        (detail::iterator_category_rank<C1> < detail::iterator_category_rank<C2>),
        C1,
        C2>;
};

template<typename C1, typename C2>
using min_iterator_category_t = typename min_iterator_category<C1, C2>::type;

}