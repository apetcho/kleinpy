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
class KPyBuiltinTPrint : public KPyCallable{
public:
    KPyBuiltinTPrint();
    KPyBuiltinTPrint(const KPyBuiltinTPrint& obj);
    virtual ~KPyBuiltinTPrint();

    KPyType* get_type();
    bool allowable_argcount(int count);
    std::string to_string();

protected:
    virtual KPyObject* __call__(std::vector<KPyObject*>* args);
};

// ------------------------------
// --- enum class KPyByteCode ---
// ------------------------------
// enum KPyOpCode
enum class KPyOpCode{
    STOP_CODE,
    NOP,
    POP_TOP,
    ROT_TWO,
    ROT_TREE,
    DUP_TOP,
    DUP_TOP_TWO,
    UNARY_POSITIVE,
    UNARY_NEGATIVE,
    UNARY_NOT,
    UNARY_INVERT,
    GET_ITER,
    BINARY_POWER,
    BINARY_MULTIPLY,
    BINARY_FLOOR_DIVIDE,
    BINARY_TRUE_DIVIDE,
    BINARY_MODULO,
    BINARY_ADD,
    BINARY_SUBSTRACT,
    BINARY_SUBSCR,
    BINARY_LSHIFT,
    BINARY_RSHIFT,
    BINARY_AND,
    BINARY_XOR,
    INPLACE_POWER,
    INPLACE_MULTIPLY,
    INPLACE_FLOOR_DIVIDE,
    INPLACE_TRUE_DIVIDE,
    INPLACE_MODULO,
    INPLACE_ADD,
    INPLACE_SUBSTRACT,
    INPLACE_LSHIFT,
    INPLACE_RSHIFT,
    INPLACE_AND,
    INPLACE_XOR,
    STORE_SUBSCR,
    DELETE_SUBSCR,
    PRINT_EXPR,
    BREAK_LOOP,
    CONTINUTE_LOOP,
    SET_ADD,
    LIST_APPEND,
    MAP_ADD,
    RETURN_VALUE,
    YIELD_VALUE,
    IMPORT_STAR,
    POP_BLOCK,
    POP_EXCEPT,
    END_FINALLY,
    LOAD_BUILD_CLASS,
    SETUP_WITH,
    WITH_CLEANUP,
    STORE_LOCALS,
    STORE_NAME,
    DELETE_NAME,
    UNPACK_SEQUENCE,
    UNPACK_EX,
    STORE_ATTR,
    DELETE_ATTR,
    STORE_GLOBAL,
    DELETE_GLOBAL,
    LOAD_CONST,
    LOAD_NAME,
    BUILD_TUPLE,
    BUILD_LIST,
    BUILD_SET,
    BUILD_MAP,
    COMPARE_OP,
    IMPORT_NAME,
    IMPORT_FROM,
    JUMP_FORWARD,
    POP_JUMP_IF_TRUE,
    POP_JUMP_IF_FALSE,
    JUMP_IF_TRUE_OR_POP,
    JUMP_IF_FALSE_OR_POP,
    JUMP_ABSOLUTE,
    FOR_ITER,
    LOAD_GLOBAL,
    SETUP_LOOP,
    SETUP_EXCEPT,
    SETUP_FINALLY,
    STORE_MAP,
    LOAD_FAST,
    STORE_FAST,
    DELETE_FAST,
    LOAD_CLOSURE,
    LOAD_DEREF,
    STORE_DEREF,
    DELETE_DEREF,
    RAISE_VARARGS,
    CALL_FUNCTION,
    MAKE_FUNCTION,
    MAKE_CLOSURE,
    BUILD_SLICE,
    CALL_FUNCTION_VAR,
    CALL_FUNCTION_KW,
    CALL_FUNCTION_VAR_KW,
    HAVE_ARGUMENT,
    // --- New opcodes defined ba Kent Lee
    BUILD_FUNLIST,
    SELECT_FUNLIST,
    CONS_FUNLIST,
    SELECT_TUPLE,
};

class KPyByteCode{
public:
    KPyByteCode(std::string opcode);
    KPyByteCode(std::string opcode, int operand);
    KPyByteCode(std::string opcode, std::string label);
    KPyByteCode(const KPyByteCode& obj);
    virtual ~KPyByteCode();
    KPyOpCode get_opcode() const;
    int get_operand() const;
    std::string get_opcode_name() const;
    std::string get_label() const;
    std::string to_string() const;
    static int nargs(std::string opcode);

protected:
    KPyOpCode opcode;
    int operand;
    std::string label;
};

// ---------------------
// --- class KPyCell ---
// ---------------------
class KPyCell : public KPyObject{
public:
    KPyCell(KPyObject *ref);
    virtual ~KPyCell();
    KPyObject* deref();
    void set(KPyObject *ref);
    KPyType* get_type();

private:
    KPyObject* ref;
};

// --------------------
// --- class PyCode ---
// --------------------
class KPyCode : public KPyObject{
public:
    KPyCode(
        std::string name, std::vector<KPyCode*>* nestedFn,
        std::vector<KPyObject*>* consts, std::vector<std::string>* locals,
        std::vector<std::string>* freeVars, std::vector<std::string>* cellVars,
        std::vector<std::string>* globals, std::vector<KPyByteCode*>* code,
        int argcount
    );

    virtual ~KPyCode();

    std::string get_name() const;
    std::vector<std::string>& get_locals() const;
    std::vector<std::string>& get_freeVars() const;
    std::vector<std::string>& get_cellVars() const;
    std::vector<std::string>& get_globals() const;
    std::vector<KPyObject*>& get_consts() const;
    std::vector<KPyByteCode*>& get_instructions() const;
    std::vector<KPyCode*>& get_nestedFn() const;
    int get_nargs() const;
    int num_locals() const;
    std::string to_string();
    std::string pretty_string(std::string indent, bool lineno) const;
    KPyType* get_type();

    KPyObject* __str__(std::vector<KPyObject*>* args);
    KPyObject* __type__(std::vector<KPyObject*>* args);

private:
    std::string name;
    std::vector<KPyCode*>* nestedFn;
    std::vector<std::string>* locals;
    std::vector<std::string>* freeVars;
    std::vector<std::string>* cellVars;
    std::vector<std::string>* globals;
    std::vector<KPyObject*>* consts;
    std::vector<KPyByteCode*>* instructions;

    int nargs;
};

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
