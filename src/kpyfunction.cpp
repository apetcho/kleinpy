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
