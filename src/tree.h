
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
    k_statementKindAssignment, 
    k_statementKindWhile,
    k_statementKindPrint,
    k_statementKindRead, 
    k_statementKindIf,
    k_statementKindIfElse
} StatementKind;


typedef struct EXP EXP;
struct EXP
{
    ExpressionKind kind;
    union {
        char *id;
        int intLiteral;
        float floatLiteral;
        char *stringLiteral;
        bool boolLiteral;
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
    StatementKind kind;
    int lineno;
    union {
        struct
        {
            char *id;
            EXP *value;
        } assignment;

        struct
        {
            EXP *condition;
            STATEMENT *body;
        } loop;
    } val;
    STATEMENT *next;
};

EXP *makeEXP_identifier(char *id);
EXP *makeEXP_stringLiteral(char *stringLiteral);
EXP *makeEXP_floatLiteral(float floatLiteral);
EXP *makeEXP_intLiteral(int intLiteral);
EXP *makeEXP_booleanLiteral(bool boolLiteral);
EXP *makeEXP_binary(ExpressionKind op, EXP *lhs, EXP *rhs);
STATEMENT *makeSTATEMENT_assign(char *id, EXP *value);
STATEMENT *makeSTATEMENT_while(EXP *condition, STATEMENT *body);
STATEMENT *makeSTATEMENT_print(EXP *exp);
STATEMENT *makeSTATEMENT_read(char *id);
STATEMENT *makeSTATEMENT_if(EXP *exp, STATEMENT *statements);
STATEMENT *makeSTATEMENT_ifelse(EXP *exp, STATEMENT *statements, STATEMENT *elsestatements);