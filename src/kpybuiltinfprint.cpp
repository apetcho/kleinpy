#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyBuiltinFPrint::KPyBuiltinFPrint() : KPyCallable(){}

// ---
KPyBuiltinFPrint::KPyBuiltinFPrint(const KPyBuiltinFPrint& other){}

// ---
KPyBuiltinFPrint::~KPyBuiltinFPrint(){}

// ---
KPyType* KPyBuiltinFPrint::get_type(){
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
            if(!escape){
                oss << text[i];
            }
        }
    }

    return oss.str();
}

KPyObject* KPyBuiltinFPrint::__call__(std::vector<KPyObject*>* args){
    std::string output = "";
    KPyObject *x;
    KPyObject *w;
    std::vector<KPyObject*>* txtargs = new std::vector<KPyObject*>();
    std::ostringstream oss;

    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyObject *arg = (*args)[0];
    if(arg->get_type()->type_id() == KPyTypeId::KPY_STR_ITERATOR_TYPE){
        output = process_args(output);
    }
    std::cout << output;

    return this;
}

// ---
std::string KPyBuiltinFPrint::to_string(){
    return "fprint";
}
