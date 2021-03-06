#include "kleinpy.hpp"

using namespace kleinpy;

// ---
void bad_token(KPyToken *token, std::string message){
    std::cerr << "***********************************************" << std::endl;
    std::cerr << "           A Parse Exception Occurred          " << std::endl;
    std::cerr << "***********************************************" << std::endl;
    std::cerr << "Bad token '" << token->get_lex() << "' found at line "
        << token->get_lineno() << " and column " << token->get_colno()
        << "." << std::endl;
    std::cerr << "Token type was " << token->get_type() << "." << std::endl;
    std::cerr << message << std::endl;
    std::exit(0);
}

// ---
std::vector<KPyCode*>* KPyParser::parse(){
    try{
        return pyassembly_prog();
    }catch(KPyException *ex){
        input->put_back_token();
        KPyToken *token = input->get_token();
        std::cerr << "*****************************************" << std::endl;
        std::cerr << "         A Parse Exception occured       " << std::endl;
        std::cerr << "*****************************************" << std::endl;
        std::cerr << "The exception occurred at line " << token->get_lineno()
            << " and column " << token->get_colno() << "." << std::endl;
        std::cerr << "The exception was: " << ex->to_string() << std::endl;
        std::exit(0);
    }
}

// ---
KPyParser::KPyParser(std::string filename){
    std::istream *stream = new std::ifstream(filename);
    this->input = new KPyScanner(stream);
}

// ---
KPyParser::KPyParser(const KPyParser& other){
    this->input = other.input;
}

// ---
KPyParser::~KPyParser(){
    try{ delete input; }
    catch(...){}
}

// ---
std::vector<KPyCode*>* KPyParser::pyassembly_prog(){
    std::vector<KPyCode*>* code = functionlist_part();
    KPyToken *token = input->get_token();

    if(token->get_type() != KPYEOFTOKEN){
        bad_token(token, "Expected End Of File marker.");
    }

    return code;
}

// ---
std::vector<KPyCode*>* KPyParser::functionlist_part(){
    KPyCode *code = fundef();
    std::vector<KPyCode*>* vec = new std::vector<KPyCode*>();
    vec->push_back(code);
    vec = functionlist(vec);

    return vec;
}

// ---
std::vector<KPyCode*>* KPyParser::functionlist(std::vector<KPyCode*>* vec){
    KPyToken *token = input->get_token();
    input->put_back_token();

    if(token->get_lex() == "Function"){
        KPyCode *code = fundef();
        vec->push_back(code);
        vec = functionlist(vec);
    }

    return vec;
}

// ---
KPyCode* KPyParser::fundef(){
    KPyToken *token = input->get_token();

    if(token->get_lex() != "Function"){
        bad_token(token, "Expected Function keyword.");
    }

    token = input->get_token();
    if(token->get_lex() != ":"){
        bad_token(token, "Expected a colon.");
    }

    KPyToken *funname = input->get_token();
    if(funname->get_type() != KPYINDENTIFIERTOKEN){
        bad_token(funname, "Expected an identifier.");
    }

    token = input->get_token();

    if(token->get_lex() != "/"){
        bad_token(token, "Expected a '/'");
    }

    KPyToken *nargstok = input->get_token();
    int numargs;

    if(nargstok->get_type() != KPYINTEGERTOKEN){
        bad_token(nargstok, "Expected an integer for the argument count.");
    }

    std::istringstream nargin(nargstok->get_lex(), std::istringstream::in);
    nargin.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    nargin >> numargs;

    std::vector<KPyCode*>* nestedFuncs = new std::vector<KPyCode*>();
    nestedFuncs = functionlist(nestedFuncs);

    std::vector<KPyObject*>* constants = const_part(nestedFuncs);
    std::vector<std::string>* locals = locals_part();
    std::vector<std::string>* freeVars = freeVars_part();
    std::vector<std::string>* cellVars = cellVars_part();
    std::vector<std::string>* globals = globals_part();

    std::vector<KPyByteCode*>* instructions = body_part();

    return new KPyCode(
        funname->get_lex(), nestedFuncs, constants, locals,
        freeVars, cellVars, globals, instructions, numargs
    );
}

// ---
std::vector<KPyObject*>* KPyParser::const_part(
    std::vector<KPyCode*>* nestedFuns
){
    std::vector<KPyObject*>* constants = new std::vector<KPyObject*>();
    KPyToken *token = input->get_token();

    if(token->get_lex() != "Constants"){
        input->put_back_token();
        return constants;
    }

    token = input->get_token();
    if(token->get_lex() != ":"){
        bad_token(token, "Expected a ':'.");
    }

    constants = value_list(constants, nestedFuns);

    return constants;
}

// ---
std::vector<KPyObject*>* KPyParser::value_list(
    std::vector<KPyObject*>* constants, std::vector<KPyCode*>* nestedFuncs
){
    KPyObject *value = value(nestedFuncs);
    constants->push_back(value);
    constants = value_rest(constants, nestedFuncs);
    return constants;
}

// ---
std::vector<KPyObject*>* KPyParser::value_rest(
    std::vector<KPyObject*>* constants, std::vector<KPyCode*>* nestedFuns
){
    KPyToken *token = input->get_token();

    if(token->get_lex() != ","){
        input->put_back_token();
        return constants;
    }

    return value_list(constants, nestedFuns);
}

// ---
KPyObject* KPyParser::value(std::vector<KPyCode*>* nestedFuncs){
    int ival;
    float fval;
    std::string sval;
    KPyToken *codeID;
    std::istringstream *tokstrm;

    KPyToken *token = input->get_token();
    switch(token->get_type()){
    case KPYINTEGERTOKEN:
        tokstrm = new std::istringstream(token->get_lex());
        tokstrm->exceptions(std::ios_base::failbit | std::ios_base::badbit);
        (*tokstrm) >> ival;
        delete tokstrm;
        return new KPyInt(ival);
        break;
    case KPYFLOATTOKEN:
        tokstrm = new std::istringstream(token->get_lex());
        tokstrm->exceptions(std::ios_base::failbit | std::ios_base::badbit);
        (*tokstrm) >> fval;
        delete tokstrm;
        return new KPyFloat(fval);
        break;
    case KPYSTRINGTOKEN:
        sval = token->get_lex();
        return new KPyStr(sval);
        break;
    case KPYINDENTIFIERTOKEN:
        if(token->get_lex() == "None"){ return new KPyNone(); }
        else if(token->get_lex() == "True"){ return new KPyBool(true); }
        else if(token->get_lex() == "False"){ return new KPyBool(); }
        else if(token->get_lex() == "code"){
            token = input->get_token();
            if(token->get_lex() != "("){ bad_token(token, "Expected a '('."); }
            codeID = input->get_token();
            if(codeID->get_type() != KPYINDENTIFIERTOKEN){
                bad_token(token, "Expected an identifier.");
            }
            token = input->get_token();
            if(token->get_lex() != ")" ){
                bad_token(token, "Expected a ')'.");
            }
            for(int i=0; i < nestedFuncs->size(); i++){
                KPyCode *code = (*nestedFuncs)[i];
                if(code->get_name() == codeID->get_lex()){ return code; }
            }
            std::cerr << "Identifier " << codeID->get_lex()
                << " is not a nested function. " << std::endl;
            bad_token(codeID, "Must be name of inner function.");
        }else{
            bad_token(token, "Expected None, int, float, str, True or False.");
        }
    default:
        bad_token(token, "Expected None, int, float, str, True, or False.");
        break;
    }

    return nullptr;
}

// ---
std::vector<std::string>* KPyParser::locals_part(){
    std::vector<std::string>* locals = new std::vector<std::string>();
    KPyToken *token = input->get_token();

    if(token->get_lex() != "Locals"){
        input->put_back_token();
        return locals;
    }

    token = input->get_token();
    if(token->get_lex() != ":"){
        bad_token(token, "Expected a ':'.");
    }
    return idlist(locals);
}

// ---
std::vector<std::string>* KPyParser::freeVars_part(){
    std::vector<std::string>* freeVars = new std::vector<std::string>();
    KPyToken *token = input->get_token();

    if(token->get_lex() != "FreeVars"){
        input->put_back_token();
        return freeVars;
    }

    token = input->get_token();
    if(token->get_lex() != ":"){
        bad_token(token, "Expected a ':'.");
    }

    return idlist(freeVars);
}

// ---
std::vector<std::string>* KPyParser::cellVars_part(){
    std::vector<std::string>* cellVars = new std::vector<std::string>();

    KPyToken *token = input->get_token();

    if(token->get_lex() != "CellVars"){
        input->put_back_token();
        return cellVars;
    }

    token = input->get_token();
    if(token->get_lex() != ":"){
        bad_token(token, "Expected a ':'.");
    }

    return idlist(cellVars);
}

// ---
std::vector<std::string>* KPyParser::idlist(std::vector<std::string>* xlist){
    KPyToken *token = input->get_token();

    if(token->get_type() != KPYINDENTIFIERTOKEN){
        bad_token(token, "Expected an identifier.");
    }

    xlist->push_back(token->get_lex());

    return idrest(xlist);
}

// ---
std::vector<std::string>* KPyParser::idrest(std::vector<std::string> *xlist){
    KPyToken *token = input->get_token();

    if(token->get_type() != KPYCOMMATOKEN){
        input->put_back_token();
        return xlist;
    }

    return idlist(xlist);
}


// ---
std::vector<std::string>* KPyParser::globals_part(){
    std::vector<std::string> *globals = new std::vector<std::string>();

    KPyToken *token = input->get_token();

    if(token->get_lex() != "Globals"){
        input->put_back_token();
        return globals;
    }

    token = input->get_token();
    if(token->get_lex() != ":"){
        bad_token(token, "Expected a ':'.");
    }

    return idlist(globals);
}

// ---
std::vector<KPyByteCode*>* KPyParser::body_part(){
    std::vector<KPyByteCode*>* instructions = new std::vector<KPyByteCode*>();

    KPyToken *token = input->get_token();
    target.clear();
    index = 0;

    if(token->get_lex() != "BEGIN"){
        bad_token(token, "Expected a BEGIN keyword.");
    }

    instructions = instruction_list(instructions);
    for(int i=0; i < instructions->size(); i++){
        KPyByteCode *inst = (*instructions)[i];
        std::string label = inst->get_label();
        if(label != ""){
            std::string op = inst->get_opcode_name();
            (*instructions)[i] = new KPyByteCode(op, target[label]);
        }
    }

    token = input->get_token();

    if(token->get_lex() != "END"){
        bad_token(token, "Expected a END keyword.");
    }

    return instructions;
}

// ---
std::vector<KPyByteCode*>* KPyParser::instruction_list(
    std::vector<KPyByteCode*>* instructions
){
    KPyToken *token = input->get_token();
    input->put_back_token();

    if(token->get_lex() == "END"){
        return instructions;
    }

    KPyByteCode *inst = labeled_instructions();

    instructions->push_back(inst);
    index++;

    return instruction_list(instructions);
}

// ---
KPyByteCode* KPyParser::labeled_instructions(){
    KPyToken *tok1 = input->get_token();
    std::string tok1lex = tok1->get_lex();

    KPyToken *tok2 = input->get_token();
    std::string tok2lex = tok2->get_lex();

    if(tok2lex == ":"){
        if(target.find(tok1lex) == target.end()){
            target[tok1lex] = index;
        }else{
            bad_token(tok1, "Duplicate label found.");
        }
        return labeled_instructions();
    }

    int argcount = 0;
    try{
        argcount = KPyByteCode::nargs(tok1lex);
    }catch(int e){
        bad_token(tok1, "Illegal opcode.");
    }

    if(argcount == 0){
        input->put_back_token();
        return new KPyByteCode(tok1lex);
    }

    if(tok2->get_type() == KPYINDENTIFIERTOKEN){
        try{
            return new KPyByteCode(tok1lex, tok2lex);
        }catch(int e){
            bad_token(tok2, "Illegal opcode.");
        }
    }

    if(tok2->get_type() == KPYINTEGERTOKEN){
        try{
            int operand;
            std::stringstream(tok2lex) >> operand;
            return new KPyByteCode(tok1lex, operand);
        }catch(int e){
            bad_token(tok1, "Illegal opcode.");
        }
    }

    bad_token(tok1, "Instruction Syntax Error.");

    return nullptr;
}
