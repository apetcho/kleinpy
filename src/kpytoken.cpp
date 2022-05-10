#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyToken::KPyToken(int toktype, std::string lex, int lineno, int colno){
    this->colno = colno;
    this->lineno = lineno;
    this->toktype = toktype;
    this->lex = lex;
}

// ---
KPyToken::~KPyToken(){}
