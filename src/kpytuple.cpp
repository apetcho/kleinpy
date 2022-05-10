#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyTuple::KPyTuple(std::vector<KPyObject*>* objlist) : KPyObject() {
    data = *objlist;
    dict["__getitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyTuple::__getitem__
    );
    dict["__len__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyTuple::__len__
    );
    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyTuple::__iter__
    );
}

// ---
KPyTuple::~KPyTuple(){}

// ---
KPyType* KPyTuple::get_type(){
    return kpytypes[KPyTypeId::KPY_TUPLE_TYPE];
}

// ---
int KPyTuple::size(){
    return data.size();
}

// ---
std::string KPyTuple::to_string(){
    std::ostringstream oss;
    oss << "(";
    for(int i=0; i < data.size(); i++){
        oss << data[i]->to_string();
        if(i < data.size()-1){ oss << ", "; }
    }
    oss << ")";

    return oss.str();
}
