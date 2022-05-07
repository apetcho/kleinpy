#include"kleinpy.hpp"

using namespace kleinpy;

// ---
KPyAttr::KPyAttr(KPyObject *self, std::string method) : KPyCallable(){
    this->self = self;
    this->method = method;
}
