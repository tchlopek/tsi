#pragma once

#include <gmock/gmock.h>

namespace utest {

MATCHER(IsEmpty, negation ? "not empty" : "empty") {
    return arg.empty();
}

}