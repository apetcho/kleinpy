#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyBuiltinTPrint::KPyBuiltinTPrint() : KPyCallable(){}

// ---
KPyBuiltinTPrint::KPyBuiltinTPrint(const KPyBuiltinTPrint& other){}

// ---
KPyBuiltinTPrint::~KPyBuiltinTPrint(){}

// ---
KPyType* KPyBuiltinTPrint::get_type(){
    return kpytypes[KPyTypeId::KPY_BUILTIN_TYPE];
}
