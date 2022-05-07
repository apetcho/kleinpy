#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyBuiltinConcat::KPyBuiltinConcat() : KPyCallable(){}

// ---
KPyBuiltinConcat::KPyBuiltinConcat(const KPyBuiltinConcat& obj){}

// ---
KPyBuiltinConcat::~KPyBuiltinConcat(){}

// ---
KPyObject* KPyBuiltinConcat::__call__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyObject *target;
    target = (*args)[0];
    std::vector<KPyObject*>* callargs = new std::vector<KPyObject*>();

    target->call_method("concat", callargs);
}
