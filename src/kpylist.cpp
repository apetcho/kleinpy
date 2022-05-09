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

// ---
KPyObject* KPyList::__getitem__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 1){
        oss << "TypeError: expected 1 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyInt *iobj = (KPyInt*)(*args)[0];
    int index = iobj->get_value();

    if(index >= data.size()){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Index out of range"
        );
    }

    return data[index];
}

// ---
KPyObject* KPyList::__setitem__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 2){
        oss << "TypeError: expected 2 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyInt *iobj = (KPyInt*)(*args)[0];
    int index = iobj->get_value();
    if(index >= data.size()){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Index out of range."
        );
    }
    data[index] = (*args)[1];

    return new KPyNone();
}

// ---
KPyObject* KPyList::__len__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: expected 0 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    return new KPyInt(data.size());
}

// ---
KPyObject* KPyList::__iter__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: expected 0 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    return new KPyListIterator(this);
}
