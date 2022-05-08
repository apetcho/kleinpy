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
