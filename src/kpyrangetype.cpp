#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyRangeType::KPyRangeType(std::string typestr, KPyTypeId id) 
: KPyType(typestr, id){}

// ---
KPyRangeType::~KPyRangeType(){}

// ---
KPyObject* KPyRangeType::__call__(std::vector<KPyObject*>* args){
    int start, stop, increment;

    switch(args->size()){
    case 1:
        if((*args)[0]->get_type()->type_id() != KPyTypeId::KPY_INT_TYPE){
            throw new KPyException(
                KPYILLEGALOPERATIONEXCEPTION,
                "range arguments must of int type."
            );
        }
        start = 0;
        stop = ((KPyInt*)((*args)[0]))->get_value();
        increment = 1;
        break;
    case 2:
        if((*args)[0]->get_type()->type_id() != KPyTypeId::KPY_INT_TYPE){
            throw new KPyException(
                KPYILLEGALOPERATIONEXCEPTION,
                "range arguments must be of int type."
            );
        }
        if((*args)[1]->get_type()->type_id() != KPyTypeId::KPY_INT_TYPE){
            throw new KPyException(
                KPYILLEGALOPERATIONEXCEPTION,
                "range arguments must be of int type."
            );
        }
        start = ((KPyInt*)((*args)[1]))->get_value();
        stop = ((KPyInt*)((*args)[0]))->get_value();
        increment = 1;
        break;
    case 3:
        if((*args)[0]->get_type()->type_id() != KPyTypeId::KPY_INT_TYPE){
            throw new KPyException(
                KPYILLEGALOPERATIONEXCEPTION,
                "range arguments must be of int type."
            );
        }
        if((*args)[1]->get_type()->type_id() != KPyTypeId::KPY_INT_TYPE){
            throw new KPyException(
                KPYILLEGALOPERATIONEXCEPTION,
                "range arguments must be of int type."
            );
        }
        if((*args)[2]->get_type()->type_id() != KPyTypeId::KPY_INT_TYPE){
            throw new KPyException(
                KPYILLEGALOPERATIONEXCEPTION,
                "range arguments must be of int type."
            );
        }
        start = ((KPyInt*)((*args)[2]))->get_value();
        stop = ((KPyInt*)((*args)[1]))->get_value();
        increment = ((KPyInt*)((*args)[0]));
        break;
    default:
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Incorrect number of arguments for built-in range function."
        );
        break;
    }

    return new KPyRange(start, stop, increment);
}
