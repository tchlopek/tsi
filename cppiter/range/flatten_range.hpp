#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/flatten_iterator.hpp"

namespace cppiter::range {

namespace detail {

template<typename R>
using inner_range_iterator = range_iterator_t<iter::detail::value_t<range_iterator_t<R>>>;

}

template<typename R>
class flatten_range :
    public range_facade<iter::flatten_iterator<
        detail::range_iterator_t<R>,
        detail::inner_range_iterator<R>>> {
    using Iterator = iter::flatten_iterator<
        detail::range_iterator_t<R>,
        detail::inner_range_iterator<R>>;
    using BaseRange = range_facade<Iterator>;

public:
    flatten_range(detail::range_iterator_t<R> begin, detail::range_iterator_t<R> end) :
        flatten_range{ begin, end, iter::detail::iterator_category_t<Iterator>{} }
    {}

private:
    flatten_range(
        detail::range_iterator_t<R> begin,
        detail::range_iterator_t<R> end,
        std::forward_iterator_tag) :
        BaseRange{
            { begin, end, begin->begin() },
            { end, end, detail::inner_range_iterator<R>{} }
        }
    {}

    template<typename Category>
    flatten_range(detail::range_iterator_t<R> begin, detail::range_iterator_t<R> end, Category) :
        BaseRange{
            { begin, end, begin, begin->begin() },
            { begin, end, end, detail::inner_range_iterator<R>{} }
        }
    {}
};

}
