#include "kleinpy.hpp"

using namespace kleinpy;

KPyRangeIterator::KPyRangeIterator(KPyRange *obj) : KPyObject() {
    rangeObj = obj;
    index = 0;

    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyRangeIterator::__iter__
    );
    dict["__next__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyRangeIterator::__next__
    );
}

// ---
KPyRangeIterator::~KPyRangeIterator(){}

// ---
KPyType* KPyRangeIterator::get_type(){
    return kpytypes[KPyTypeId::KPY_RANGE_ITERATOR_TYPE];
}

// ---
KPyObject* KPyRangeIterator::__iter__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: expected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    return this;
}
