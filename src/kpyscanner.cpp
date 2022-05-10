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
int is_white_space(char c){
    return (c == ' ' || c == '\t' || c == '\n');
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

// ---
KPyScanner::~KPyScanner(){
    try{ delete istrm; }
    catch(...){}
}

// ---
KPyToken* KPyScanner::get_token(){
    if(!needtok){
        needtok = true;
        return lasttok;
    }

    KPyToken *token;
    int state = 0;
    bool foundOne = false;
    char c;
    std::string lex;
    int type;
    int k;
    int column, line;

    c = istrm->get();
    while(!foundOne){
        colcount++;
        switch(state){
        case 0:
            lex = "";
            column = colcount;
            line = linecount;
            if(is_letter(c)){ state = 1; }
            else if(is_digit(c)) { state = 2; }
            else if(c == '-'){ state = 11: }
            else if(c == ':'){ state = 3; }
            else if(c == ','){ state = 4; }
            else if(c == SINGLE_QUOTE){ state = 6; }
            else if(c == '"'){ state = 7; }
            else if(c == '/'){ state = 8; }
            else if(c == '('){ state = 9; }
            else if(c == ')'){ state = 10; }
            else if(c =0 ';'){ state = 12; }
            else if(c == -1){
                foundOne = true;
                type = KPYEOFTOKEN;
            }else if(c == '\n'){
                colcount = -1;
                linecount++;
            }else if(is_white_space(c)){}
            else if (istrm->eof()){
                foundOne = true;
                type = KPYEOFTOKEN;
            }else{
                if(!error){
                    std::cerr << "Unrecognized character '" << c
                        << "' found at line " << line << " and column "
                        << column << std::endl;
                    error = true;
                }
                type = KPYBADTOKEN;
                lex = c;
                foundOne = true;
            }
            break;
        case 1:
            if(is_letter(c) || is_digit(c)){ state = 1; }
            else{
                for(k=0; k < NUMBER_OF_KEYWORDS; k++){
                    if(lex == Keywords[k]){
                        foundOne = true;
                        type = KPYKEYWORDTOKEN;
                    }
                }
                if(!foundOne){
                    type = KPYINDENTIFIERTOKEN;
                    foundOne = true;
                }
            }
            break;
        case 2:
            if(is_digit(c)){ state = 2; }
            else if(c == '.'){ state = 5; }
            else {
                type = KPYINDENTIFIERTOKEN;
                foundOne = true;
            }
            break;
        case 3:
            type = KPYCOLONTOKEN;
            foundOne = true;
            break;
        case 4:
            type = KPYCOMMATOKEN;
            foundOne = true;
            break;
        case 5:
            if(is_digit(c)){ state = 5; }
            else{
                type = KPYFLOATTOKEN;
                foundOne = true;
            }
            break;
        case 6:
            if(c == SINGLE_QUOTE){
                type = KPYSTRINGTOKEN;
                lex = lex + c;
                lex = lex.substr(1, lex.size() - 2);
                c = istrm->get();
                foundOne = true;
                if(istrm->eof()){ type = KPYBADTOKEN; }
            }else{
                if(istrm->eof()){
                    type = KPYBADTOKEN;
                    foundOne = true;
                }
            }
            break;
        case 7:
            if(c == '"'){
                type = KPYSTRINGTOKEN;
                lex = lex + c;
                lex = lex.substr(1, lex.size() - 2);
                c = istrm->get();
                foundOne = true;
            }else{
                if(istrm->eof()){
                    type = KPYBADTOKEN;
                    foundOne = true;
                }
            }
            break;
        case 8:
            foundOne = true;
            type = KPYSLASHTOKEN;
            break;
        case 9:
            foundOne = true;
            type KPYLEFTPARENTOKEN;
            break;
        case 10:
            foundOne = true;
            type = KPYRIGHTPARENTOKEN;
            break;
        case 11:
            if(is_digit(c)){state = 2;}
            else{
                type = KPYBADTOKEN;
                foundOne = true;
            }
            break;
        case 12:
        }
    }
}
