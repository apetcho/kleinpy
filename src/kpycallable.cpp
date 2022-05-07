#include "kleinpy.hpp"

using namespace kleinpy;
// --
KPyCallable::KPyCallable() : KPyObject() {
    dict["__call__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyCallable::__call__
    );
}


// --
KPyCallable::KPyCallable(const KPyCallable& obj){}

// --
KPyCallable::~KPyCallable(){}
