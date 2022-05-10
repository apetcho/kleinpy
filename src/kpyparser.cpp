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
