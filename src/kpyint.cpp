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

// ---
KPyObject KPyInt::__add__(std::vector<KPyObject*>* args){
    KPyInt *iobj;
    KPyFloat *fobj;
    std::ostringstream oss;
    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyObject *arg = (*args)[0];
    switch(arg->get_type()->type_id()){
    case KPyTypeId::KPY_INT_TYPE:
        iobj = (KPyInt*)arg;
        return new KPyInt(this->value + iobj->value);
    case KPyTypeId::KPY_FLOAT_TYPE:
        fobj = (KPyFloat*)arg;
        return new KPyFloat(this->value + fobj->get_value());
    default:
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Invalid types for +: int and " + arg->get_type()->to_string()
        );
    }
}

// ---
KPyObject KPyInt::__sub__(std::vector<KPyObject*>* args){
    KPyInt *iobj;
    KPyFloat *fobj;
    std::ostringstream oss;
    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyObject *arg = (*args)[0];
    switch(arg->get_type()->type_id()){
    case KPyTypeId::KPY_INT_TYPE:
        iobj = (KPyInt*)arg;
        return new KPyInt(this->value - iobj->value);
    case KPyTypeId::KPY_FLOAT_TYPE:
        fobj = (KPyFloat*)arg;
        return new KPyFloat(this->value - fobj->get_value());
    default:
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Invalid types for -: int and " + arg->get_type()->to_string()
        );
    }
}

// ---
KPyObject KPyInt::__mul__(std::vector<KPyObject*>* args){
    KPyInt *iobj;
    KPyFloat *fobj;
    std::ostringstream oss;
    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyObject *arg = (*args)[0];
    switch(arg->get_type()->type_id()){
    case KPyTypeId::KPY_INT_TYPE:
        iobj = (KPyInt*)arg;
        return new KPyInt(this->value * iobj->value);
    case KPyTypeId::KPY_FLOAT_TYPE:
        fobj = (KPyFloat*)arg;
        return new KPyFloat(this->value * fobj->get_value());
    default:
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Invalid types for *: int and " + arg->get_type()->to_string()
        );
    }
}

// ---
KPyObject KPyInt::__truediv__(std::vector<KPyObject*>* args){
    KPyInt *iobj;
    KPyFloat *fobj;
    std::ostringstream oss;
    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyObject *arg = (*args)[0];
    switch(arg->get_type()->type_id()){
    case KPyTypeId::KPY_INT_TYPE:
        iobj = (KPyInt*)arg;
        if(iobj->value == 0){
            throw new KPyException(
                KPYILLEGALOPERATIONEXCEPTION,
                "ZeroDivisionError: integer division or modulo by zero"
            );
        }
        return new KPyFloat(this->value / iobj->value);
    case KPyTypeId::KPY_FLOAT_TYPE:
        fobj = (KPyFloat*)arg;
        if(fobj->get_value() == 0){
            throw new KPyException(
                KPYILLEGALOPERATIONEXCEPTION,
                "ZeroDivisionError: integer division or modulo by zero"
            );
        }
        return new KPyFloat(this->value / fobj->get_value());
    default:
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Invalid types for /: int and " + arg->get_type()->to_string()
        );
    }
}
