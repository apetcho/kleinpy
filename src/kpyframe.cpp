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

            case KPyOpCode::BINARY_SUBSTRACT:
                v = safety_pop();
                u = safety_pop();
                args = new std::vector<KPyObject*>();
                args->push_back(v);
                w = u->call_method("__sub__", args);
                opstack->push(w);
                try{ delete args; }
                catch(...){
                    std::cerr << "Delet of BINARY_SUBSTRACT args caused "
                        << "an exception for some reason." << std::endl;
                }
                break;

            case KPyOpCode::BINARY_MULTIPLY:
                v = safety_pop();
                u = safety_pop();
                args = new std::vector<KPyObject*>();
                args->push_back(v);
                w = u->call_method("__mul__", args);
                opstack->push(w);
                try{ delete args; }
                catch(...){
                    std::cerr << "Delet of BINARY_MULTIPLY args caused "
                        << "an exception for some reason." << std::endl;
                }
                break;

            case KPyOpCode::BINARY_TRUE_DIVIDE:
                v = safety_pop();
                u = safety_pop();
                args = new std::vector<KPyObject*>();
                args->push_back(v);
                w = u->call_method("__truediv__", args);
                opstack->push(w);
                try{ delete args; }
                catch(...){
                    std::cerr << "Delet of BINARY_TRuE_DIVIDE args caused "
                        << "an exception for some reason." << std::endl;
                }
                break;

            case KPyOpCode::BINARY_FLOOR_DIVIDE:
                v = safety_pop();
                u = safety_pop();
                args = new std::vector<KPyObject*>();
                args->push_back(v);
                w = u->call_method("__floordiv__", args);
                opstack->push(w);
                try{ delete args; }
                catch(...){
                    std::cerr << "Delet of BINARY_FLOOR_DIVIDE args caused "
                        << "an exception for some reason." << std::endl;
                }
                break;

            case KPyOpCode::GET_ITER:
                u = safety_pop();
                args = new std::vector<KPyObject*>();
                v = u->call_method("__iter__", args);
                opstack->push(v);
                try{ delete args; }
                catch(...){
                    std::cerr << "Delete of GET_ITER args caused "
                        << "an exception for some reason." << std::endl;
                }
                break;
            case KPyOpCode::ROT_TWO:
                u = safety_pop();
                v = safety_pop();
                opstack->push(u);
                opstack->push(v);
                break;

            case KPyOpCode::FOR_ITER:
                u = safety_pop();
                args = new std::vector<KPyObject*>();
                try{
                    v = u->call_method("__next__", args);
                    opstack->push(u);
                    opstack->push(v);
                }catch(KPyException *ex){
                    if(ex->get_exception_type() == KPYSTOPITERATIONEXCEPTION){
                        pc = operand;
                    }else{
                        throw ex;
                    }
                }
                try{ delete args; }
                catch(...){
                    std::cerr << "Delete of FOR_ITER args caused "
                        << "an exception for some reason." << std::endl;
                }
                break;

            case KPyOpCode::CALL_FUNCTION:
                args = new std::vector<KPyObject*>();
                for(i=0; i < operand; i++){
                    u = safety_pop();
                    args->push_back(u);
                }
                u = safety_pop();
                v = u->call_method("__call__", args);
                opstack->push(v);
                try{ delete args; }
                catch(...){
                    std::cerr << "Delete of CALL_FUNCTION args caused "
                        << "and exception for some reason." << std::endl;
                }
                break;

            case KPyOpCode::LOAD_ATTR:
                u = safety_pop);
                v = new KPyAttr(u, code.get_globals()[operand]);
                opstack->push(v);
                break;

            case KPyOpCode::BINARY_SUBSCR:
                u = safety_pop();
                v = safety_pop();
                args = new std::vector<KPyObject*>();
                args->push_back(u);

                w = v->call_method("__getitem__", args);
                opstack->push(w);
                delete args; //! @todo wrap this in a try .. catch block
                break;

            case KPyOpCode::STORE_SUBSCR:
                u = safety_pop();
                v = safety_pop();
                w = safety_pop();
                args = new std::vector<KPyObject*>();
                args->push_back(u); // the index
                args->push_back(w); // the item
                w = v->call_method("__setitem__", args);
                delete w;
                delete args;
                break;

            case KPyOpCode::LOAD_CLOSURE:
                name = get_cell_name(operand);
                opstack->push(cellVars[name]);
                break;

            case KPyOpCode::BUILD_TUPLE:
                args = new std::vector<KPyObject*>();
                for(i=0; i < operand; i++){
                    u = safety_pop();
                    iter = args->begin();
                    args->insert(iter, u);
                }
                opstack->push(new KPyTuple(args));
                break;

            case KPyOpCode::SELECT_TUPLE:
                u = safety_pop();
                if(u->get_type()->type_id() != KPyTypeId::KPY_TUPLE_TYPE){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "Attempt to select elements of a tuple from "
                        "non-tuple object."
                    );
                }
                tuple = (KPyTuple*)u;
                if(operand != tuple->size()){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "Attempt to select elements of a tuple with "
                        "incorrect size."
                    );
                }
                for(i=tuple->size()-1; i >= 0; i--){
                    opstack->push(tuple->get_value(i));
                }
                break;

            case KPyOpCode::BUILD_LIST:
                args = new std::vector<KPyObject*>();
                for(i=0; i < operand; i++){
                    u = safety_pop();
                    iter = args->begin();
                    args->insert(iter, u);
                }
                opstack->push(new KPyList(args));
                break;

            case KPyOpCode::BUILD_FUNLIST:
                args = new std::vector<KPyObject*>();
                for(i=0; i < operand; i++){
                    u = safety_pop();
                    iter = args->begin();
                    args->insert(iter, u);
                }
                opstack->push(new KPyFunList(args));
                break;

            case KPyOpCode::SELECT_FUNLIST:
                u = safety_pop();
                if(u->get_type()->type_id() != KPyTypeId::KPY_FUNLIST_TYPE){
                    throw new KPyException(
                        "Attempt to select elements of a funlist from "
                        "non-funlist object."
                    );
                }
                fnlist = (KPyFunList*)u;
                opstack->push(fnlist->get_tail());
                opstack->push(fnlist->get_head());
                break;

            case KPyOpCode::CONS_FUNLIST:
                u = safety_pop();
                v = safety_pop();
                if(u->get_type()->type_id() != KPyTypeId::KPY_FUNLIST_TYPE){
                    throw new KPyException(
                        "Attempt to construct a funlist without a funlist "
                        "tail."
                    );
                }
                fnlist = (KPyFunList*)u;
                opstack->push(new KPyFunList(v, fnlist));
                break;

            case KPyOpCode::MAKE_CLOSURE:
                u = safety_pop();
                v = safety_pop();
                w = new KPyFunction(*((KPyCode*)u), globals, v);
                opstack->push(w);
                break;

            case KPyOpCode::MAKE_FUNCTION:
                u = safety_pop();
                w = new KPyFunction(*((KPyCode*)u), globals, NULL);
                opstack->push(w);
                break;

            case KPyOpCode::STORE_DEREF:
                u = safety_pop();
                cell = cellVars[get_cell_name(operand)];
                cell->set(u);
                break;

            case KPyOpCode::LOAD_DEREF:
                cell = cellVars[get_cell_name(operand)];
                opstack->push(cell->deref());
                break;

            case KPyOpCode::SETUP_EXCEPT:
                blockstack->push(-1*operand);
                break;

            case KPyOpCode::RAISE_VARARGS:
                u = safety_pop();
                throw ((KPyException*)u);
                break;

            case KPyOpCode::DUP_TOP:
                if(opstack->is_empty()){
                    throw new KPyException(
                        KPYEMPTYSTACKEXCEPTION,
                        "Attempt to duplicate top entry of empty operand "
                        "stack."
                    );
                }
                opstack->push(opstack->top());
                break;

            case KPyOpCode::SETUP_FINALLY:
                blockstack->push(-1*operand);
                break;

            case KPyOpCode::END_FINALLY:
                if(!handled){
                    u = safety_pop();
                    v = safety_pop();
                    w = safety_pop();
                    blockstack->pop();
                    throw ((KPyException*)u);
                }
                break;

            case KPyOpCode::POP_EXCEPT:
                operand = blockstack->pop();
                if(operand > 0){
                    throw new KPyException(
                        KPYILLEGALOPERATIONEXCEPTION,
                        "Pop of block stack was for non-exception handling "
                        "block."
                    );
                }
                break;

            case KPyOpCode::DELETE_FAST:
                delete locals[code.get_locals()[operand]];
                break;

            default:
                throw new KPyException(
                    KPYILLEGALOPERATIONEXCEPTION,
                    "Unimplemented instruction: " + inst->get_opcode_name()
                );
            }
        }catch(KPyException *ex){
            int x;
            bool found = false;
            while(!found && !blockstack->is_empty()){
                x = blockstack->pop();
                if(x < 0){
                    found = true;
                    if(verbose){
                        std::cerr
                            << "*********************"
                            << "Handling Exception"
                            << "*********************" << std::endl;
                        std::cerr << "The exception was: "
                            <<  ex->to_string() << std::endl;
                        std::cerr << "--------------------------"
                            << "--------------------------------" << std::endl;
                        std::cerr << "            "
                            << "The Exception's Traceback" << std::endl;
                        std::cerr << "--------------------------"
                            << "--------------------------------" << std::endl;
                        ex->print_traceback();
                        std::cerr
                            << "*********************"
                            << "End Handling Exception"
                            << "*********************" << std::endl;

                        opstack->push(ex->get_traceback());
                        opstack->push(ex);
                        opstack->push(ex);
                        pc = -1 * x;
                        blockstack->push(0);
                    }
                }
                if(!found){
                    ex->traceback_append(this);
                    throw ex;
                }
            }
        }catch(...){
                KPyException *ex = new KPyException(
                    KPYILLEGALOPERATIONEXCEPTION,
                    "Unknown Error while executing instruction " +
                    inst->get_opcode_name()
                );
                ex->traceback_append(this);
                throw ex;
        }
    }
}

const KPyCode& KPyFrame::get_code() const {
    return code;
}
