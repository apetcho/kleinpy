#ifndef __KLEINPY_H_
#define __KLEINPY_H_
#include<string>
#include<unordered_map>
#include<vector>
#include<iostream>


namespace kleinpy{
class KPyType;  // foreward declaration

// -----------------------
// --- class KPyObject ---
// -----------------------
class KPyObject{
public:
    KPyObject();
    virtual ~KPyObject();
    virtual KPyType *get_type();
    virtual std::string to_string();
    void decref();
    void incref();
    int get_refcount() const;

    KPyObject* call_method(std::string name, std::vector<KPyObject*>* args);

protected:
    std::unordered_map<
        std::string,
        KPyObject* (KPyObject::*)(std::vector<KPyObject*>*)> dict;

    int refcount;

    virtual KPyObject* __str__(std::vector<KPyObject*>* args);
    virtual KPyObject* __type__(std::vector<KPyObject*>* args);
};

std::ostream& operator<<(std::ostream& out, KPyObject& obj);
extern bool verbose;

// ------------------------
// --- class KPyCallable ---
// ------------------------
class KPyCallable : public KPyObject {
public:
    KPyCallable();
    KPyCallable(const KPyCallable& callable);
    virtual ~KPyCallable();

protected:
    virtual KPyObject* __call__(std::vector<KPyObject*>* args) = 0;
};

// ---------------------
// --- class KPyAttr ---
// ---------------------
class KPyAttr : public KPyCallable{
public:
    KPyAttr(KPyObject *self, std::string method);
    virtual ~KPyAttr();
    bool allowable_argcount(int count);

    KPyType* get_type();
    std::string to_string();

protected:
    std::string method;
    KPyObject *self;

    virtual KPyObject* __call__(std::vector<KPyObject*>* args);
}; // KPyAttr

// ---------------------
// --- class KPyBool ---
// ---------------------
class KPyBool : public KPyObject{
public:
    KPyBool();
    KPyBool(const KPyBool& obj);
    virtual ~KPyBool();

    KPyType* get_type();
    std::string to_string();
    bool get_value();

protected:
    bool value;

    virtual KPyObject* __float__(std::vector<KPyObject*>* args);
    virtual KPyObject* __int__(std::vector<KPyObject*>* args);
    virtual KPyObject* __bool__(std::vector<KPyObject*>* args);
    virtual KPyObject* __eq__(std::vector<KPyObject*>* args);
};

// ------------------------------
// --- class KPyBuiltinConcat ---
// ------------------------------
class KPyBuiltinConcat : public KPyCallable{
public:
    KPyBuiltinConcat();
    KPyBuiltinConcat(const KPyBuiltinConcat& obj);
    virtual ~KPyBuiltinConcat();
    KPyType* get_type();
    bool allowable_argcount(int count);
    std::string to_string();

protected:
    virtual KPyObject* __call__(std::vector<KPyObject*>* args);
};

// ------------------------------
// --- class KPyBuiltinFPrint ---
// ------------------------------
class KPyBuiltinFPrint : public KPyCallable{
public:
    KPyBuiltinFPrint();
    KPyBuiltinFPrint(const KPyBuiltinFPrint& obj);
    virtual ~KPyBuiltinFPrint();
    KPyType* get_type();
    std::string to_string();

protected:
    virtual KPyObject* __call__(std::vector<KPyObject*>* args);
};

// -----------------------------
// --- class KPyBuiltinInput ---
// -----------------------------
class KPyBuiltinInput : public KPyCallable{
public:
    KPyBuiltinInput();
    KPyBuiltinInput(const KPyBuiltinInput& obj);
    virtual ~KPyBuiltinInput();
    KPyType* get_type();
    bool allowable_argcount(int count);
    std::string to_string();

protected:
    virtual KPyObject* __call__(std::vector<KPyObject*>* args);
};

// ----------------------------
// --- class KPyBuiltinIter ---
// ----------------------------
class KPyBuiltinIter : public KPyCallable {
public:
    KPyBuiltinIter();
    KPyBuiltinIter(const KPyBuiltinIter& obj);
    virtual ~KPyBuiltinIter();

    KPyType* get_type();
    bool allowable_argcount(int count);
    std::string to_string();

protected:
    virtual KPyObject* __call__(std::vector<KPyObject*>* args);
};

// ---------------------------
// --- class KPyBuiltinLen ---
// ---------------------------
class KPyBuiltinLen: public KPyCallable{
public:
    KPyBuiltinLen();
    KPyBuiltinLen(const KPyBuiltinLen& obj);
    virtual ~KPyBuiltinLen();
    KPyType* get_type();

    bool allowable_argcount(int count);
    std::string to_string();

protected:
    virtual KPyObject* __call__(std::vector<KPyObject*>* args);
};

// -----------------------------
// --- class KPyBuiltinPrint ---
// -----------------------------
class KPyBuiltinPrint : public KPyCallable{
public:
    KPyBuiltinPrint();
    KPyBuiltinPrint(const KPyBuiltinPrint& onj);
    virtual ~KPyBuiltinPrint();
    KPyType* get_type();
    bool allowable_argcount(int count);
    std::string to_string();

protected:
    KPyObject* __call__(std::vector<KPyObject*>* args);
};

// -----------------------------
// --- class PyBuiltinTPrint ---
// -----------------------------

// class PyByteCode
// enum PyOpCode
// class PyCell
// class PyCode
// class PyException
// class PyExceptionType
// class PyFloat
// class PyFrame 
// class PyFunction
// class PyFunListElem
// class PyFunList
// class PyFunListIterator
// class PyInt
// class PyList
// class PyListIterator
// class PyNone
// class PyParser
// class PyRange
// class PyRangeIterator
// class PyRangeType
// class PyScanner
// class _PyStackElement
// class PyStack
// class PyStr or PyString
// class PyStrIterator
// class PyToken
// class PyTuple
// class PyTupleIterator
// enum PyTypeId
// --- pyutil ---
// printMap()

}// namespace mpy
#endif
