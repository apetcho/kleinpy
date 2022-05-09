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

// ---
KPyListIterator::~KPyListIterator(){}

// ---
KPyType* KPyListIterator::get_type(){
    return kpytypes[KPyTypeId::KPY_LIST_ITERATOR_TYPE];
}
