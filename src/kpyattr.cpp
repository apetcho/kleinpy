#include"kleinpy.hpp"

using namespace kleinpy;

// ---
KPyAttr::KPyAttr(KPyObject *self, std::string method) : KPyCallable(){
    this->self = self;
    this->method = method;
}

// ---
KPyAttr::~KPyAttr(){
    try{ delete self;}
    catch(...){}
}

// ---
KPyType* KPyAttr::get_type(){
    return kpytypes[KPyTypeId::KPY_BUILTIN_TYPE];
}

// ---
KPyObject* KPyAttr::__call__(std::vector<KPyObject*>* args){
    return self->call_method(method, args);
}

// ---
std::string KPyAttr::to_string(){
    std::ostringstream ss;
    ss  << "<built-in method " << method << " of "
        << self->get_type()->to_string()
        << " object at " << this << ">";

    return ss.str();
}
