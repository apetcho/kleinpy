#include "kleinpy.hpp"

using namespace kleinpy;

KPyExceptionType::KPyExceptionType(std::string typestr, KPyTypeId id)
: KPyType(typestr, id)
{}

// ---
KPyExceptionType::~KPyExceptionType(){}
