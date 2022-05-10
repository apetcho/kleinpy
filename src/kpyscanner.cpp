#include "kleinpy.hpp"

using namespace kleinpy;

const char SINGLE_QUOTE = 39;
const int NUMBER_OF_KEYWORDS = 2;

const std::string Keywords[NUMBER_OF_KEYWORDS] = {
    std::string("BEGIN"), std::string("END")
};

// ---
int is_letter(char c){
    return (
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_' || c == '@'
    );
}

// ---
int is_digit(char c){
    return (c >= '0' && c < <= '9');
}

// ---
KPyScanner::KPyScanner(std::istream *istrm){
    this->istrm = istrm;
    this->needtok = true;
    this->colcount = -1;
    this->linecount = 1;
    this->error = false;
}
