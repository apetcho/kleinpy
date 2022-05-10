#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyTupleIterator::KPyTupleIterator(KPyTuple tuple) : KPyObject() {
    this->index = 0;
    this->tuple = tuple;

    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyTupleIterator::__iter__
    );
    dict["__next__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyTupleIterator::__next__
    );
}

// ---
KPyTupleIterator::~KPyTupleIterator(){}

// ---
KPyType* KPyTupleIterator::get_type(){
    return kpytypes[KPyTypeId::KPY_TUPLE_ITERATOR];
}

// ---
KPyObject* KPyTuple::__iter__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }
    return this;
}
