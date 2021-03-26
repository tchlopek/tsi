#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base>
struct filter_iterator_traits {
    using iterator_category = min_iterator_category_t<
        category_t<Base>,
        std::bidirectional_iterator_tag>;
    using reference = reference_t<Base>;
    using difference_type = difference_t<Base>;
    using value_type = value_t<Base>;
    using pointer = pointer_t<Base>;
};

}

template<typename BaseIter, typename Pred>
class filter_iterator : public iterator_facade<
    filter_iterator<BaseIter, Pred>,
    detail::filter_iterator_traits<BaseIter>> {
    using BaseType = iterator_facade<
        filter_iterator<BaseIter, Pred>,
        detail::filter_iterator_traits<BaseIter>>;

    friend class derived_access;

public:
    filter_iterator(BaseIter iter, BaseIter end, Pred pred) :
        iter{ iter }, end{ end }, predicate{ pred }
    {
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

    typename BaseType::reference dereference() const {
        return *iter;
    }

    void align_position() {
        while (iter != end && !predicate(dereference())) {
            ++iter;
        }
    }

    BaseIter iter;
    BaseIter end;
    Pred predicate;
};

}
