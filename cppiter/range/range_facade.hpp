#pragma once

namespace cppiter::range {

template<typename Iterator>
struct range_types_facade {
    using value_type = typename Iterator::value_type;
    using reference = typename Iterator::reference;
    using iterator = Iterator;
    using const_iterator = Iterator;
};

template<typename Iterator>
class range_facade : public range_types_facade<Iterator> {
public:
    range_facade(Iterator begin, Iterator end) : b{ begin }, e{ end }
    {}

    Iterator begin() const {
        return b;
    }

    Iterator end() const {
        return e;
    }

private:
    Iterator b;
    Iterator e;
};

}
