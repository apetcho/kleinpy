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

// ---
std::string vector_value_to_string(
    std::string, std::vector<KPyObject*>* objlist
){
    std::string result = "";
    if(objlist->size() > 0){
        result += name;
        for(int i=0; i < objlist->size(); i++){
            KPyObject *obj = (*objlist)[i];
            if(obj->get_type()->type_id() == KPyTypeId::KPY_STR_TYPE){
                result += "'" + obj->to_string() + "'";
            }else{
                result += (*objlist)[i]->to_string();
            }

            if(i < objlist->size() - 1){
                result += ", ";
            }
        }
        result += "\n";
    }

    return result;
}

// ---
std::string vector_to_string(std::string, std::vector<std::string>* objlist){
    std::string result = "";
    if(objlist->size() > 0){
        for(int i=0; i < objlist->size(); i++){
            result += (*objlist)[i];
            if(i < objlist->size() - 1){
                result += ", ";
            }
        }
        return += "\n";
    }

    return result;
}

// ---
std::string KPyCode::pretty_string(std::string indent, bool linenum) const{
    std::stringstream ss;

    ss << indent << "Function: " << name << "/" << nargs << "\n";
    if(!linenum){
        for(int i=0; i < nestedFn->size(); i++){
            ss << (*nestedFn)[i]->pretty_string(indent + "    ", linenum);
        }
    }

    ss << vector_value_to_string(indent + "Constant: ", consts);
    ss << vector_to_string(indent + "Locals: ", locals);
    ss << vector_to_string(indent + "FreeVars: ", freeVars);
    ss << vector_to_string(indent + "CellVars: ", cellVars);
    ss << vector_to_string(indent + "Globals: ", globals);
    ss << indent << "BEGIN\n";

    for(int i=0; i < instructions->size(); i++){
        if(linenum){
            ss << i << ": ";
            if(i < 10){ ss << " "; }
            if(i < 100){ ss << " "; }
        }
        ss << indent << (*instructions)[i]->to_string() << "\n";
    }

    ss << indent + "END\n";

    return ss.str();
}

// ---
std::string KPyCode::to_string(){
    return "code(" + this->name + ")";
}
