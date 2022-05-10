#include "kleinpy.hpp"

using namespace kleinpy;

KPyRangeIterator::KPyRangeIterator(KPyRange *obj) : KPyObject() {
    rangeObj = obj;
    index = 0;

    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyRangeIterator::__iter__
    );
    dict["__next__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyRangeIterator::__next__
    );
}

// ---
KPyRangeIterator::~KPyRangeIterator(){}
