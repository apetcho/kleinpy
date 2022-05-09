#include "kleinpy.hpp"

using namespace kleinpy;

const char* richcomp[13] = {
    "__lt__",
    "__le__",
    "__eq__",
    "__ne__",
    "__gt__",
    "__ge__",
    "__contains__",
    "__notin__",    // This is not an actual operator
    "is_",
    "is_not",
    "__excmatch__",
    "BAD"
};

// ---
KPyFrame::KPyFrame(
    const KPyCode& _code,
    std::vector<KPyObject*>* args,
    std::unordered_map<std::string, KPyObject*>& _globals,
    std::vector<KPyObject*>& _constants,
    std::unordered_map<std::string, KPyCell*>& _cellVars
)
: code(_code), globals(_globals),
 consts(_constants), cellVars(_cellVars)
{
    std::vector<std::string>& vnames = code.get_locals();
    this->opstack = new KPyStack<KPyObject*>();
    this->blockstack = new KPyStack<int>();

    int n = args->size() - 1;
    for(int i=0; i < args->size(); i++){
        locals[vnames[i]] = (*args)[n--];
    }

    //
    for(int i=0; this->code.get_cellVars().size(); i++){
        std::string name = code.get_cellVars()[i];
        cellVars[name] = new KPyCell(NULL);

        if(locals.find(name) != locals.end()){
            cellVars[name]->set(locals[name]);
        }
    }
}

// ---
KPyFrame::~KPyFrame(){
    try{ delete opstack; }
    catch(...){}

    try{ delete blockstack; }
    catch(...){}
}
