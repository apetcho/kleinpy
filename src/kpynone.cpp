#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyNone::KPyNone() : KPyObject(){}

// ---
KPyNone::KPyNone(const KPyNone& other){}

// ---
KPyNone::~KPyNone(){}

// ---
KPyType* KPyNone::get_type(){
    return kpytypes[KPyTypeId::KPY_NONE_TYPE];
}

// ---
std::string KPyNone::to_string(){
    return "None";
}
