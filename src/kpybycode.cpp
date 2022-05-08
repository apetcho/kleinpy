#include "kleinpy.hpp"

using namespace kleinpy;

// ---
bool create_map(std::unordered_map<std::string, KPyOpCode>& bcmap){
    bcmap["STOP_CODE"] = KPyOpCode::STOP_CODE;
    bcmap["NOP"] = KPyOpCode::NOP;
    bcmap["POP_TOP"] = KPyOpCode::POP_TOP;
    bcmap["ROT_TWO"] = KPyOpCode::ROT_TWO;
    bcmap["ROT_THREE"] = KPyOpCode::ROT_TREE;
    bcmap["DUP_TOP"] = KPyOpCode::DUP_TOP;
    bcmap["DUP_TOP_TWO"] = KPyOpCode::DUP_TOP_TWO;
    bcmap["UNARY_POSITIVE"] = KPyOpCode::UNARY_POSITIVE;
    bcmap["UNARY_NEGATIVE"] = KPyOpCode::UNARY_NEGATIVE;
    bcmap["UNARY_NOT"] = KPyOpCode::UNARY_NOT;
    bcmap["UNARY_INVERT"] = KPyOpCode::UNARY_INVERT;
    bcmap["GET_ITER"] = KPyOpCode::GET_ITER;
    bcmap["BINARY_POWER"] = KPyOpCode::BINARY_POWER;
    bcmap["BINARY_MULTIPLY"] = KPyOpCode::BINARY_MULTIPLY;
    bcmap["BINARY_FLOOR_DIVIDE"] = KPyOpCode::BINARY_FLOOR_DIVIDE;
    bcmap["BINARY_TRUE_DIVIDE"] = KPyOpCode::BINARY_TRUE_DIVIDE;
    bcmap["BINARY_MODULO"] = KPyOpCode::BINARY_MODULO;
    bcmap["BINARY_ADD"] = KPyOpCode::BINARY_ADD;
    bcmap["BINARY_SUBSTRACT"] = KPyOpCode::BINARY_SUBSTRACT;
    bcmap["BINARY_SUBSCR"] = KPyOpCode::BINARY_SUBSCR;
    bcmap["BINARY_LSHIFT"] = KPyOpCode::BINARY_LSHIFT;
    bcmap["BINARY_RSHIFT"] = KPyOpCode::BINARY_RSHIFT;
    bcmap["BINARY_AND"] = KPyOpCode::BINARY_AND;
    bcmap["BINARY_XOR"] = KPyOpCode::BINARY_XOR;
    bcmap["BINARY_OR"] = KPyOpCode::BINARY_OR;
    bcmap["INPLACE_POWER"] = KPyOpCode::INPLACE_POWER;
    bcmap["INPLACE_MULTIPLY"] = KPyOpCode::INPLACE_MULTIPLY;
    bcmap["INPLACE_FLOOR_DIVIDE"] = KPyOpCode::INPLACE_FLOOR_DIVIDE;
    bcmap["INPLACE_TRUE_DIVIDE"] = KPyOpCode::INPLACE_TRUE_DIVIDE;
    bcmap["INPLACE_MODULO"] = KPyOpCode::INPLACE_MODULO;
    bcmap["INPLACE_ADD"] = KPyOpCode::INPLACE_ADD;
    bcmap["INPLACE_SUBSTRACT"] = KPyOpCode::INPLACE_SUBSTRACT;
    bcmap["INPLACE_LSHIFT"] = KPyOpCode::INPLACE_LSHIFT;
    bcmap["INPLACE_RSHIFT"] = KPyOpCode::INPLACE_RSHIFT;
    bcmap["INPLACE_AND"] = KPyOpCode::INPLACE_AND;
    bcmap["INPLACE_XOR"] = KPyOpCode::INPLACE_XOR;
    bcmap["INPLACE_OR"] = KPyOpCode::INPLACE_OR;
    bcmap["STORE_SUBSCR"] = KPyOpCode::STORE_SUBSCR;
    bcmap["DELETE_SUBSCR"] = KPyOpCode::DELETE_SUBSCR;
    bcmap["PRINT_EXPR"] = KPyOpCode::PRINT_EXPR;
    bcmap["BREAK_LOOP"] = KPyOpCode::BREAK_LOOP;
    bcmap["CONTINUE_LOOP"] = KPyOpCode::CONTINUTE_LOOP;
    bcmap["SET_ADD"] = KPyOpCode::SET_ADD;
    bcmap["LIST_APPEND"] = KPyOpCode::LIST_APPEND;
    bcmap["MAP_ADD"] = KPyOpCode::MAP_ADD;
    bcmap["RETURN_VALUE"] = KPyOpCode::RETURN_VALUE;
    bcmap["YIELD_VALUE"] = KPyOpCode::YIELD_VALUE;
    bcmap["IMPORT_STAR"] = KPyOpCode::IMPORT_STAR;
    bcmap["POP_BLOCK"] = KPyOpCode::POP_BLOCK;
    bcmap["POP_EXCEPT"] = KPyOpCode::POP_EXCEPT;
    bcmap["END_FINALLY"] = KPyOpCode::END_FINALLY;
    bcmap["LOAD_BUILD_CLASS"] = KPyOpCode::LOAD_BUILD_CLASS;
    bcmap["SETUP_WITH"] = KPyOpCode::SETUP_WITH;
    bcmap["WITH_CLEANUP"] = KPyOpCode::WITH_CLEANUP;
    bcmap["STORE_LOCALS"] = KPyOpCode::STORE_LOCALS;
    bcmap["STORE_NAME"] = KPyOpCode::STORE_NAME;
    bcmap["DELETE_NAME"] = KPyOpCode::DELETE_NAME;
    bcmap["UNPACK_SEQUENCE"] = KPyOpCode::UNPACK_SEQUENCE;
    bcmap["UNPACK_EX"] = KPyOpCode::UNPACK_EX;
    bcmap["STORE_ATTR"] = KPyOpCode::STORE_ATTR;
    bcmap["DELETE_ATTR"] = KPyOpCode::DELETE_ATTR;
    bcmap["STORE_GLOBAL"] = KPyOpCode::STORE_GLOBAL;
    bcmap["DELETE_GLOBAL"] = KPyOpCode::DELETE_GLOBAL;
    bcmap["LOAD_CONST"] = KPyOpCode::LOAD_CONST;
    bcmap["LOAD_NAME"] = KPyOpCode::LOAD_NAME;
    bcmap["BUILD_TUPLE"] = KPyOpCode::BUILD_TUPLE;
    bcmap["BUILD_LIST"] = KPyOpCode::BUILD_LIST;
    bcmap["BUILD_SET"] = KPyOpCode::BUILD_SET;
    bcmap["BUILD_MAP"] = KPyOpCode::BUILD_MAP;
    bcmap["LOAD_ATTR"] = KPyOpCode::LOAD_ATTR;
    bcmap["COMPARE_OP"] = KPyOpCode::COMPARE_OP;
    bcmap["IMPORT_NAME"] = KPyOpCode::IMPORT_NAME;
    bcmap["IMPORT_FROM"] = KPyOpCode::IMPORT_FROM;
    bcmap["JUMP_FORWARD"] = KPyOpCode::JUMP_FORWARD;
    bcmap["POP_JUMP_IF_TRUE"] = KPyOpCode::POP_JUMP_IF_TRUE;
    bcmap["POP_JUMP_IF_FALSE"] = KPyOpCode::POP_JUMP_IF_FALSE;
    bcmap["JUMP_IF_TRUE_OR_POP"] = KPyOpCode::JUMP_IF_TRUE_OR_POP;
    bcmap["JUMP_IF_FALSE_OR_POP"] = KPyOpCode::JUMP_IF_FALSE_OR_POP;
    bcmap["JUMP_ABSOLUTE"] = KPyOpCode::JUMP_ABSOLUTE;
    bcmap["FOR_ITER"] = KPyOpCode::FOR_ITER;
    bcmap["LOAD_GLOBAL"] = KPyOpCode::LOAD_GLOBAL;
    bcmap["SETUP_LOOP"] = KPyOpCode::SETUP_LOOP;
    bcmap["SETUP_EXCEPT"] = KPyOpCode::SETUP_EXCEPT;
    bcmap["SETUP_FINALLY"] = KPyOpCode::SETUP_FINALLY;
    bcmap["STORE_MAP"] = KPyOpCode::STORE_MAP;
    bcmap["LOAD_FAST"] = KPyOpCode::LOAD_FAST;
    bcmap["STORE_FAST"] = KPyOpCode::STORE_FAST;
    bcmap["DELETE_FAST"] = KPyOpCode::DELETE_FAST;
    bcmap["LOAD_CLOSURE"] = KPyOpCode::LOAD_CLOSURE;
    bcmap["LOAD_DEREF"] = KPyOpCode::LOAD_DEREF;
    bcmap["DELETE_DEREF"] = KPyOpCode::DELETE_DEREF;
    bcmap["RAISE_VARARGS"] = KPyOpCode::RAISE_VARARGS;
    bcmap["CALL_FUNCTION"] = KPyOpCode::CALL_FUNCTION;
    bcmap["MAKE_FUNCTION"] = KPyOpCode::MAKE_FUNCTION;
    bcmap["MAKE_CLOSURE"] = KPyOpCode::MAKE_CLOSURE;
    bcmap["BUILD_SLICE"] = KPyOpCode::BUILD_SLICE;
    bcmap["EXTENDED_ARG"] = KPyOpCode::EXTENDED_ARG;
    bcmap["CALL_FUNCTION_VAR"] = KPyOpCode::CALL_FUNCTION_VAR;
    bcmap["CALL_FUNCTION_KW"] = KPyOpCode::CALL_FUNCTION_KW;
    bcmap["CALL_FUNCTION_VAR_KW"] = KPyOpCode::CALL_FUNCTION_VAR_KW;
    bcmap["HAVE_ARGUMENT"] = KPyOpCode::HAVE_ARGUMENT;
    // New Instructions
    bcmap["BUILD_FUNLIST"] = KPyOpCode::BUILD_FUNLIST;
    bcmap["SELECT_FUNLIST"] = KPyOpCode::SELECT_FUNLIST;
    bcmap["CONS_FUNLIST"] = KPyOpCode::CONS_FUNLIST;
    bcmap["SELECT_TUPLE"] = KPyOpCode::SELECT_TUPLE;

    return true;
}

std::unordered_map<std::string, KPyOpCode> opcodemap;
bool dummy = create_map(opcodemap);

// ---
bool create_arg_map(std::unordered_map<std::string, int>& argmap){
    argmap["STOP_CODE"] = 0;
    argmap["NOP"] = 0;
    argmap["POP_TOP"] = 0;
    argmap["ROT_TWO"] = 0;
    argmap["ROT_THREE"] = 0;
    argmap["DUP_TOP"] = 0;
    argmap["DUP_TOP_TWO"] = 0;
    argmap["UNARY_POSITIVE"] = 0;
    argmap["UNARY_NEGATIVE"] = 0;
    argmap["UNARY_NOT"] = 0;
    argmap["UNARY_INVERT"] = 0;
    argmap["GET_ITER"] = 0;
    argmap["BINARY_POWER"] = 0;
    argmap["BINARY_MULTIPLY"] = 0;
    argmap["BINARY_FLOOR_DIVIDE"] = 0;
    argmap["BINARY_TRUE_DIVIDE"] = 0;
    argmap["BINARY_MODULO"] = 0;
    argmap["BINARY_ADD"] = 0;
    argmap["BINARY_SUBSTRACT"] = 0;
    argmap["BINARY_SUBSCR"] = 0;
    argmap["BINARY_LSHIFT"] = 0;
    argmap["BINARY_RSHIFT"] = 0;
    argmap["BINARY_AND"] = 0;
    argmap["BINARY_XOR"] = 0;
    argmap["BINARY_OR"] = 0;
    argmap["INPLACE_POWER"] = 0;
    argmap["INPLACE_MULTIPLY"] = 0;
    argmap["INPLACE_FLOOR_DIVIDE"] = 0;
    argmap["INPLACE_TRUE_DIVIDE"] = 0;
    argmap["INPLACE_MODULO"] = 0;
    argmap["INPLACE_ADD"] = 0;
    argmap["INPLACE_SUBSTRACT"] = 0;
    argmap["INPLACE_LSHIFT"] = 0;
    argmap["INPLACE_RSHIFT"] = 0;
    argmap["INPLACE_AND"] = 0;
    argmap["INPLACE_XOR"] = 0;
    argmap["INPLACE_OR"] = 0;
    argmap["STORE_SUBSCR"] = 0;
    argmap["DELETE_SUBSCR"] = 0;
    argmap["PRINT_EXPR"] = 0;
    argmap["BREAK_LOOP"] = 0;
    argmap["CONTINUE_LOOP"] = 1;
    argmap["SET_ADD"] = 1;
    argmap["LIST_APPEND"] = 1;
    argmap["MAP_ADD"] = 1;
    argmap["RETURN_VALUE"] = 0;
    argmap["YIELD_VALUE"] = 0;
    argmap["IMPORT_STAR"] = 0;
    argmap["POP_BLOCK"] = 0;
    argmap["POP_EXCEPT"] = 0;
    argmap["END_FINALLY"] = 0;
    argmap["LOAD_BUILD_CLASS"] = 0;
    argmap["SETUP_WITH"] = 1;
    argmap["WITH_CLEANUP"] = 0;
    argmap["STORE_LOCALS"] = 0;
    argmap["STORE_NAME"] = 1;
    argmap["DELETE_NAME"] = 1;
    argmap["UNPACK_SEQUENCE"] = 1;
    argmap["UNPACK_EX"] = 1;
    argmap["STORE_ATTR"] = 1;
    argmap["DELETE_ATTR"] = 1;
    argmap["STORE_GLOBAL"] = 1;
    argmap["DELETE_GLOBAL"] = 1;
    argmap["LOAD_CONST"] = 1;
    argmap["LOAD_NAME"] = 1;
    argmap["BUILD_TUPLE"] = 1;
    argmap["BUILD_LIST"] = 1;
    argmap["BUILD_SET"] = 1;
    argmap["BUILD_MAP"] = 1;
    argmap["LOAD_ATTR"] = 1;
    argmap["COMPARE_OP"] = 1;
    argmap["IMPORT_NAME"] = 1;
    argmap["IMPORT_FROM"] = 1;
    argmap["JUMP_FORWARD"] = 1;
    argmap["POP_JUMP_IF_TRUE"] = 1;
    argmap["POP_JUMP_IF_FALSE"] = 1;
    argmap["JUMP_IF_TRUE_OR_POP"] = 1;
    argmap["JUMP_IF_FALSE_OR_POP"] = 1;
    argmap["JUMP_ABSOLUTE"] = 1;
    argmap["FOR_ITER"] = 1;
    argmap["LOAD_GLOBAL"] = 1;
    argmap["SETUP_LOOP"] = 1;
    argmap["SETUP_EXCEPT"] = 1;
    argmap["SETUP_FINALLY"] = 1;
    argmap["STORE_MAP"] = 0;
    argmap["LOAD_FAST"] = 1;
    argmap["STORE_FAST"] = 1;
    argmap["DELETE_FAST"] = 1;
    argmap["LOAD_CLOSURE"] = 1;
    argmap["LOAD_DEREF"] = 1;
    argmap["DELETE_DEREF"] = 1;
    argmap["RAISE_VARARGS"] = 1;
    argmap["CALL_FUNCTION"] = 1;
    argmap["MAKE_FUNCTION"] = 1;
    argmap["MAKE_CLOSURE"] = 1;
    argmap["BUILD_SLICE"] = 1;
    argmap["EXTENDED_ARG"] = 1;
    argmap["CALL_FUNCTION_VAR"] = 1;
    argmap["CALL_FUNCTION_KW"] = 1;
    argmap["CALL_FUNCTION_VAR_KW"] = 1;
    argmap["HAVE_ARGUMENT"] = 0;
    // New Instructions
    argmap["BUILD_FUNLIST"] = 1;
    argmap["SELECT_FUNLIST"] = 0;
    argmap["CONS_FUNLIST"] = 0;
    argmap["SELECT_TUPLE"] = 1;
    return true;
}

std::unordered_map<std::string, int> argmap;
bool dummy2 = create_arg_map(argmap);

const char* opcodenames[] = {
    "STOP_CODE",
    "NOP",
    "POP_TOP",
    "ROT_TWO",
    "ROT_THREE",
    "DUP_TOP",
    "DUP_TOP_TWO",
    "UNARY_POSITIVE",
    "UNARY_NEGATIVE",
    "UNARY_NOT",
    "UNARY_INVERT",
    "GET_ITER",
    "BINARY_POWER",
    "BINARY_MULTIPLY",
    "BINARY_FLOOR_DIVIDE",
    "BINARY_TRUE_DIVIDE",
    "BINARY_MODULO",
    "BINARY_ADD",
    "BINARY_SUBSTRACT",
    "BINARY_SUBSCR",
    "BINARY_LSHIFT",
    "BINARY_RSHIFT",
    "BINARY_AND",
    "BINARY_XOR",
    "BINARY_OR",
    "INPLACE_POWER",
    "INPLACE_MULTIPLY",
    "INPLACE_FLOOR_DIVIDE",
    "INPLACE_TRUE_DIVIDE",
    "INPLACE_MODULO",
    "INPLACE_ADD",
    "INPLACE_SUBSTRACT",
    "INPLACE_LSHIFT",
    "INPLACE_RSHIFT",
    "INPLACE_AND",
    "INPLACE_XOR",
    "INPLACE_OR",
    "STORE_SUBSCR",
    "DELETE_SUBSCR",
    "PRINT_EXPR",
    "BREAK_LOOP",
    "CONTINUE_LOOP",
    "SET_ADD",
    "LIST_APPEND",
    "MAP_ADD",
    "RETURN_VALUE",
    "YIELD_VALUE",
    "IMPORT_STAR",
    "POP_BLOCK",
    "POP_EXCEPT",
    "END_FINALLY",
    "LOAD_BUILD_CLASS",
    "SETUP_WITH",
    "WITH_CLEANUP",
    "STORE_LOCALS",
    "STORE_NAME",
    "DELETE_NAME",
    "UNPACK_SEQUENCE",
    "UNPACK_EX",
    "STORE_ATTR",
    "DELETE_ATTR",
    "STORE_GLOBAL",
    "DELETE_GLOBAL",
    "LOAD_CONST",
    "LOAD_NAME",
    "BUILD_TUPLE",
    "BUILD_LIST",
    "BUILD_SET",
    "BUILD_MAP",
    "LOAD_ATTR",
    "COMPARE_OP",
    "IMPORT_NAME",
    "IMPORT_FROM",
    "JUMP_FORWARD",
    "POP_JUMP_IF_TRUE",
    "POP_JUMP_IF_FALSE",
    "JUMP_IF_TRUE_OR_POP",
    "JUMP_IF_FALSE_OR_POP",
    "JUMP_ABSOLUTE",
    "FOR_ITER",
    "LOAD_GLOBAL",
    "SETUP_LOOP",
    "SETUP_EXCEPT",
    "SETUP_FINALLY",
    "STORE_MAP",
    "LOAD_FAST",
    "STORE_FAST",
    "DELETE_FAST",
    "LOAD_CLOSURE",
    "LOAD_DEREF",
    "DELETE_DEREF",
    "RAISE_VARARGS",
    "CALL_FUNCTION",
    "MAKE_FUNCTION",
    "MAKE_CLOSURE",
    "BUILD_SLICE",
    "EXTENDED_ARG",
    "CALL_FUNCTION_VAR",
    "CALL_FUNCTION_KW",
    "CALL_FUNCTION_VAR_KW",
    "HAVE_ARGUMENT",
    // New Instructions
    "BUILD_FUNLIST",
    "SELECT_FUNLIST",
    "CONS_FUNLIST",
    "SELECT_TUPLE"
};
