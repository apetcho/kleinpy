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

// class PyBool
// class PyBuiltinConcat
// class PyBuiltinFPrint
// class PyBuiltinInput
// class PyBuiltinIter
// class PyBuiltinLen
// class PyBuiltinPrint
// class PyBuiltinTPrint
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
