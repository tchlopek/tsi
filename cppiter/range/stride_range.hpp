#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/stride_iterator.hpp"

namespace cppiter::range {

template<typename R>
class stride_range :
    public range_facade<iter::stride_iterator<
        detail::range_iterator_t<R>,
        iter::detail::iterator_category_t<
            detail::range_iterator_t<R>>>> {
    using Iterator = detail::range_iterator_t<R>;
    using BaseRange = range_facade<iter::stride_iterator<
        Iterator,
        iter::detail::iterator_category_t<Iterator>>>;
    using Difference = iter::detail::difference_t<Iterator>;

    stride_range(Iterator begin, Iterator end, Difference n, std::forward_iterator_tag) :
        BaseRange{ { begin, end, n }, { end, end, n } }
    {}

    stride_range(Iterator begin, Iterator end, Difference n, std::bidirectional_iterator_tag) :
        BaseRange{ { begin, 0, n }, { end, std::distance(begin, end), n } }
    {}

    stride_range(Iterator begin, Iterator end, Difference n, std::random_access_iterator_tag) :
        BaseRange{ { begin, begin, n }, { begin, end, n } }
    {}

public:
    stride_range(Iterator begin, Iterator end, Difference n) :
        stride_range{ begin, end, n, iter::detail::iterator_category_t<Iterator>{} }
    {}
};

}
