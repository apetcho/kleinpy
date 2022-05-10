#include "kleinpy.hpp"

using namespace kleinpy;

KPyStrIterator::KPyStrIterator(KPyStr *text) : KPyObject(){
    this->str = text;
    this->index = 0;

    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStrIterator::__iter__
    );
    dict["__next__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStrIterator::__next__
    );
}

// ---
KPyStrIterator::~KPyStrIterator(){}

// ---
KPyType* KPyStrIterator::get_type(){
    return kpytypes[KPyTypeId::KPY_STR_ITERATOR_TYPE];
}
