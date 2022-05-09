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

// ---
static void terminate(int except, int pc, std::string name){
    throw new KPyException(
        except, "Terminating with exception in function " + name);
}

// ---
KPyObject* KPyFrame::safety_pop(){
    if(opstack->is_empty()){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Attempt to pop empty operand stack in " +
            code.get_instructions()[pc-1]->get_opcode_name()
        );
    }

    return opstack->pop();
}

// ---
std::string KPyFrame::get_cell_name(int index){
    std::string name;

    if(index < code.get_cellVars().size()){
        name = code.get_cellVars()[index];
    }else{
        if(index - code.get_cellVars().size() >= code.get_freeVars().size()){
            throw new KPyException(
                KPYILLEGALOPERATIONEXCEPTION,
                "Index value out of range on instruction."
            );
        }
        name = code.get_freeVars()[index - code.get_cellVars().size()];
    }

    return name;
}

// ---
KPyObject* KPyFrame::execute(){
    pc = 0;
    KPyObject *inst;
    KPyOpCode opcode;
    int operand;
    int i;
    KPyType *selftype;
    KPyCell *cell;
    KPyObject *u;
    KPyObject *v;
    KPyObject *w;
    KPyFunList *fnlist;
    KPyTuple *tuple;
    KPyObject *x;
    KPyObject *y;
    KPyObject *z;
    KPyBool *bu;
    bool handled = false;
    KPyCallable *fn;
    std::vector<KPyObject*>* args;
    std::vector<KPyObject*>::iterator iter;
    std::string name;

    // register this frame for the signal handler in case a signal occurs.
    push_frame(this);
    while(true){
        inst = code.get_instructions()[pc];
        pc++;
        opcode = inst->get_opcode();
        operand = inst->get_operand();
        try{
            switch(opcode){
            case KPyOpCode::LOAD_FAST:
                u = locals[code.get_locals()[operand]];
                if(u==0){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "LOAD_FAST failed to find value " +
                        code.get_locals()[operand]
                    );
                }
                opstack->push(u);
                break;
            case KPyOpCode::LOAD_CONST:
                u = consts[operand];
                opstack->push(u);
                break;

            case KPyOpCode::LOAD_GLOBAL:
                u = globals[code.get_globals()[operand]];
                if(u==0){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "LOAD_GLOBAL failed to find value " +
                        code.get_globals()[operand]
                    );
                }
                opstack->push(u);
                break;
            case KPyOpCode::STORE_FAST:
                u = safety_pop();
                locals[code.get_locals()[operand]] = u;
                break;
            case KPyOpCode::POP_TOP:
                u = safety_pop();
                break;
            case KPyOpCode::COMPARE_OP:
                v = safety_pop();
                u = safety_pop();
                args = new std::vector<KPyObject*>();
                args->push_back(v);
                w = u->call_method(richcomp[operand], args);
                try{ delete args; }
                catch(...){
                    std::cerr << "Delete of COMPARE_OP args caused "
                        << "an exception from some reason." << std::endl;
                }
                opstack->push(w);
                if(operand == 10){
                    handled = ((KPyBool*)w)->get_value();
                }
                break;
            case KPyOpCode::SETUP_LOOP:
                blockstack->push(operand);
                break;
            case KPyOpCode::BREAK_LOOP:
                pc = blockstack->pop();
                break;

            case KPyOpCode::POP_BLOCK:
                if(blockstack->is_empty()){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "Attempt to pop empty block stack."
                    );
                }
                blockstack->pop();
                break;
            case KPyOpCode::JUMP_FORWARD:
                pc = operand;
                break;
            case KPyOpCode::JUMP_ABSOLUTE:
                pc = operand;
                break;
            case KPyOpCode::POP_IF_TRUE:
                if(opstack->is_empty()){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "Attempt to pop empty operand stack in "
                        "POP_JUMP_IF_TRUE."
                    );
                }
                u = safety_pop();
                if(u->get_type()->to_string() != "bool"){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "Illegal TOS value for POP_JUMP_IF_TRUE. "
                        "Boolean value required."
                    );
                }
                bu = (KPyBool*)u;
                if(bu->get_value() == true){
                    pc = operand;
                }
                break;

            case KPyOpCode::POP_JUMP_IF_FALSE:
                if(opstack->is_empty()){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "Attempt to pop emty operand stack in "
                        "POP_JUMP_IF_FALSE."
                    );
                }
                u = safety_pop();
                if(u->get_type()->to_string() != "bool"){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "Illegal TOS value for POP_JUMP_IF_FALSE. "
                        "Boolean value required."
                    );
                }
                bu = (KPyBool*)u;
                if(bu->get_value() == false){
                    pc = operand;
                }
                break;

            case KPyOpCode::RETURN_VALUE:
                if(opstack->is_empty()){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "Attempt to pop empty operand stack in RETURN_VALUE."
                    );
                }
                u = safety_pop();
                pop_frame();
                return u;
                break;
            case KPyOpCode::BINARY_ADD:
            case KPyOpCode::INPLACE_ADD:
                v = safety_pop();
                u = safety_pop();
                args = new std::vector<KPyObject*>();
                args->push_back(v);
                w = u->call_method("__add__", args);
                opstack->push(w);
                try{ delete args;}
                catch(...){
                    std::cerr << "Delete of BINARY_ADD args caused "
                        << "an exception for some reason." << std::endl;
                }
                break;
            }
        }
    }
}
