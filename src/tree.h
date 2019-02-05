#ifndef TREE_H
#define TREE_H

typedef enum
{
    k_expressionKindIdentifier,
    k_expressionKindIntLiteral,
    k_expressionKindFloatLiteral,
    k_expressionKindBooleanLiteral,
    k_expressionKindStringLiteral,
    k_expressionKindBinary,
    k_expressionKindBracketed,
    k_expressionKindNot,
    k_expressionKindNegative
} ExpressionKind;

typedef enum
{
    k_statementKindWhile,
    k_statementKindPrint,
    k_statementKindRead,
    k_statementKindIf,
    k_statementKindElse,
    k_statementKindElseIf,
    k_statementKindAssign,
    k_statementKindDeclaration,
    k_statementKindDeclarationAssignment,
    k_statementKindComment
} StatementKind;

typedef enum
{
    k_typeInt,
    k_typeFloat,
    k_typeBool,
    k_typeString
} TypeKind;

typedef struct TYPE TYPE;
struct TYPE
{
    int lineno;
    TypeKind kind;
    char *string;
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
        char *boolLiteral;
        struct
        {
            EXP *exp;
        } bracketed;
        struct
        {
            EXP *lhs;
            EXP *rhs;
            char *opera;
        } binary;
        struct
        {
            char op;
            EXP *exp;
        } unary;
    } val;
};

typedef struct STATEMENT STATEMENT;
struct STATEMENT
{
    int lineno;
    StatementKind kind;
    union {
        struct
        {
            EXP *condition;
            STATEMENT *body;
        } loop;
        struct
        {
            EXP *condition;
            STATEMENT *body;
            STATEMENT *elsestatement;
        } ifstatement;
        struct
        {
            STATEMENT *body;
        } elsestatement;
        struct
        {
            EXP *condition;
            STATEMENT *body;
            STATEMENT *elsestatement;
        } elseifstatement;
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
        struct
        {
            char *id;
            EXP *exp;
        } assignment;
        struct
        {
            char *id;
        } comment;
    } val;
    STATEMENT *next;
};

typedef struct PROGRAM PROGRAM;
struct PROGRAM
{
    int lineno;
    STATEMENT *next;
};

EXP *makeEXP_identifier(char *id);
EXP *makeEXP_stringLiteral(char *stringLiteral);
EXP *makeEXP_floatLiteral(float floatLiteral);
EXP *makeEXP_intLiteral(int intLiteral);
EXP *makeEXP_booleanLiteral(char *boolLiteral);
EXP *makeEXP_binary(char *opera, EXP *lhs, EXP *rhs);
EXP *makeEXP_unary(ExpressionKind, char op, EXP *exp);
EXP *makeEXP_bracketed(EXP *exp);
STATEMENT *makeSTATEMENT_if(EXP *condition, STATEMENT *body, STATEMENT *elsest);
STATEMENT *makeSTATEMENT_elseif(EXP *condition, STATEMENT *statements, STATEMENT *elsestatement);
STATEMENT *makeSTATEMENT_else(STATEMENT *statements);
STATEMENT *makeSTATEMENT_while(EXP *condigition, STATEMENT *body);
STATEMENT *makeSTATEMENT_decl(char *id, TYPE *type);
STATEMENT *makeSTATEMENT_declassign(char *id, TYPE *type, EXP *value);
STATEMENT *makeSTATEMENT_print(EXP *exp);
STATEMENT *makeSTATEMENT_read(char *id);
STATEMENT *makeSTATEMENT_assign(char *id, EXP *exp);
STATEMENT *makeSTATEMENT_comment(char *id);
TYPE *makeTYPEbool();
TYPE *makeTYPEint();
TYPE *makeTYPEfloat();
TYPE *makeTYPEstring();

#endif