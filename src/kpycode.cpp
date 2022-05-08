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

// ---
std::string KPyCode::get_name() const {
    return this->name;
}

// ---
std::vector<KPyCode*>& KPyCode::get_nestedFn() const {
    return *nestedFn;
}

// ---
std::vector<std::string>& KPyCode::get_locals() const {
    return *(this->locals);
}

// ---
std::vector<std::string>& KPyCode::get_freeVars() const {
    return *(this->freeVars);
}

// ---
std::vector<std::string>& KPyCode::get_cellVars() const {
    return *(this->cellVars);
}

// ---
std::vector<std::string>& KPyCode::get_globals() const {
    return *(this->globals);
}

// ---
std::vector<KPyObject*>& KPyCode::get_consts() const {
    return *(this->instructions);
}

// ---
std::vector<KPyByteCode*>& KPyCode::get_instructions() const {
    return *(this->instructions);
}

// ---
int KPyCode::get_nargs() const {
    return this->nargs;
}

// ---
int KPyCode::num_locals() const {
    return this->locals->size();
}
