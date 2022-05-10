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

// ---
int KPyToken::get_type() const { return toktype; }

// ---
std::string KPyToken::get_lex() const { return lex; }
