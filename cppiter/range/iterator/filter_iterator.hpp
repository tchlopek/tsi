#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

namespace detail {

template<typename Base>
struct filter_iterator_traits {
    using iterator_category = min_iterator_category_t<
        typename std::iterator_traits<Base>::iterator_category,
        std::bidirectional_iterator_tag>;
    using reference = typename std::iterator_traits<Base>::reference;
    using difference_type = typename std::iterator_traits<Base>::difference_type;
    using value_type = typename std::iterator_traits<Base>::value_type;
    using pointer = typename std::iterator_traits<Base>::pointer;
};

}

template<typename BaseIter, typename Pred>
class filter_iterator : public iterator_facade<
    filter_iterator<BaseIter, Pred>,
    detail::filter_iterator_traits<BaseIter>> {
    using BaseType = iterator_facade<
        filter_iterator<BaseIter, Pred>,
        detail::filter_iterator_traits<BaseIter>>;

public:
    filter_iterator(BaseIter iter, BaseIter end, Pred pred) :
        iter{ iter }, end{ end }, predicate{ pred }
    {
        align_position();
    }

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

private:
    void align_position() {
        while (iter != end && !predicate(dereference()))
            ++iter;
        }

    BaseIter iter;
    BaseIter end;
    Pred predicate;
};

}
