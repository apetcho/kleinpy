#include<functional>
#include "kleinpy.hpp"

using namespace kleinpy;
// ---
std::ostream& operator<<(
    std::ostream& strm, KPyObject kpyObj){
    strm << kpyObj.to_string();
    return strm;
}

// ----
KPyObject* KPyObject::call_method(
    std::string name, std::vector<KPyObject*>* args
){
    KPyObject* (KPyObject::*fun)(std::vector<KPyObject*>*);
    if(dict.find(name) == dict.end()){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "TypeError: '" + get_type()->to_string() + 
            "' object has no attribute '" + name + "'"
        );
    }
    fun = dict[name];

    return (this->*fun)(args);
}


// --
KPyObject::KPyObject(){
    dict["__str__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyObject::__str__
    );
    dict["__type__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyObject::__type__
    );
}
