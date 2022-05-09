#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyFunListIterator::KPyFunListIterator(KPyFunList *flist) : KPyObject() {
    this->node = flist->get_node();

    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunListIterator::__iter__
    );
    dict["__next__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunListIterator::__next__
    );
}

// ---
KPyFunListIterator::~KPyFunListIterator(){}

// ---
KPyType* KPyFunListIterator::get_type(){
    return kpytypes[KPyTypeId::KPY_FUNLIST_ITERATOR_TYPE];
}


// ---
std::string KPyFunListIterator::to_string(){
    std::ostringstream oss;
    oss << "<funlist_iterator object at " << this << ">";

    return oss.str();
}

// ---
KPyObject* KPyFunListIterator::__iter__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    return this;
}

// ---
KPyObject* KPyFunListIterator::__next__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: expected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    if(node == nullptr){
        throw new KPyException(KPYSTOPITERATIONEXCEPTION, "Stop Iteration");
    }
    KPyObject *item = node->get_head();
    node = node->get_tail();
    return item;
}
