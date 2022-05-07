#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyBuiltinPrint::KPyBuiltinPrint() : KPyCallable(){}

// ---
KPyBuiltinPrint::KPyBuiltinPrint(const KPyBuiltinPrint& other){}

// ---
KPyBuiltinPrint::~KPyBuiltinPrint(){}


// ---
KPyType* KPyBuiltinPrint::get_type(){
    return kpytypes[KPyTypeId::KPY_BUILTIN_TYPE];
}

// ---
KPyObject* KPyBuiltinPrint::__call__(std::vector<KPyObject*>* args){
    std::string output = "";
    KPyObject *x;
    KPyObject* y;
    std::vector<KPyObject*>* strargs = new std::vector<KPyObject*>();

    for(int i=0; i < args->size(); i++){
        x = (*args)[i];
        y = x->call_method("__str__", strargs);
        output = y->to_string() + output;

        if(i < args->size()-1){
            output = " " + output;
        }
    }

    std::cout << output << std::endl;

    return new KPyNone();
}


// ---
std::string KPyBuiltinPrint::to_string(){
    return "print";
}
