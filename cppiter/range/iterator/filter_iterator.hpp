#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

template<typename BaseIter, typename Pred>
class filter_iterator : public iterator_facade<filter_iterator<BaseIter, Pred>> {
    using BaseType = iterator_facade<filter_iterator<BaseIter, Pred>>;

public:
    filter_iterator(BaseIter begin, BaseIter end, Pred pred) :
        begin{ begin }, end{ end }, predicate{ pred }
    {
        align_position();
    }

    bool equal(const filter_iterator& other) const {
        return begin == other.begin;
    }

    void increment() {
        ++begin;
        align_position();
    }

    void decrement() {
        do {
            --begin;
        } while (!predicate(dereference()));
    }

    typename BaseType::reference dereference() {
        return *begin;
    }

private:
    void align_position() {
        while (begin != end && !predicate(dereference()))
            ++begin;
        }

    BaseIter begin;
    BaseIter end;
    Pred predicate;
};

}
