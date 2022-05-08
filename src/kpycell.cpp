#include "kleinpy.hpp"

using namespace kleinpy;

KPyCell::KPyCell(KPyObject *ref) : KPyObject(){
    this->ref = ref;
}
