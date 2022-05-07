#include "kleinpy.hpp"
using namespace kleinpy;
// ---
std::ostream& operator<<(
    std::ostream& strm, KPyObject kpyObj){
    strm << kpyObj.to_string();
    return strm;
}
