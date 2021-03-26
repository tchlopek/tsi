#pragma once

#include "range_facade.hpp"
#include "range_iterator.hpp"
#include "iterator/stride_iterator.hpp"

namespace cppiter::range {

template<typename R>
class stride_range : public range_facade<iter::stride_iterator<range_iterator_t<R>>> {
    using Iterator = range_iterator_t<R>;
    using BaseRange = range_facade<iter::stride_iterator<Iterator>>;
    using Difference = iter::difference_t<Iterator>;

public:
    stride_range(Iterator begin, Iterator end, Difference n) :
        stride_range{ begin, end, n, iter::category_t<Iterator>{} }
    {}

private:
    stride_range(Iterator begin, Iterator end, Difference n, std::forward_iterator_tag) :
        BaseRange{ { begin, end, n }, { end, end, n } }
    {}

    stride_range(Iterator begin, Iterator end, Difference n, std::bidirectional_iterator_tag) :
        BaseRange{ { begin, 0, n }, { end, std::distance(begin, end), n } }
    {}

    stride_range(Iterator begin, Iterator end, Difference n, std::random_access_iterator_tag) :
        BaseRange{ { begin, begin, n }, { begin, end, n } }
    {}
};

}
