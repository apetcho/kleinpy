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

// ---
std::string KPyListIterator::to_string(){
    std::ostringstream oss;
    oss << "<list_iterator object at " << this << ">";
    return oss.str();
}


// ---
KPyObject* KPyListIterator::__iter__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    return this;
}

// ---
KPyObject* KPyListIterator::__next__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    return objlist->get_value(index++);
}
