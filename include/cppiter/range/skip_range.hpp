#pragma once

#include "util/range_facade.hpp"
#include "util/range_iterator.hpp"

namespace cppiter::range {

template<typename R>
class skip_range : public util::range_facade<util::range_iterator_t<R>> {
    using I = util::range_iterator_t<R>;

public:
    skip_range(I begin, I end, iter::util::difference_t<I> n) :
        util::range_facade<I>{ { makeBeginIter<iter::util::category_t<I>>(begin, end, n) }, { end } }
    {}

private:
    template<typename C>
    I makeBeginIter(I begin, I end, iter::util::difference_t<I> n) {
        if constexpr (std::is_same_v<C, std::random_access_iterator_tag>) {
            return begin + std::min(end - begin, n);
        } else {
            for (; begin != end && n-- > 0; ++begin);
            return begin;
        }
    }
};

}
