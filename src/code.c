#include "tree.h"
#include <stdio.h>
#include "code.h"
void codeEXP(EXP *e)
{
    switch (e->kind)
    {
    case k_expressionKindIdentifier:
        printf("%s", e->val.stringLiteral);
        break;
    case k_expressionKindIntLiteral:
        printf("%i", e->val.intLiteral);
        break;
    case k_expressionKindBinary:
        printf("(");
        codeEXP(e->val.binary.lhs);
        printf("%s", e->val.binary.opera);
        codeEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindFloatLiteral:
        printf("%f", e->val.floatLiteral);
        break;
    case k_expressionKindStringLiteral:
        printf("%s", e->val.stringLiteral);
        break;
    case k_expressionKindNot:
        printf("!");
        codeEXP(e->val.unary.exp);
        break;
    case k_expressionKindNegative:
        printf("-");
        codeEXP(e->val.unary.exp);
        break;
    }
}

void codeSTATEMENT(STATEMENT *s)
{
    if (s->next != NULL)
    {
        codeSTATEMENT(s->next);
    }
    switch (s->kind)
    {
    case k_statementKindAssign:
        printf("%s = ", s->val.assignment.id);
        codeEXP(s->val.assignment.exp);
        printf(";\n");
        break;
    case k_statementKindWhile:
        printf("while");
        printf("(");
        codeEXP(s->val.loop.condition);
        printf(")");
        printf("{");
        printf("\n");
        codeSTATEMENT(s->val.loop.body);
        printf("}");
        printf("\n");
        break;
    case k_statementKindPrint:
        printf("printf(");
        codeEXP(s->val.print.exp);
        printf(");\n");
        break;
    case k_statementKindRead:
        printf("read(%s);\n", s->val.read.id);
        break;
    case k_statementKindIf:
        printf("if ( ");
        codeEXP(s->val.ifstatement.condition);
        printf(" ) {");
        printf("\n");
        codeSTATEMENT(s->val.ifstatement.body);
        printf("}\n");
        if (s->val.ifstatement.elsestatement != NULL)
        {
            codeSTATEMENT(s->val.ifstatement.elsestatement);
        }
        break;
    case k_statementKindElseIf:
        printf("else if (");
        codeEXP(s->val.elseifstatement.condition);
        printf(") {");
        printf("\n");
        codeSTATEMENT(s->val.elseifstatement.body);
        printf("}\n");
        if (s->val.ifstatement.elsestatement != NULL)
        {
            codeSTATEMENT(s->val.ifstatement.elsestatement);
        }
        break;
    case k_statementKindElse:
        printf("else {");
        codeSTATEMENT(s->val.elsestatement.body);
        printf("}\n");
        break;
    case k_statementKindDeclaration:
        printf("var %s : ", s->val.decl.id);
        codeTYPE(s->val.decl.type);
        printf(";\n");
        codeTYPE(s->val.declassign.type);

        break;
    case k_statementKindDeclarationAssignment:
        codeTYPE(s->val.declassign.type);
        printf("%s", s->val.declassign.id);
        printf(" = ");
        codeEXP(s->val.declassign.exp);
        printf(";\n");
        break;
    }
}

void codeTYPE(TYPE *t)
{
    char *string;
    switch (t->kind)
    {
    case k_typeBool:
        string = "bool ";
        break;
    case k_typeInt:
        string = "int ";
        break;
    case k_typeFloat:
        string = "float ";
        break;
    case k_typeString:
        string = "char* ";
        break;
    }
    printf("%s", string);
}
