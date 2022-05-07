#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyBuiltinLen::KPyBuiltinLen() : KPyCallable(){}

// ---
KPyBuiltinLen::KPyBuiltinLen(const KPyBuiltinLen& other){}

// // ---
KPyBuiltinLen::~KPyBuiltinLen(){}


// // ---
KPyType* KPyBuiltinLen::get_type(){
     return kpytypes[KPyTypeId::KPY_BUILTIN_TYPE];
}

// ---
KPyObject* KPyBuiltinLen::__call__(std::vector<KPyObject*>* args){
    KPyObject *obj;
    std::ostringstream oss;

    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    obj = (*args)[0];
    std::vector<KPyObject*>* callargs = new std::vector<KPyObject*>();
    KPyObject *result = obj->call_method("__len__", callargs);

    return result;
}


// ---
std::string KPyBuiltinLen::to_string(){
    return "len";
}
