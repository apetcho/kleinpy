#include "kleinpy.hpp"

using namespace kleinpy;

KPyBool::KPyBool() : KPyObject(){
    value = false;
    dict["__float__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyBool::__float__
    );
    dict["__int__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyBool::__int__
    );
    dict["__bool__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyBool::__bool__
    );
    dict["__eq__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyBool::__eq__
    );
}

// ---
KPyBool::KPyBool(bool value) : KPyBool(){
    this->value = value;
}
