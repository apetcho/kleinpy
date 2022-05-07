#include"kleinpy.hpp"

using namespace kleinpy;

// ---
KPyBuiltinInput::KPyBuiltinInput() : KPyCallable(){}

// ---
KPyBuiltinInput::KPyBuiltinInput(const KPyBuiltinInput& other){}

// ---
KPyBuiltinInput::~KPyBuiltinInput(){}

// ---
KPyType* KPyBuiltinInput::get_type(){
    return kpytypes[KPyTypeId::KPY_BUILTIN_TYPE];
}

// ---
KPyObject* KPyBuiltinInput::__call__(std::vector<KPyObject*>* args){
    KPyObject *x;
    KPyObject *y;
    std::string output;
    char buffer[256];
    std::ostringstream oss;

    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    x = (*args)[0];
    if(x->get_type()->type_id() != KPyTypeId::KPY_STR_TYPE){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Invalid argument to input(): excpected str, found " + 
            x->get_type()->to_string()
        );
    }

    y = (KPyStr*)x;
    std::cout << y->to_string();

    std::ostringstream out;

    std::cin.getline(buffer, 256);
    while(std::cin.gcount() == 255){
        out << buffer;
        std::cin.getline(buffer, 256);
    }
    out << buffer;

    return new KPyStr(out.str());
}

// ---
std::string KPyBuiltinInput::to_string(){
    return "input";
}
