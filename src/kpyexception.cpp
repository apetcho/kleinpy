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

// ---
void KPyException::print_traceback(){
    for(int i=0; i < traceback.size(); i++){
        std::cerr << "============> At PC=" << (traceback[i]->get_pc()-1)
            << " in this function. " << std::endl;
        std::cerr << traceback[i]->get_code().pretty_string("", true);
    }
}

// ---
void KPyException::traceback_append(KPyFrame *frame){
    traceback.push_back(frame);
}


// ---
KPyObject* KPyException::__excmatch__(std::vector<KPyObject*>* args){
    std::ostringstream oss;

    if(args->size() != 1){
        oss << "TypeError: expected 1 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyObject *arg = (*args)[0];

    // ---
    if(this->get_type() == arg){
        return new KPyBool(true);
    }

    // ---
    if(this->get_type() != arg->get_type()){
        oss << "TypeError: Exception match type mismatch. Expected Exception"
            << " Object got " << arg->to_string();

        throw new KPyException(KPYILLEGALOPERATIONEXCEPTION, oss.str());
    }

    KPyException *other = (KPyException*)arg;

    return new KPyBool(this->get_exception_type()==other->get_exception_type());
}

// ---
KPyObject* KPyException::get_traceback(){
    return new KPyList((std::vector<KPyObject*>*)&traceback);
}
