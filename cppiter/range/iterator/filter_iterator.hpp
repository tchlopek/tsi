#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Iter>
struct filter_iterator_traits : iterator_traits_facade<
    Iter,
    min_iterator_category_t<category_t<Iter>, std::bidirectional_iterator_tag>>
{};

}

template<typename Iter, typename Pred>
class filter_iterator :
    public iterator_facade<filter_iterator<Iter, Pred>, detail::filter_iterator_traits<Iter>> {

    friend class derived_access;

public:
    filter_iterator(Iter iter, Iter end, Pred pred) :
        iter{ iter }, end{ end }, predicate{ pred } {
        align_position();
    }

private:
    bool equal(const filter_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
        align_position();
    }

    void decrement() {
        do {
            --iter;
        } while (!predicate(dereference()));
    }

    reference_t<Iter> dereference() const {
        return *iter;
    }

    void align_position() {
        while (iter != end && !predicate(dereference())) {
            ++iter;
        }
    }

    Iter iter;
    Iter end;
    Pred predicate;
};

}
