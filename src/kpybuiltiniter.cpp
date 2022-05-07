#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyBuiltinIter::KPyBuiltinIter() : KPyCallable(){}

// ---
KPyBuiltinIter::KPyBuiltinIter(const KPyBuiltinIter& other){}

// ---
KPyBuiltinIter::~KPyBuiltinIter(){}


// ---
KPyType* KPyBuiltinIter::get_type(){
    return kpytypes[KPyTypeId::KPY_BUILTIN_TYPE];
}
