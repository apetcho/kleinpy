#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyList::KPyList(std::vector<KPyObject*>* arglist) : KPyObject() {
    data = *arglist;

    dict["__getitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyList::__getitem__
    );
    dict["__setitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyList::__setitem__
    );
    dict["__len__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyList::__len__
    );
    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyList::__iter__
    );
    dict["append"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyList::append
    );
}

// ---
KPyList::~KPyList(){}

// ---
KPyType* KPyList::get_type(){
    return kpytypes[KPyTypeId::KPY_LIST_TYPE];
}

// ---
void KPyList::set_value(int index, KPyObject *obj){
    data[index] = obj;
}

// ---
std::string KPyList::to_string(){
    std::ostringstream oss;

    oss << "[";
    for(int i=0; i < data.size(); i++){
        oss << data[i]->to_string();
        if(i < data.size()-1){
            oss << ", ";
        }
    }
    oss << "]";

    return oss.str();
}

// ---
KPyObject* KPyList::get_value(int index){
    if(index >= data.size()){
        throw new KPyException(KPYSTOPITERATIONEXCEPTION, "Stop Iteration");
    }

    return data[index];
}
