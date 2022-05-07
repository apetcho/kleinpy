#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyBuiltinFPrint::KPyBuiltinFPrint() : KPyCallable(){}

// ---
KPyBuiltinFPrint::KPyBuiltinFPrint(const KPyBuiltinFPrint& other){}

// ---
KPyBuiltinFPrint::~KPyBuiltinFPrint(){}

// ---
KPyType* KPyBuiltinFPrint::get_type(){
    return kpytypes[KPyTypeId::KPY_BUILTIN_TYPE];
}
