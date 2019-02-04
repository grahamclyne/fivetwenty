#include <stdio.h>
#include "pretty.h"
void prettyEXP(EXP *e)
{
    switch (e->kind)
    {
    case k_expressionKindIdentifier:
        printf("%s", e->val.stringLiteral);
        break;
    case k_expressionKindIntLiteral:
        printf("%i", e->val.intLiteral);
        break;
    case k_expressionKindAddition:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf("+");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindSubtraction:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf("-");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindMultiplication:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf("*");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindDivision:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf("/");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindFloatLiteral:
        printf("%f", e->val.floatLiteral);
        break;
    case k_expressionKindStringLiteral:
        printf("%s", e->val.stringLiteral);
        break;
    case k_expressionKindEquality:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf("==");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindGreaterThan:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf(">");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindLessThan:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf("<");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindGreaterThanEquals:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf(">=");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindLessThanEquals:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf("<=");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindNotEqual:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf("!=");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindAnd:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf("&&");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    case k_expressionKindOr:
        printf("(");
        prettyEXP(e->val.binary.lhs);
        printf("||");
        prettyEXP(e->val.binary.rhs);
        printf(")");
        break;
    }
}

void prettySTATEMENT(STATEMENT *s)
{
    if (s->next != NULL)
    {
        prettySTATEMENT(s->next);
    }
    switch (s->kind)
    {
    case k_statementKindAssign:
        printf("%s = ", s->val.assignment.id);
        prettyEXP(s->val.assignment.exp);
        printf(";\n");
        break;
    case k_statementKindWhile:
        printf("while");
        printf("(");
        prettyEXP(s->val.loop.condition);
        printf(")");
        printf("{");
        printf("\n");
        prettySTATEMENT(s->val.loop.body);
        printf("}");
        printf("\n");
        break;
    case k_statementKindPrint:
        printf("printf(");
        prettyEXP(s->val.print.exp);
        printf(");\n");
        break;
    case k_statementKindRead:
        printf("read(%s);\n", s->val.read.id);
        break;
    case k_statementKindIf:
        printf("if ( ");
        prettyEXP(s->val.ifstatement.condition);
        printf(" ) {");
        printf("\n");
        prettySTATEMENT(s->val.ifstatement.body);
        printf("}\n");
        if (s->val.ifstatement.elsestatement != NULL)
        {
            prettySTATEMENT(s->val.ifstatement.elsestatement);
        }
        break;
    case k_statementKindElseIf:
        printf("else if (");
        prettyEXP(s->val.elseifstatement.condition);
        printf(") {");
        printf("\n");
        prettySTATEMENT(s->val.elseifstatement.body);
        printf("}\n");
        if (s->val.ifstatement.elsestatement != NULL)
        {
            prettySTATEMENT(s->val.ifstatement.elsestatement);
        }
        break;
    case k_statementKindElse:
        printf("else {");
        prettySTATEMENT(s->val.elsestatement.body);
        printf("}\n");
        break;
    case k_statementKindDeclaration:
        printf("var %s : ", s->val.decl.id);
        prettyTYPE(s->val.decl.type);
        printf(";\n");
        break;
    case k_statementKindDeclarationAssignment:
        printf("var %s : ", s->val.declassign.id);
        prettyTYPE(s->val.declassign.type);
        printf(" = ");
        prettyEXP(s->val.declassign.exp);
        printf(";\n");
        break;
    }
}

void prettyTYPE(TYPE *t)
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
        string = "string ";
        break;
    }
    printf("%s", string);
}

