#pragma once

template<typename Iterator>
class range_facade {
public:
    using value_type = typename Iterator::value_type;
    using reference = typename Iterator::reference;
    using iterator = Iterator;
    using const_iterator = Iterator;

    range_facade(iterator begin, iterator end) : b{ begin }, e{ end }
    {}

    iterator begin() const {
        return b;
    }

    iterator end() const {
        return e;
    }

private:
    iterator b;
    iterator e;
};