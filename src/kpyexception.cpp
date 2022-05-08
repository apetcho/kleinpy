#include "kleinpy.hpp"

using namespace kleinpy;

// ---
struct names{
    static std::unordered_map<int, std::string> create_map(){
        std::unordered_map<int, std::string> exceptmap;
        exceptmap[KPYEXCEPTION] = "Exception";
        exceptmap[KPYEMPTYSTACKEXCEPTION] = "EmptyStackException";
        exceptmap[KPYPARSEEXCEPTION] = "ParseException";
        exceptmap[KPYILLEGALOPERATIONEXCEPTION] = "IllegalOperatonException";
        exceptmap[KPYWRONGARGCOUNTEXCEPTION] = "WrongArgCountException";
        exceptmap[KPYSTOPITERATIONEXCEPTION] = "StopIterationException";
        exceptmap[KPYMATCHEXCEPTION] = "MatchException";

        return exceptmap;
    }
};

static std::unordered_map<int, std::string> exceptmap = names::create_map();

// ---

KPyException::KPyException(int except, KPyObject *obj)
    : KPyObject(), exceptionType(except), value(obj)
{
    dict["__excmatch__"] = (KPyObject * (KPyObject::*)(std::vector<KPyObject))(
        &KPyException::__excmatch__
    );
}

// ---
KPyException::KPyException(int except, std::string msg)
: KPyObject(), exceptionType(except), value(new KPyStr(msg))
{
    dict["__excmatch__"]=(KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyException::__excmatch__
    );
}


// ---
KPyException::~KPyException(){
    try{ delete value; }
    catch(...){}
}

// ---
int KPyException::get_exception_type(){
    return exceptionType;
}

// ---
std::string KPyException::to_string(){
    return value->to_string();
}

// ---
KPyType* KPyException::get_type(){
    return kpytypes[KPyTypeId::KPY_EXCEPTION_TYPE_ID];
}
