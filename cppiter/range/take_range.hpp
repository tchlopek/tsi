#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/take_iterator.hpp"

namespace cppiter::range {

template<typename R>
class take_range :
    public range_facade<iter::take_iterator<
        detail::range_iterator_t<R>,
        iter::detail::iterator_category_t<
            detail::range_iterator_t<R>>>> {
    using Iterator = detail::range_iterator_t<R>;
    using BaseRange = range_facade<iter::take_iterator<
        Iterator,
        iter::detail::iterator_category_t<Iterator>>>;
    using Difference = iter::detail::difference_t<Iterator>;

public:
    take_range(Iterator begin, Iterator end, Difference n) :
        take_range{ begin, end, n, iter::detail::iterator_category_t<Iterator>{} }
    {}

private:
    take_range(Iterator begin, Iterator end, Difference n, std::forward_iterator_tag) :
        BaseRange{ { begin, 0 }, { end, n } }
    {}

    take_range(Iterator begin, Iterator end, Difference n, std::bidirectional_iterator_tag) :
        BaseRange{ { begin, 0 }, { end, n } }
    {}

    take_range(Iterator begin, Iterator end, Difference n, std::random_access_iterator_tag) :
        BaseRange{ { begin }, { begin + (end - begin < n ? end - begin : n) } }
    {}
};

}
