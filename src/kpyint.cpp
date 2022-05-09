#include "kleinpy.hpp"

using namespace kleinpy;

KPyInt::KPyInt(int value) : KPyObject() {
    this->value = value;
    dict["__add__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__add__
    );
    dict["__sub__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__sub__
    );
    dict["__mul__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__mul__
    );
    dict["__floordiv__"]=(KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__floordiv__
    );
    dict["__truediv__"]=(KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__truediv__
    );
    dict["__eq__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__eq__
    );
    dict["__gt__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__gt__
    );
    dict["__lt__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__lt__
    );
    dict["__ge__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__ge__
    );
    dict["__le__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__le__
    );
    dict["__float__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__float__
    );
    dict["__int__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__int__
    );
    dict["__bool__"] = (KPyObject* (KPyObject::*)(std::vectory<KPyObject*>*))(
        &KPyInt::__bool__
    );
}


// ---
KPyInt::KPyInt(const KPyInt& other) : KPyInt(other.value){}

// ---
KPyInt::~KPyInt(){}

// ---
std::string KPyInt::to_string(){
    std::stringstream ss;
    ss << value;
    return ss.str();
}

// ---
int KPyInt::get_value(){
    return value;
}
