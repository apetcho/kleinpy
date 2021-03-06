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

// ---
KPyObject* KPyFunList::__add__(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 1){
        oss << "TypeError: expected 1 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    KPyFunList *other = (KPyFunList*)(*args[0]);
    KPyStack<KPyObject*> tmpstack;
    KPyFunListNode *node = data;
    KPyObject *xvalue;

    while(node != nullptr){
        tmpstack.push(node->get_head());
        node = node->get_tail();
    }
    node = other->data;
    while(!tmpstack.is_empty()){
        xvalue = tmpstack.pop();
        node = new KPyFunListNode(xvalue, node);
    }

    new KPyFunList(node);
}

// ---
KPyFunListNode* KPyFunList::get_node(){
    return data;
}

// ---
KPyObject* KPyFunList::get_head(){
    if(data == nullptr){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Attempt to get head of empty funlist."
        );
    }

    return get_node()->get_head();
}

// ---
KPyFunList* KPyFunList::get_tail(){
    if(data == nullptr){
        throw new KPyException(
            KPYILLEGALOPERATIONEXCEPTION,
            "Attempt to get tail of empty funlist."
        );
    }

    return new KPyFunList(get_node()->get_tail());
}

// ---
KPyObject* KPyFunList::head(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        if(args->size() != 0){
            oss << "TypeError: expected 0 argument, got " << args->size();
            throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
        }
    }

    return get_head();
}

// ---
KPyObject* KPyFunList::tail(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        if(args->size() != 0){
            oss << "TypeError: expected 0 argument, got " << args->size();
            throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
        }
    }

    return get_tail();
}

// ---
KPyObject* KPyFunList::concat(std::vector<KPyObject*>* args){
    std::ostringstream oss;
    if(args->size() != 0){
        oss << "TypeError: expected 0 argument, got " << args->size();
        throw new KPyException(KPYWRONGARGCOUNTEXCEPTION, oss.str());
    }

    std::ostringstream strm;
    KPyFunListNode *lnode= data; //! FIXME
    while(data != nullptr){
        strm << data->get_head()->to_string();
        data = data->get_tail();
    }

    return new KPyStr(strm.str());
}
