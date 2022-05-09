#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyList::KPyList(std::vector<KPyObject*>* arglist) : KPyObject() {
    data = *arglist;

    dict["__getitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyList::__getitem__
    );
    dict["__setitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyList::__setitem__
    );
    dict["__len__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyList::__len__
    );
    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyList::__iter__
    );
    dict["append"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyList::append
    );
}
