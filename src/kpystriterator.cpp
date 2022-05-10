#include "kleinpy.hpp"

using namespace kleinpy;

KPyStrIterator::KPyStrIterator(KPyStr *text) : KPyObject(){
    this->str = text;
    this->index = 0;

    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStrIterator::__iter__
    );
    dict["__next__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStrIterator::__next__
    );
}
