#include<functional>
#include "kleinpy.hpp"

using namespace kleinpy;
// ---
std::ostream& operator<<(
    std::ostream& strm, KPyObject kpyObj){
    strm << kpyObj.to_string();
    return strm;
}

// ----
KPyObject* KPyObject::call_method(
    std::string name, std::vector<KPyObject*>* args
){
    KPyObject* (KPyObject::*fun)(std::vector<KPyObject*>*);
    if(dict.find(name) == dict.end()){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "TypeError: '" + get_type()->to_string() + 
            "' object has no attribute '" + name + "'"
        );
    }
    fun = dict[name];

    return (this->*fun)(args);
}


// --
KPyObject::KPyObject(){
    dict["__str__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyObject::__str__
    );
    dict["__type__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyObject::__type__
    );
}

// ---
KPyObject::~KPyObject(){}

// ---
KPyType* KPyObject::get_type(){
    return NULL;
}

// --
void KPyObject::incref(){ refcount++; }

// --
void KPyObject::decref(){ refcount--; }

// --
int KPyObject::get_refcount() const { return refcount; }

// --
KPyObject* KPyObject::__str__(std::vector<KPyObject*>* args){
    std::ostringstream message;
    if(args->size() != 0){
        message << "TypeError: excepted 0 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, message.str());
    }

    return new KPyStr(to_string());
}

// ---
KPyObject* KPyObject::__type__(std::vector<KPyObject*>* args){
    std::ostringstream message;
    if(args->size() != 0){
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, message.str());
    }

    return (KPyObject*)this->get_type();
}
