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

// ---
KPyBool::KPyBool(const KPyBool& obj) : KPyBool(){
    this->value = obj.value;
}

// ---
KPyBool::~KPyBool(){}

// ---
std::string KPyBool::to_string(){
    if(value){ return "True"; }
    return "False";
}

// ---
KPyObject* KPyBool::__eq__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 1){
        oss << "TypeError: expected 1 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyBool *other = (KPyBool*)(*args)[0];

    return new KPyBool(value == other->value);
}

// ---
KPyType* KPyBool::get_type(){
    return kpytypes[KPyTypeId::KPY_BOOL_TYPE];
}

// ---
bool KPyBool::get_value(){ return value; }

KPyObject* KPyBool::__float__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 arguments, git " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    if(this->value){ return new KPyFloat(1); }

    return new KPyFloat(0);
}
