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


// ---
KPyObject* KPyTuple::get_value(int index){
    if(index >= data.size()){
        throw new KPyException(KPYSTOPITERATIONEXCEPTION, "Stop Iteration");
    }

    return data[index];
}

// ---
KPyObject* KPyTuple::__getitem__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }
    KPyInt *iobj = (KPyInt*)(*args)[0];
    int index = iobj->get_value();
    if(index >= data.size()){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION, "Index ouf of range."
        );
    }
    return data[index];
}

// ---
KPyObject* KPyTuple::__len__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }
    
    return new KPyInt(data.size());
}
