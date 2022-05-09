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
KPyObject* KPyFloat::__float__(std::vector<KPyObject*>* args){
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
