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
