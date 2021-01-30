#pragma once

#include "iterator_facade.hpp"

template<typename BaseIter, typename Pred>
class filter_iterator : public iterator_facade<filter_iterator<BaseIter, Pred>> {
    using BaseType = iterator_facade<filter_iterator<BaseIter, Pred>>;

public:
    filter_iterator(BaseIter begin, BaseIter end, Pred pred) :
        begin{ begin }, end{ end }, predicate{ pred }
    {}

    bool equal(const filter_iterator& other) const {
        return begin == other.begin;
    }

    void increment() {
        do { 
            ++begin;
        } while (begin != end && !predicate(dereference()));
    }

    void decrement() {
        while (!predicate(dereference())) {
            --begin;
        }
    }

    typename BaseType::reference dereference() {
        return *begin;
    }

private:
    BaseIter begin;
    BaseIter end;
    Pred predicate;
};