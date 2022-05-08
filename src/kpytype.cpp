#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyType::KPyType(std::string typestr, KPyTypeId id) : KPyCallable() {
    this->typeStr = typestr;
    this->index = id;
}

// ---
KPyType::~KPyType(){}

// ---
std::string KPyType::to_string(){
    return this->typeStr;
}

// ---
KPyType* KPyType::get_type(){
    return kpytypes[KPyTypeId::KPY_TYPE_TYPE];
}

// ---
KPyTypeId KPyType::type_id(){
    return index;
}

// ---
std::string KPyType::call_name(){
    return "type";
}

// --
KPyObject* KPyType::__str__(std::vector<KPyObject*>* args){
    return new KPyStr("<class '" + to_string() + "'");
}

// ---
KPyObject* KPyType::__type__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: excpected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    return kpytypes[KPyTypeId::KPY_TYPE_TYPE];
}

// ---
KPyObject* KPyType::__call__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    std::vector<KPyObject*>* emptyArgs = new std::vector<KPyObject*>();
    KPyObject *arg = (*args)[0];
    std::string funname = "__" + this->to_string() + "__";

    return arg->call_method(funname, emptyArgs);
}
