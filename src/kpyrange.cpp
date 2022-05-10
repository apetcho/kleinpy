#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyRange::KPyRange(int start, int stop, int step) : KPyObject(){
    this->start = start;
    this->stop = stop;
    this->increment = step;

    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyRange::__iter__
    );
    dict["__len__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyRange::__len__
    );
    dict["__getitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyRange::__getitem__
    );
    dict["__list__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyRange::__list__
    );
}

// ---
KPyType* KPyRange::get_type(){
    return kpytypes[KPyTypeId::KPY_RANGE_TYPE_ID]
}

// ---
KPyObject* KPyRange::__iter__(std::vector<KPyObject*>* args){
    return new KPyRangeIterator(this);
}

// ---
KPyObject* KPyRange::__len__(std::vector<KPyObject*>* args){
    return new KPyInt((stop, start)/increment);
}
