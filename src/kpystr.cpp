#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyStr::KPyStr(std::string txt) : KPyObject(){
    value = txt;

    dict["__add__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__add__
    );
    dict["__float__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__float__
    );
    dict["__int__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__int__
    );
    dict["__bool__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__bool__
    );
    dict["__funlist__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__funlist__
    );
    dict["__eq__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__eq__
    );
    dict["split"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::split
    );
    dict["__getitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__getitem__
    );
    dict["__len__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__len__
    );
    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyStr::__iter__
    );
}

// ---
KPyStr::KPyStr(const KPyStr& other) : KPyStr(other.value){}

// ---
KPyStr::~KPyStr(){}

// ---
KPyObject* KPyStr::__add__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyStr *arg = (KPyStr*)(*args)[0];
    return new KPyStr(this->value + arg->value);
}

// ---
KPyObject* KPyStr::__str__(std::vector<KPyObject*>* args){
    return this;
}

// ---
KPyObject* KPyStr::__float__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    double xvalue;
    try{
        std::istringstream iss(this->to_string());
        iss.exceptions(std::ios_base::failbit | std::ios_base::badbit);
        iss >> xvalue;
        return new KPyFloat(xvalue);
    }catch(...){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "could not convert string to float: '" + this->to_string() + "'"
        );
    }
}

// ---
KPyObject* KPyStr::__int__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    int ivalue;
    try{
        std::istringstream iss(this->to_string());
        iss.exceptions(std::ios_base::failbit | std::ios_base::badbit);
        iss >> ivalue;
        return new KPyInt(ivalue);
    }catch(...){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "invalid literal for int() with base 10: '" + this->to_string()+"'"
        );
    }
}
