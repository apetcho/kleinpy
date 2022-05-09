#ifndef __KLEINPY_H_
#define __KLEINPY_H_
#include<string>
#include<sstream>
#include<unordered_map>
#include<vector>
#include<iostream>


namespace kleinpy{
class KPyType;  // forward declaration
class KPyFrame;
template<typename T> class KPyStack;

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
    KPyBool(bool value);
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
    BINARY_OR,
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
    INPLACE_OR,
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
    LOAD_ATTR,
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
    EXTENDED_ARG,
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

// --------------------------
// --- class KPyException ---
// --------------------------
class KPyException : public KPyObject{
public:
    KPyException(int exceptType, KPyObject *obj);
    KPyException(int exceptType, std::string message);
    virtual ~KPyException();
    int get_exception_type();
    void traceback_append(KPyFrame *frame);
    std::string to_string();
    KPyType* get_type();
    KPyObject* get_traceback();
    void print_traceback();

protected:
    int exceptionType;
    KPyObject *value;
    std::vector<KPyFrame*> traceback;

    virtual KPyObject* __excmatch__(std::vector<KPyObject*>* args);
};

constexpr int KPYEXCEPTION = 1;
constexpr int KPYEMPTYSTACKEXCEPTION = 2;
constexpr int KPYPARSEEXCEPTION = 3;
constexpr int KPYILLEGALOPERATIONEXCEPTION = 4;
constexpr int KPYWRONGARGCOUNTEXCEPTION = 5;
constexpr int KPYSTOPITERATIONEXCEPTION = 6;
constexpr int KPYMATCHEXCEPTION = 7;

// ----------------------------
// --- enum class KPyTypeId ---
// ----------------------------
enum class KPyTypeId{
    KPY_TYPE_TYPE,
    KPY_NONE_TYPE,
    KPY_BOOL_TYPE,
    KPY_INT_TYPE,
    KPY_FLOAT_TYPE,
    KPY_STR_TYPE,
    KPY_FUNCTION_TYPE,
    KPY_BUILTIN_TYPE,
    KPY_RANGE_TYPE_ID,
    KPY_RAND_ITERATOR_TYPE,
    KPY_LIST_TYPE,
    KPY_LIST_ITERATOR_TYPE,
    KPY_FUNLIST_TYPE,
    KPY_FUNLIST_ITERATOR_TYPE,
    KPY_STR_ITERATOR_TYPE,
    KPY_CODE_TYPE,
    KPY_TUPLE_TYPE,
    KPY_TUPLE_ITERATOR,
    KPY_CELL_TYPE,
    KPY_EXCEPTION_TYPE_ID
};

// ---------------------
// --- class KPyType ---
// ---------------------
class KPyType : public KPyCallable{
public:
    KPyType(std::string typeStr, KPyTypeId id);
    virtual ~KPyType();
    std::string to_string();
    KPyType* get_type();
    KPyTypeId type_id();
    std::string call_name();

protected:
    std::string typeStr;
    KPyTypeId index;

    virtual KPyObject* __call__(std::vector<KPyObject*>* args);
    virtual KPyObject* __str__(std::vector<KPyObject*>* args);
    virtual KPyObject* __type__(std::vector<KPyObject*>* args);
};

extern std::unordered_map<KPyTypeId, KPyType*, std::hash<int>> kpytypes;

// ------------------------------
// --- class KPyExceptionType ---
// ------------------------------
class KPyExceptionType: public KPyType {
public:
    KPyExceptionType(std::string typeStr, KPyTypeId id);
    virtual ~KPyExceptionType();
    bool allowable_argcount(int count);

protected:
    KPyObject* __call__(std::vector<KPyObject*>* args);
};

// ----------------------
// --- class KPyFloat ---
// ----------------------
class KPyFloat : public KPyObject{
public:
    KPyFloat(double value);
    KPyFloat(const KPyFloat& obj);
    virtual ~KPyFloat();
    std::string to_string();
    KPyType* get_type();
    double get_value();

protected:
    double value;

    virtual KPyObject* __add__(std::vector<KPyObject*>* args);
    virtual KPyObject* __float__(std::vector<KPyObject*>* args);
    virtual KPyObject* __int__(std::vector<KPyObject*>* args);
    virtual KPyObject* __bool__(std::vector<KPyObject*>* args);
};

// ----------------------
// --- class KPyFrame ---
// ----------------------
class KPyFrame : public KPyObject{
public:
    KPyFrame(
        const KPyCode& code, std::vector<KPyObject*>* args,
        std::unordered_map<std::string, KPyObject*>& globals,
        const std::vector<KPyObject*>& consts,
        std::unordered_map<std::string, KPyCell*>& cellVars
    );

    virtual ~KPyFrame();

    KPyObject* execute();
    std::string get_cell_name(int index);
    const KPyCode& get_code() const;
    int get_pc() const;

private:
    const KPyCode& code;
    int pc;
    std::unordered_map<std::string, KPyObject*> locals;
    std::unordered_map<std::string, KPyObject*>& globals;
    std::unordered_map<std::string, KPyCell*>& cellVars;
    const std::vector<KPyObject*>& consts;

    KPyStack<KPyObject*>& opstack;
    KPyStack<int>* blockstack;
    KPyObject* safety_pop();
};

void push_frame(KPyFrame *frame);
void pop_frame();

// -------------------------
// --- class KPyFunction ---
// -------------------------
class KPyFunction : public KPyCallable {
public:
    KPyFunction(
        KPyCode& code, std::unordered_map<std::string, KPyObject*>& globals,
        KPyObject *env
    );
    virtual ~KPyFunction();

    KPyType* get_type();
    bool allowable_argcount(int count);
    std::string to_string();
    std::string call_name();

private:
    KPyCode& code;
    std::unordered_map<std::string, KPyObject*>& globals;
    std::unordered_map<std::string, KPyCell*> cellVars;

    KPyObject* __call__(std::vector<KPyObject*>* args);
};

// ----------------------------
// --- class KPyFunListNode --- 
// ----------------------------
class KPyFunListNode {
public:
    KPyFunListNode(KPyObject* head, KPyFunListNode *tail);
    ~KPyFunListNode();
    std::string to_string();
    KPyObject* get_head();
    KPyFunListNode* get_tail();
    int get_len();

private:
    KPyObject *head;
    KPyFunListNode *tail;
    int len;
};

// ------------------------
// --- class KPyFunList ---
// ------------------------
class KPyFunList : public KPyObject{
public:
    KPyFunList(std::vector<KPyObject*>* obj);
    KPyFunList();
    KPyFunList(KPyObject *head, KPyFunList *tail);
    KPyFunList(KPyFunListNode *node);
    virtual ~KPyFunList();
    KPyType* get_type();
    std::string to_string();
    KPyObject* get_head();
    KPyFunList* get_tail();
    KPyFunListNode* get_node();

protected:
    KPyFunListNode *data;
    virtual KPyObject* __getitem__(std::vector<KPyObject*>* args);
    virtual KPyObject* __len__(std::vector<KPyObject*>* args);
    virtual KPyObject* __iter__(std::vector<KPyObject*>* args);
    virtual KPyObject* __add__(std::vector<KPyObject*>* args);
    virtual KPyObject* head(std::vector<KPyObject*>* args);
    virtual KPyObject* tail(std::vector<KPyObject*>* args);
    virtual KPyObject* concat(std::vector<KPyObject*>* args);
};

// --------------------------------
// --- class KPyFunListIterator ---
// --------------------------------
class KPyFunListIterator: public KPyObject{
public:
    KPyFunListIterator(KPyFunList* fnlist);
    virtual ~KPyFunListIterator();
    KPyType* get_type();
    std::string to_string();

protected:
    KPyFunListNode *node;

    virtual KPyObject* __iter__(std::vector<KPyObject*>* args);
    virtual KPyObject* __next__(std::vector<KPyObject*>* args);
};

// --------------------
// --- class KPyInt ---
// --------------------
class KPyInt : public KPyObject{
public:
    KPyInt(int value);
    KPyInt(const KPyInt& obj);
    virtual ~KPyInt();
    KPyType* get_type();
    std::string to_string();
    int get_value();

protected:
    int value;

    virtual KPyObject* __add__(std::vector<KPyObject*>* args);
    virtual KPyObject* __sub__(std::vector<KPyObject*>* args);
    virtual KPyObject* __mul__(std::vector<KPyObject*>* args);
    virtual KPyObject* __floordiv__(std::vector<KPyObject*>* args);
    virtual KPyObject* __truediv__(std::vector<KPyObject*>* args);
    virtual KPyObject* __eq__(std::vector<KPyObject*>* args);
    virtual KPyObject* __gt__(std::vector<KPyObject*>* args);
    virtual KPyObject* __lt__(std::vector<KPyObject*>* args);
    virtual KPyObject* __ge__(std::vector<KPyObject*>* args);
    virtual KPyObject* __le__(std::vector<KPyObject*>* args);
    virtual KPyObject* __float__(std::vector<KPyObject*>* args);
    virtual KPyObject* __int__(std::vector<KPyObject*>* args);
    virtual KPyObject* __bool__(std::vector<KPyObject*>* args);
};

// ---------------------
// --- class KPyList ---
// ---------------------
class KPyList : public KPyObject{
public:
    KPyList(std::vector<KPyObject*>* obj);
    virtual ~KPyList();
    KPyType* get_type();
    std::string to_string();
    KPyObject* get_value(int index);
    void set_value(int index, KPyObject *value);

protected:
    std::vector<KPyObject*> data;

    virtual KPyObject* __getitem__(std::vector<KPyObject*>* args);
    virtual KPyObject* __setitem__(std::vector<KPyObject*>* args);
    virtual KPyObject* __len__(std::vector<KPyObject*>* args);
    virtual KPyObject* __iter__(std::vector<KPyObject*>* args);
    virtual KPyObject* append(std::vector<KPyObject*>* args);
};

// -----------------------------
// --- class KPyListIterator ---
// -----------------------------
class KPyListIterator : public KPyObject {
public:
    KPyListIterator(KPyList* objlist);
    virtual ~KPyListIterator();

    KPyType* get_type();
    std::string to_string();

protected:
    KPyList *objlist;
    int index;

    virtual KPyObject* __iter__(std::vector<KPyObject*>* args);
    virtual KPyObject* __next__(std::vector<KPyObject*>* args);
};

// ---------------------
// --- class KPyNone ---
// ---------------------
class KPyNone : public KPyObject{
public:
    KPyNone();
    KPyNone(const KPyNone& obj);
    virtual ~KPyNone();
    KPyType* get_type();
    std::string to_string();

protected:
};

// ----------------------
// --- class KPyToken ---
// ----------------------
class KPyToken {
public:
    KPyToken(int tokenType, std::string lex, int lineno, int colno);
    virtual ~KPyToken();
    std::string get_lex() const;
    int get_type() const ;
    int get_colno() const;
    int get_lineno() const;

private:
    std::string lex;
    int toktype;
    int lineno;
    int colno;
};

constexpr int KPYINDENTIFIERTOKEN = 1;
constexpr int KPYINTEGERTOKEN = 2;
constexpr int KPYFLOATTOKEN = 3;
constexpr int KPYSTRINGTOKEN = 4;
constexpr int KPYKEYWORDTOKEN = 5;
constexpr int KPYCOLONTOKEN = 6;
constexpr int KPYCOMMATOKEN = 7;
constexpr int KPYSLASHTOKEN = 8;
constexpr int KPYLEFTPARENTOKEN = 9;
constexpr int KPYRIGHTPARENTOKEN = 10;
constexpr int KPYEOFTOKEN = 98;
constexpr int KPYBADTOKEN = 99;

// -----------------------
// --- class PyScanner ---
// -----------------------
class KPyScanner {
public:
    KPyScanner(std::istream *istrm);
    virtual ~KPyScanner();
    void put_back_token();

private:
    std::istream *istrm;
    KPyToken *lasttok;
    bool needtok;
    int colcount;
    int linecount;
    bool error;
};


// -----------------------
// --- class KPyParser ---
// -----------------------
class KPyParser {
public:
    KPyParser(std::string filename);
    KPyParser(const KPyParser& obj);
    virtual ~KPyParser();
    std::vector<KPyCode*>* parse();

private:
    KPyScanner *input;

    std::unordered_map<std::string, int> target;
    int index;
    std::vector<KPyCode*>* pyassemble_prog();
    std::vector<KPyCode*>* functionlist_part();
    std::vector<KPyCode*>* functionlist(std::vector<KPyCode*>* vec);

    KPyCode* fundef();
    std::vector<KPyObject*>* const_part(std::vector<KPyCode*>* nestedFn);
    std::vector<KPyObject*>* value_list(
        std::vector<KPyObject*>* constant,
        std::vector<KPyCode*>* nestedFn
    );
    std::vector<KPyObject*>* value_rest(
        std::vector<KPyObject*>* constant,
        std::vector<KPyCode*>* nestedFn
    );
    KPyObject* value(std::vector<KPyCode*>* nestedFn);
    std::vector<std::string>* locals_part();
    std::vector<std::string>* freeVars_part();
    std::vector<std::string>* cellVars_part();
    std::vector<std::string>* idlist(std::vector<std::string>* objlist);
    std::vector<std::string>* idrest(std::vector<std::string>* objlist);
    std::vector<std::string>* globals_part();
    std::vector<KPyByteCode*>* body_part();
    std::vector<KPyByteCode*>* instruction_list(std::vector<KPyByteCode*>*);
    KPyByteCode* labeled_instructions();
};

// ----------------------
// --- class KPyRange ---
// ----------------------
class KPyRange : public KPyObject{
public:
    KPyRange(int start, int stop, int increment);
    virtual ~KPyRange();
    KPyType* get_type();
    KPyObject* index_of(int index);
    std::string to_string();

protected:
    int start;
    int stop;
    int increment;

    virtual KPyObject* __iter__(std::vector<KPyObject*>* args);
    virtual KPyObject* __next__(std::vector<KPyObject*>* args);
    virtual KPyObject* __getitem__(std::vector<KPyObject*>* args);
    virtual KPyObject* __list__(std::vector<KPyObject*>* args);
};

// -----------------------------
// --- class PyRangeIterator ---
// -----------------------------
class KPyRangeIterator : public KPyObject {
public:
    KPyRangeIterator(KPyRange *rangeObj);
    virtual ~KPyRangeIterator();
    KPyType* get_type();
    std::string to_string();

protected:
    KPyRange *rangeObj;
    int index;

    virtual KPyObject* __iter__(std::vector<KPyObject*>* args);
    virtual KPyObject* __next__(std::vector<KPyObject*>* args);
};

// --------------------------
// --- class KPyRangeType ---
// --------------------------
class KPyRangeType : public KPyType{
public:
    KPyRangeType(std::string typestr, KPyTypeId id);
    virtual ~KPyRangeType();
    bool allowable_argcount(int count);

protected:
    virtual KPyObject* __call__(std::vector<KPyObject*>* args);
};

// ----------------------------
// --- class __KPyStackNode ---
// ----------------------------
template<typename T>
class __KPyStackNode{
public:
    __KPyStackNode(T node);
    virtual ~__KPyStackNode();
    T object;
    __KPyStackNode<T>* next;
};

// ----------------------
// --- class KPyStack ---
// ----------------------
template<typename T>
class KPyStack{
public:
    KPyStack();
    virtual ~KPyStack();
    T pop();
    void push(T object);
    T top();
    bool is_empyty();
    std::string to_string();
    int get_count();

private:
    __KPyStackNode<T>* tos;
    int count;
};

template<typename T>
KPyStack<T>::KPyStack(){ tos = nullptr; }

template<typename T>
KPyStack<T>::~KPyStack(){
    if(tos != nullptr){
        try{ delete tos;}
        catch(...){}
    }
}

template<typename T>
std::string KPyStack<T>::to_string(){
    std::stringstream out;
    out << "top " << std::endl;
    __KPyStackNode<T>* cursor;
    cursor = tos;
    while(cursor != nullptr){
        out << *(cursor->object) << std::endl;
        cursor = cursor->next;
    }

    return out.str();
}

template<typename T>
T KPyStack<T>::pop(){
    if(tos != nullptr){
        __KPyStackNode<T>* node = tos;
        T value = node->object;
        tos = tos->next;
        node->next = nullptr;
        delete node;
        count--;
        return value;
    }
    throw new KPyException(
        KPYEMPTYSTACKEXCEPTION, "Attempt to pop an empty stack"
    );
}

template<typename T>
void KPyStack<T>::push(T object){
    __KPyStackNode<T>* node = new __KPyStackNode<T>(object);
    node->next = tos;
    tos = node;
    node++;
}

template<typename T>
T KPyStack<T>::top(){
    if(tos != nullptr){
        T value = tos->object;
        return value;
    }

    throw new KPyException(
        KPYEMPTYSTACKEXCEPTION, "Attempt to get top of empty stack."
    );
}

template<typename T>
bool KPyStack<T>::is_empyty(){
    return (tos == nullptr);
}

template<typename T>
__KPyStackNode<T>::__KPyStackNode(T obj){
    object = obj;
    next = nullptr;
}

template<typename T>
__KPyStackNode<T>::~__KPyStackNode(){
    if(next != nullptr){
        try{ delete next; }
        catch(...){}
    }
}

// --------------------
// --- class KPyStr ---
// --------------------
class KPyStr : public KPyObject{
public:
    KPyStr(std::string text);
    KPyStr(const KPyStr& obj);
    virtual ~KPyStr();
    KPyType* get_type();
    std::string to_string();
    KPyStr* char_at(int index);

protected:
    std::string value;

    virtual KPyObject* __add__(std::vector<KPyObject*>* args);
    virtual KPyObject* __str__(std::vector<KPyObject*>* args);
    virtual KPyObject* __float__(std::vector<KPyObject*>* args);
    virtual KPyObject* __int__(std::vector<KPyObject*>* args);
    virtual KPyObject* __bool__(std::vector<KPyObject*>* args);
    virtual KPyObject* __funlist__(std::vector<KPyObject*>* args);
    virtual KPyObject* __eq__(std::vector<KPyObject*>* args);
    virtual KPyObject* split(std::vector<KPyObject*>* args);

    virtual KPyObject* __getitem__(std::vector<KPyObject*>* args);
    virtual KPyObject* __len__(std::vector<KPyObject*>* args);
    virtual KPyObject* __iter__(std::vector<KPyObject*>* args);
};

// ----------------------------
// --- class KPyStrIterator ---
// ----------------------------
class KPyStrIterator : public KPyObject{
public:
    KPyStrIterator(KPyStr *strobj);
    virtual ~KPyStrIterator();

    KPyType* get_type();
    std::string to_string();

private:
    KPyStr* str;
    int index;

    virtual KPyObject* __iter__(std::vector<KPyObject*>* args);
    virtual KPyObject* __next__(std::vector<KPyObject*>* args);
};

// ---------------------
// --- class PyTuple ---
// ---------------------
class KPyTuple : public KPyObject {
public:
    KPyTuple(std::vector<KPyObject*>* objlist);
    virtual ~KPyTuple();
    KPyType* get_type();
    std::string to_string();
    KPyObject* get_value(int index);
    int size();

protected:
    std::vector<KPyObject*> data;

    virtual KPyObject* __getitem__(std::vector<KPyObject*>* args);
    virtual KPyObject* __len__(std::vector<KPyObject*>* args);
    virtual KPyObject* __iter__(std::vector<KPyObject*>* args);
};

// -----------------------------
// --- class PyTupleIterator ---
// -----------------------------
class KPyTupleIterator : public KPyObject{
public:
    KPyTupleIterator(KPyTuple* objlist);
    virtual ~KPyTupleIterator();

    KPyType* get_type();
    std::string to_string();

protected:
    KPyTuple *tuple;
    int index;

    virtual KPyObject* __iter__(std::vector<KPyObject*>* args);
    virtual KPyObject* __next__(std::vector<KPyObject*>* args);
};

// ---------------------------
// --------- pyutil ----------
// ---------------------------
template<typename K, typename V>
void print_map(const std::unordered_map<K, V>& dict){
    typename std::unordered_map<K, V>::const_iterator iter;

    for(iter = dict.begin(); iter != dict.end(); iter++){
        std::cout << 
            "key: \"" << iter->first << "\" " <<
            "value: " << iter->second
        << std::endl;
    }
}

}// namespace kleinpy
#endif
