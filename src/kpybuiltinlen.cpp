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

// // ---
// KPyObject* KPyBuiltinIter::__call__(std::vector<KPyObject*>* args){
//     std::vector<KPyObject*>* iterargs = new std::vector<KPyObject*>();
//     KPyObject *obj;
//     std::ostringstream oss;

//     if(args->size() != 1){
//         oss << "TypeError: expected 1 argument, got " << args->size();
//         throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
//     }

//     obj = (*args)[0];
//     KPyObject *result = obj->call_method("__iter__", iterargs);

//     return result;
// }


// // ---
// std::string KPyBuiltinIter::to_string(){
//     return "iter";
// }
