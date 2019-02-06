#include "tree.h"
#include <stdio.h>
#include "code.h"



void codeEXP(EXP *e, SymbolTable *st)
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
        codeEXP(e->val.binary.lhs, st);
        printf("%s", e->val.binary.opera);
        codeEXP(e->val.binary.rhs, st);
        printf(")");
        break;
    case k_expressionKindBooleanLiteral:
        printf("%s", e->val.boolLiteral);
        break;
    case k_expressionKindFloatLiteral:
        printf("%f", e->val.floatLiteral);
        break;
    case k_expressionKindStringLiteral:
        printf("%s", e->val.stringLiteral);
        break;
    case k_expressionKindNot:
        printf("!");
        codeEXP(e->val.unary.exp, st);
        break;
    case k_expressionKindNegative:
        printf("-");
        codeEXP(e->val.unary.exp, st);
        break;
    }
}



void codeSTATEMENT(STATEMENT *s, SymbolTable *st)
{
    if (s->next != NULL)
    {
        codeSTATEMENT(s->next, st);
    }
    switch (s->kind)
    {
    case k_statementKindAssign:;
        printf("%s = ", s->val.assignment.id);
        codeEXP(s->val.assignment.exp, st);
        printf(";\n");
        break;
    case k_statementKindWhile:
        printf("while");
        printf("(");
        codeEXP(s->val.loop.condition, st);
        printf(")");
        printf("{");
        printf("\n");
        codeSTATEMENT(s->val.loop.body, st);
        printf("}");
        printf("\n");
        break;
    case k_statementKindPrint:
        printf("printf(");
        SYMBOL *sym = codePRINT(s->val.print.exp, st);
        codeEXP(s->val.print.exp, st);
        printf(", %s);\n", sym->type.string);
        break;
    case k_statementKindRead:;
        SYMBOL *sym = getSymbol(st, s->val.assignment.id);
        char* string = "";
        switch (sym->type.kind)
        {
        case 0:
            string = "%d";
            break;
        case 1:
            string = "%f";
            break;
        case 2:
            string = "%b";
            break;
        case 3:
            printf("char  %s[20];", s->val.read.id);
            string = "%s";
            break;
        }
        printf("scanf(%s,%s);\n", string, s->val.read.id);
        break;
    case k_statementKindIf:
        printf("if ( ");
        codeEXP(s->val.ifstatement.condition, st);
        printf(" ) {");
        printf("\n");
        codeSTATEMENT(s->val.ifstatement.body, st);
        printf("}\n");
        if (s->val.ifstatement.elsestatement != NULL)
        {
            codeSTATEMENT(s->val.ifstatement.elsestatement, st);
        }
        break;
    case k_statementKindElseIf:
        printf("else if (");
        codeEXP(s->val.elseifstatement.condition, st);
        printf(") {");
        printf("\n");
        codeSTATEMENT(s->val.elseifstatement.body, st);
        printf("}\n");
        if (s->val.ifstatement.elsestatement != NULL)
        {
            codeSTATEMENT(s->val.ifstatement.elsestatement, st);
        }
        break;
    case k_statementKindElse:
        printf("else {");
        codeSTATEMENT(s->val.elsestatement.body, st);
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
        codeEXP(s->val.declassign.exp, st);
        printf(";\n");
        break;
    }
}


SYMBOL* codePRINT(EXP *e, SymbolTable *st)
{
    switch (e->kind)
    {
    case k_expressionKindIdentifier:
        SYMBOL *sym = getSymbol(st,e->val.id);
        if (sym == NULL)
        {
            fprintf(stderr, "Error: %s not defined at line %d\n", e->val.id, e->lineno);
            exit(1);
        }
        return sym;
    case k_expressionKindNot:
        codePRINT(e->val.unary.exp, st);
        break;
    case k_expressionKindNegative:
        codePRINT(e->val.unary.exp, st);
        break;
    case k_expressionKindBracketed:
        codePRINT(e->val.bracketed.exp, st);
        break;
    case k_expressionKindBinary:
        codePRINT(e->val.binary.lhs, st);
        codePRINT(e->val.binary.rhs, st);
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
