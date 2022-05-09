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
