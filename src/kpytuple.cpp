#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyTuple::KPyTuple(std::vector<KPyObject*>* objlist) : KPyObject() {
    data = *objlist;
    dict["__getitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyTuple::__getitem__
    );
    dict["__len__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyTuple::__len__
    );
    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyTuple::__iter__
    );
}
