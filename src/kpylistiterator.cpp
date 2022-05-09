#include "kleinpy.hpp"

using namespace kleinpy;


// ---
KPyListIterator::KPyListIterator(KPyList *pylist) : KPyObject(){
    this->index = 0;
    this->objlist = pylist;

    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyListIterator::__iter__
    );
    dict["__next__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyListIterator::__next__
    );
}
