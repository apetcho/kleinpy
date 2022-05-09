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

// ---
KPyFunList::KPyFunList(KPyObject *obj, KPyFunList *flist) : KPyObject(){
    data = new KPyFunList(obj, flist->get_node());
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
KPyFunList::KPyFunList(KPyFunListNode *node) : KPyObject() {
    data = node;

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
KPyFunList::~KPyFunList(){}

// ---
KPyType* KPyFunList::get_type(){
    return kpytypes[KPyTypeId::KPY_FUNLIST_TYPE];
}

// ---
std::string KPyFunList::to_string(){
    std::ostringstream oss;
    oss << "[";
    if(data != nullptr){
        oss << data->to_string();
    }
    oss << "]";

    return oss.str();
}

// ---
KPyObject* KPyFunList::__getitem__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 1){
        oss << "TypeError: expected 1 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    if(data == nullptr){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Attempt to index an empty funlist."
        );
    }

    KPyInt *iobj = (KPyInt*)(*args)[0];
    int index = iobj->get_value();
    if(index >= data->get_len()){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Index out of range on funlist"
        );
    }

    KPyFunListNode *node = data;
    for(int k=0; k < index; k++){
        node = node->get_tail();
    }

    return node->get_head();
}

// ---
KPyObject* KPyFunList::__len__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }
    if(data == nullptr){ return new KPyInt(0); }

    return new KPyInt(data->get_len());
}

// ---
KPyObject* KPyFunList::__iter__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 arguments, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    return new KPyFunListIterator(this);
}
