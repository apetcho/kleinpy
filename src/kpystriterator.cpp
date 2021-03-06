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

// ---
std::string KPyStrIterator::to_string(){
    std::ostringstream oss;
    oss << "<str_iterator object at " << this << ">";
    return oss.str();
}

// ---
KPyObject* KPyStrIterator::__iter__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }
    return this;
}

// ---
KPyObject* KPyStrIterator::__next__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    return str->char_at(index++);
}
