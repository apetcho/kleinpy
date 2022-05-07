#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyBuiltinTPrint::KPyBuiltinTPrint() : KPyCallable(){}

// ---
KPyBuiltinTPrint::KPyBuiltinTPrint(const KPyBuiltinTPrint& other){}

// ---
KPyBuiltinTPrint::~KPyBuiltinTPrint(){}

// ---
KPyType* KPyBuiltinTPrint::get_type(){
    return kpytypes[KPyTypeId::KPY_BUILTIN_TYPE];
}

// ---
static std::string process_args(std::string text){
    std::ostringstream oss;
    bool escape = false;

    for(int i=0; i < text.size(); i++){
        if(escape){
            switch(text[i]){
            case 'n':
                oss << "\n";
                break;
            case 't':
                oss << "\t";
                break;
            default:
                oss << text[i];
                break;
            }
            escape = false;
        }else{
            escape = (text[i] == '\\');
            if(!escape){ oss << text[i]; }
        }
    }

    return oss.str();
}

// ---
KPyObject* KPyBuiltinTPrint::__call__(std::vector<KPyObject*>* args){
    std::string output = "";
    KPyObject *x;
    KPyObject *y;
    std::vector<KPyObject*>* strargs = new std::vector<KPyObject*>();
    std::ostringstream oss;

    if(args->size() != 1){
        oss << "TypeError: expected 1 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyObject *arg = (*args)[0];

    if(arg->get_type()->type_id() == KPyTypeId::KPY_TUPLE_TYPE){
        KPyTuple *atuple = (KPyTuple*)arg;
        for(int i= atuple->size() - 1; i >= 0; i--){
            x = atuple->get_value(i);
            y = x->call_method("__str__", strargs);
            if(x->get_type()->type_id() == KPyTypeId::KPY_STR_TYPE){
                output = process_args(y->to_string()) + output;
            }else{
                output = y->to_string() + output;
            }

            if(i > 0){ output = " " + output; }
        }
    }else{
        output = arg->to_string();
    }
    std::cout << output << std::endl;

    return new KPyNone();
}

// ---
std::string KPyBuiltinTPrint::to_string(){
    return "tprint";
}
