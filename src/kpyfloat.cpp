#include "kleinpy.hpp"

using namespace kleinpy;

KPyFloat::KPyFloat(double value) : KPyObject(){
    this->value = value;
    dict["__add__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFloat::__add__
    );
    dict["__float__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFloat::__float__
    );
    dict["__int__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFloat::__int__
    );
    dict["__bool__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFloat::__bool__
    );
}

// ---
KPyFloat::KPyFloat(const KPyFloat& other) : KPyFloat(other.value){}
