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
