#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

template<typename BaseIter>
class skip_iterator : public iterator_facade<skip_iterator<BaseIter>> {
    using BaseType = iterator_facade<skip_iterator<BaseIter>>;

    friend class derived_access;

public:
    skip_iterator(BaseIter iter) : iter{ iter }
    {}

private:
    bool equal(const skip_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
    }


    void decrement() {
        --iter;
    }

    typename BaseType::reference dereference() const {
        return *iter;
    }

    void advance(typename BaseType::difference_type n) {
        iter += n;
    }

    typename BaseType::difference_type distance_to(const skip_iterator& other) const {
        return iter - other.iter;
    }

    BaseIter iter;
};

}
