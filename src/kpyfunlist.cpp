#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyFunListNode::KPyFunListNode(KPyObject *head, KPyFunListNode *tail){
    this->head = head;
    this->tail = tail;
    if(tail != nullptr){ len = 1 + tail->len; }
    else{ len = 1; }
}
