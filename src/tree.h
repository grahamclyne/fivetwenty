#ifndef TREE_H
#define TREE_H

typedef enum
{
    k_expressionKindIdentifier,
    k_expressionKindIntLiteral,
    k_expressionKindFloatLiteral,
    k_expressionKindStringLiteral,
    k_expressionKindAddition,
    k_expressionKindSubtraction,
    k_expressionKindMultiplication,
    k_expressionKindDivision,
    k_expressionKindEquality,
    k_expressionKindGreaterThan,
    k_expressionKindLessThan
} ExpressionKind;

typedef enum
{
    k_typeInt,
    k_typeBool,
    k_typeString,
    k_typeIdentifier,
    k_typeFloat
} TypeKind;

typedef struct TYPE TYPE;
struct TYPE
{
    int lineno;
    TypeKind kind;
};

typedef struct EXP EXP;
struct EXP
{
    int lineno;
    ExpressionKind kind;
    union {
        char *id;
        int intLiteral;
        float floatLiteral;
        char *stringLiteral;
        int boolLiteral;
        struct
        {
            EXP *lhs;
            EXP *rhs;
        } binary;
    } val;
};

typedef struct STATEMENT STATEMENT;
struct STATEMENT
{
    int lineno;
    union {
        struct
        {
            char *id;
            EXP *exp;
        } assignment;
        struct
        {
            EXP *condition;
            STATEMENT *body;
        } loop;
        struct
        {
            EXP *condition;
            STATEMENT *body;
        } ifstatement;
        struct
        {
            char *id;
            TYPE *type;
        } decl;
        struct
        {
            char *id;
            TYPE *type;
            EXP *exp;
        } declassign;
        struct
        {
            char *id;
        } read;
        struct
        {
            EXP *exp;
        } print;
    } val;
    STATEMENT *next;
};

EXP *makeEXP_identifier(char *id);
EXP *makeEXP_stringLiteral(char *stringLiteral);
EXP *makeEXP_floatLiteral(float floatLiteral);
EXP *makeEXP_intLiteral(int intLiteral);
EXP *makeEXP_booleanLiteral(int boolLiteral);
EXP *makeEXP_binary(ExpressionKind op, EXP *lhs, EXP *rhs);
STATEMENT *makeSTATEMENT_if(EXP *condition, STATEMENT *body);
STATEMENT *makeSTATEMENT_while(EXP *condigition, STATEMENT *body);
STATEMENT *makeSTATEMENT_assign(char *id, EXP *exp);
STATEMENT *makeSTATEMENT_decl(char *id, TYPE *type);
STATEMENT *makeSTATEMENT_declassign(char *id, TYPE *type, EXP *value);
STATEMENT *makeSTATEMENT_print(EXP *exp);
STATEMENT *makeSTATEMENT_read(char *id);
STATEMENT *makeSTATEMENT_ifelse(EXP *exp, STATEMENT *statements, STATEMENT *elsestatements);
TYPE *makeTYPEbool();
TYPE *makeTYPEint();
TYPE *makeTYPEfloat();
TYPE *makeTYPEstring();

#endif