#include "kleinpy.hpp"

using namespace kleinpy;

KPyExceptionType::KPyExceptionType(std::string typestr, KPyTypeId id)
: KPyType(typestr, id)
{}

// ---
KPyExceptionType::~KPyExceptionType(){}

// ---
KPyObject* KPyExceptionType::__call__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    int exctype;

    if(args->size() > 2){
        oss << "TypeError: excepted 1 or 2 arguments, got " << args->size();
        throw new KPyExceptionType(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    if(args->size() == 1){
        return new KPyException(KPYEXCEPTION, (*args)[0]);
    }

    if((*args)[0]->get_type()->type_id() != KPyTypeId::KPY_INT_TYPE){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "TypeError: excepted in for first argument ot Exception."
        );
    }
    exctype = ((KPyInt*)(*args)[0])->get_value();

    return new KPyException(exctype, (*args)[1]);
}
