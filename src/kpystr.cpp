#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyStr::KPyStr(std::string txt) : KPyObject(){
    value = txt;

    dict["__add__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__add__
    );
    dict["__float__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__float__
    );
    dict["__int__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__int__
    );
    dict["__bool__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__bool__
    );
    dict["__funlist__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__funlist__
    );
    dict["__eq__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__eq__
    );
    dict["split"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::split
    );
    dict["__getitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__getitem__
    );
    dict["__len__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__len__
    );
    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__iter__
    );
}

// ---
KPyStr::KPyStr(const KPyStr& other) : KPyStr(other.value){}
