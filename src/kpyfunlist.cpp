#include "kleinpy.hpp"

using namespace kleinpy;

// ---
KPyFunListNode::KPyFunListNode(KPyObject *head, KPyFunListNode *tail){
    this->head = head;
    this->tail = tail;
    if(tail != nullptr){ len = 1 + tail->len; }
    else{ len = 1; }
}

// ---
KPyFunListNode::~KPyFunListNode(){
    try{ delete head; }
    catch(...){}

    try{ delete tail; }
    catch(...){}
}

// ---
std::string KPyFunListNode::to_string(){
    std::ostringstream oss;

    oss << head->to_string();
    if(tail != nullptr){
        oss << ", " << tail->to_string();
    }

    return oss.str();
}

// ---
KPyObject* KPyFunListNode::get_head(){
    return head;
}
