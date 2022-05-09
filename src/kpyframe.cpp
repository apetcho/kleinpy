#include "kleinpy.hpp"

using namespace kleinpy;

const char* richcomp[13] = {
    "__lt__",
    "__le__",
    "__eq__",
    "__ne__",
    "__gt__",
    "__ge__",
    "__contains__",
    "__notin__",    // This is not an actual operator
    "is_",
    "is_not",
    "__excmatch__",
    "BAD"
};
