#include "kleinpy.hpp"

using namespace kleinpy;

// ---
struct names{
    static std::unordered_map<int, std::string> create_map(){
        std::unordered_map<int, std::string> exceptmap;
        exceptmap[KPYEXCEPTION] = "Exception";
        exceptmap[KPYEMPTYSTACKEXCEPTION] = "EmptyStackException";
        exceptmap[KPYPARSEEXCEPTION] = "ParseException";
        exceptmap[KPYILLEGALOPERATIONEXCEPTION] = "IllegalOperatonException";
        exceptmap[KPYWRONGARGCOUNTEXCEPTION] = "WrongArgCountException";
        exceptmap[KPYSTOPITERATIONEXCEPTION] = "StopIterationException";
        exceptmap[KPYMATCHEXCEPTION] = "MatchException";

        return exceptmap;
    }
};

static std::unordered_map<int, std::string> exceptmap = names::create_map();
