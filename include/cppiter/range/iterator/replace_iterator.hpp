#pragma once

#include "util/add_ref_const.hpp"
#include "util/iterator_facade.hpp"

namespace cppiter::rng::iter {

namespace detail {
using namespace util;

template<typename Iter>
struct replace_iterator_traits : iterator_traits_facade<
    Iter,
    category_t<Iter>,
    value_t<Iter>,
    add_ref_const_t<reference_t<Iter>>,
    add_ref_const_t<pointer_t<Iter>>>
{};

}

template<typename Iter, typename Pred>
class replace_iterator :
    public util::iterator_facade<replace_iterator<Iter, Pred>, detail::replace_iterator_traits<Iter>> {

    friend class util::iterator_accessor;

public:
    replace_iterator(Iter iter, Pred pred, const util::value_t<Iter>& newVal) :
        iter{ iter }, newVal{ newVal }, pred{ pred }
    {}

private:
    bool equal(const replace_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
    }

    void decrement() {
        --iter;
    }

    util::reference_t<detail::replace_iterator_traits<Iter>> dereference() const {
        return pred(*iter) ? newVal : *iter;
    }

    void advance(util::difference_t<Iter> n) {
        iter += n;
    }

    util::difference_t<Iter> distance_to(const replace_iterator& other) const {
        return iter - other.iter;
    }

    bool less(const replace_iterator& other) const {
        return iter < other.iter;
    }

    Iter iter;
    util::value_t<Iter> newVal;
    Pred pred;
};

}
