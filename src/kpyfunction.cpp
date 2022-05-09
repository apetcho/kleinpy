#include "kleinpy.hpp"

using namespace kleinpy;

KPyFunction::KPyFunction(
    KPyCode& _code,
    std::unordered_map<std::string, KPyObject*>& _globals, KPyObject *env
) : KPyCallable(), code(_code), globals(_globals)
{
    KPyTuple *tuple = (KPyTuple*)env;
    for(int i=0; i < _code.get_freeVars().size(); i++){
        cellVars[_code.get_freeVars()[i]] = (KPyCell*)tuple->get_value(i);
    }
}

// ---
KPyFunction::~KPyFunction(){}

// ---
KPyObject* KPyFunction::__call__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != code.get_nargs()){
        oss << "TypeError: expected " << code.get_nargs() 
            << " arguments, got " << args->size() << " for function "
            << code.get_name();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyFrame *frame = new KPyFrame(
        code, args, globals, code.get_consts(), cellVars
    );

    KPyObject *result = frame->execute();
    try{ delete frame; }
    catch(...){
        std::cerr << "Frame deletion caused an exception for "
            << "some reason." << std::endl;
    }

    return result;
}
