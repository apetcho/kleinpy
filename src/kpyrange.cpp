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

// ---
std::string KPyRange::to_string(){
    std::ostringstream oss;
    oss << "range(" << start << ", " << stop << ", " << increment << ")";

    return oss.str();
}

// ---
KPyObject* KPyRange::__getitem__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyInt* idxObj = (KPyInt*)(*args)[0];
    int idx = idxObj->get_value();

    return index_of(idx);
}
