#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

template<typename BaseIter, typename Pred>
class replace_iterator :
    public iterator_facade<replace_iterator<BaseIter, Pred>> {
    using BaseType = iterator_facade<replace_iterator<BaseIter, Pred>>;

    using ValueType = typename BaseType::value_type;

public:
    replace_iterator(BaseIter iter, Pred pred, const ValueType& newVal) :
        iter{ iter }, newVal{ newVal }, pred{ pred }
    {}

    bool equal(const replace_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
    }

    void decrement() {
        --iter;
    }

    typename BaseType::reference dereference() {
        return pred(*iter) ? newVal : *iter;
    }

    void advance(typename BaseType::difference_type n) {
        iter += n;
    }

    typename BaseType::difference_type distance_to(const replace_iterator& other) const {
        return iter - other.iter;
    }

private:
    BaseIter iter;
    ValueType newVal;
    Pred pred;
};

}
