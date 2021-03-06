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

// ---
KPyFloat::~KPyFloat(){}

// ---
std::string KPyFloat::to_string(){
    char buffer[50];
    std::sprintf(buff, "%1.1f", value);
    std::stringstream ss;
    ss << buffer;
    return ss.str();
}

// ---
KPyObject* KPyFloat::__add__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 1){
        oss << "TypeError: excepted 1 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyFloat *arg = (KPyFloat*)(*args)[0];
    return new KPyFloat(this->value + arg->value);
}

// ---
KPyType* KPyFloat::get_type(){
    return kpytypes[KPyTypeId::KPY_FLOAT_TYPE];
}

// ---
double KPyFloat::get_value(){
    return value;
}

// ---
KPyObject* KPyFloat::__float__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: excepted 0 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    return this;
}

// ---
KPyObject* KPyFloat::__int__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: excepted 0 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    int x = (int)this->get_value();
    return new KPyInt(x);
}

// ---
KPyObject* KPyFloat::__bool__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: excpected 0 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }
    if(this->get_value() == 0.0){
        return new KPyBool(false);
    }

    return new KPyBool(true);
}
