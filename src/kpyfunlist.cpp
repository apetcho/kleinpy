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

// ---
KPyObject* KPyFunListNode::get_tail(){
    return tail;
}

// ---
int KPyFunListNode::get_len(){
    return len;
}

// ---
KPyFunList::KPyFunList(std::vector<KPyObject*>* args) : KPyObject(){
    KPyFunListNode *tmp = nullptr;
    for(int k= args->size()-1; k >= 0; k--){
        tmp = new KPyFunListNode((*args)[k], tmp);
    }
    data = tmp;
    dict["__getitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::__getitem__
    );

    dict["__len__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::__len__
    );

    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::__iter__
    );

    dict["__add__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::__add__
    );

    dict["head"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::head
    );

    dict["tail"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::tail
    );

    dict["concat"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::concat
    );
}

// ---
KPyFunList::KPyFunList() : KPyObject(){
    data = nullptr;
    dict["__getitem__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::__getitem__
    );

    dict["__len__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::__len__
    );

    dict["__iter__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::__iter__
    );

    dict["__add__"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::__add__
    );

    dict["head"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::head
    );

    dict["tail"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::tail
    );

    dict["concat"] = (KPyObject* (KPyObject::*)(std::vector<KPyObject*>*))(
        &KPyFunList::concat
    );
}
