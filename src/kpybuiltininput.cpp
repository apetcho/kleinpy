#include"kleinpy.hpp"

using namespace kleinpy;

// ---
KPyBuiltinInput::KPyBuiltinInput() : KPyCallable(){}

// ---
KPyBuiltinInput::KPyBuiltinInput(const KPyBuiltinInput& other){}

// ---
KPyBuiltinInput::~KPyBuiltinInput(){}

// ---
KPyType* KPyBuiltinInput::get_type(){
    return kpytypes[KPyTypeId::KPY_BUILTIN_TYPE];
}
