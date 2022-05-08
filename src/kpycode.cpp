#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyCode::KPyCode(
    std::string name, std::vector<KPyCode*>* nestedFn,
    std::vector<KPyObject*>* consts, std::vector<std::string>* locals,
    std::vector<std::string>* freeVars, std::vector<std::string>* cellVars,
    std::vector<std::string>* globals, std::vector<KPyByteCode*>* code,
    int argcount
) : KPyObject(){
    this->name = name;
    this->locals = locals;
    this->freeVars = freeVars;
    this->cellVars = cellVars;
    this->globals = globals;
    this->consts = consts;
    this->instructions = code;
    this->nargs =  argcount;
    this->nestedFn = nestedFn;
}

// ---
KPyCode::~KPyCode(){
    try{ delete nestedFn; }
    catch(...){}

    try{ delete instructions; }
    catch(...){}

    try{ delete consts; }
    catch(...){}

    try{ delete globals; }
    catch(...){}

    try{ delete cellVars; }
    catch(...){}

    try{ delete freeVars; }
    catch(...){}

    try{ delete locals; }
    catch(...){}
}