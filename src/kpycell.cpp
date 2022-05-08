#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyCell::KPyCell(KPyObject *ref) : KPyObject(){
    this->ref = ref;
}

// ---
KPyCell::~KPyCell(){
    try{ delete ref; }
    catch(...){}
}

// ---
KPyObject* KPyCell::deref(){
    return ref;
}

// ---
void KPyCell::set(KPyObject *ref){
    this->ref = ref;
}

// ---
KPyType* KPyCell::get_type(){
    return kpytypes[KPyTypeId::KPY_CELL_TYPE];
}
