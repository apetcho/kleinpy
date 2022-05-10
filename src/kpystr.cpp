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
        oss << "TypeError: expected 0 argument, got " << args->size();
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
        oss << "TypeError: expected 0 argument, got " << args->size();
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

// ---
KPyObject* KPyStr::__bool__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 0){
        oss << "TypeError: expected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    if(this->to_string() == ""){ return new KPyBool(false); }
    return new KPyBool(true);
}

// ---
KPyObject* KPyStr::__eq__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyStr *arg = (KPyStr*)(*args)[0];
    if(this->to_string() == arg->to_string()){ return new KPyBool(true); }
    return new KPyBool(false);
}

// ---
KPyObject* KPyStr::__funlist__(std::vector<KPyObject*>* args){
    KPyFunList *result = new KPyFunList();
    for(int k = value.size()-1; k >= 0, k--){
        std::ostringstream oss;
        oss << value[k];
        result = new KPyFunList(new KPyStr(oss.str()), result);
    }

    return result;
}

// ---
KPyType* KPyStr::get_type(){
    return kpytypes[KPyTypeId::KPY_STR_TYPE];
}

// ---
std::string KPyStr::to_string(){
    return value;
}

// ---
KPyStr* KPyStr::char_at(int index){
    if(index >= value.size()){
        throw new KPyException(KPYSTOPITERATIONEXCEPTION, "Stop Iteration");
    }
    std::ostringstream oss;
    oss << value[index];
    return new KPyStr(oss.str());
}
