
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "symbol.h"

int Hash(char *str)
{
    unsigned int hash = 0;
    while (*str)
        hash = (hash << 1) + *str++;
    return hash % HashSize;
}

SymbolTable *initSymbolTable()
{
    SymbolTable *t;
    int i;
    t = malloc(sizeof(SymbolTable));
    for (i = 0; i < HashSize; i++)
        t->table[i] = NULL;
    t->parent = NULL;
    return t;
}

SymbolTable *scopeSymbolTable(SymbolTable *st)
{
    SymbolTable *t;
    t = initSymbolTable();
    t->parent = st;
    return t;
}

SYMBOL *putSymbol(SymbolTable *st, char *name, TYPE *type)
{
    int i = Hash(name);
    SYMBOL *s;
    for (s = st->table[i]; s; s = s->next)
    {
        if (strcmp(s->name, name) == 0)
            return s;
    }
    s = malloc(sizeof(SYMBOL));
    s->name = name;
    s->type = *type;
    s->next = st->table[i];
    st->table[i] = s;
    return s;
}

SYMBOL *getSymbol(SymbolTable *st, char *name)
{
    int i = Hash(name);
    SYMBOL *s;
    for (s = st->table[i]; s; s = s->next)
    {
        if (strcmp(s->name, name) == 0)
            return s;
    }
    if (st->parent == NULL)
        return NULL;
    return getSymbol(st->parent, name);
}

void symSTATEMENT(STATEMENT *s, SymbolTable *st)
{
    if (s->next != NULL)
    {
        symSTATEMENT(s->next, st);
    }
    switch (s->kind)
    {
    case k_statementKindWhile:
        symEXP(s->val.loop.condition, st);
        SymbolTable *stwhile = scopeSymbolTable(st);
        symSTATEMENT(s->val.loop.body, stwhile);
        break;
    case k_statementKindPrint:
        symEXP(s->val.print.exp, st);
        break;
    case k_statementKindRead:
        if (getSymbol(st, s->val.read.id) == NULL)
        {
            fprintf(stderr, "Error: %s not defined on line %d\n", s->val.read.id, s->lineno);
            exit(1);
        }
        break;
    case k_statementKindIf:
        symEXP(s->val.ifstatement.condition, st);
        SymbolTable *stif = scopeSymbolTable(st);
        symSTATEMENT(s->val.ifstatement.body, stif);
        if (s->val.ifstatement.elsestatement != NULL)
        {
            SymbolTable *stelse = scopeSymbolTable(st);
            symSTATEMENT(s->val.ifstatement.elsestatement, stelse);
        }
        break;
    case k_statementKindElse:
        symSTATEMENT(s->val.elsestatement.body, st);
        break;
    case k_statementKindElseIf:
        symEXP(s->val.elseifstatement.condition, st);
        SymbolTable *stelseif = scopeSymbolTable(st);
        symSTATEMENT(s->val.elseifstatement.body, stelseif);
        if (s->val.elseifstatement.elsestatement != NULL)
        {
            SymbolTable *stelse = scopeSymbolTable(st);
            symSTATEMENT(s->val.elseifstatement.elsestatement, stelse);
        }
        break;
    case k_statementKindAssign:
        if (getSymbol(st, s->val.assignment.id) == NULL)
        {
            fprintf(stderr, "Error: %s not defined on line %d.\n", s->val.assignment.id, s->lineno);
            exit(1);
        }
        symEXP(s->val.assignment.exp, st);
        break;
    case k_statementKindDeclaration:
        if (getSymbol(st, s->val.decl.id) == NULL)
        {
            putSymbol(st, s->val.decl.id, s->val.decl.type);
        }
        else
        {
            fprintf(stderr, "Error: %s already defined.", s->val.decl.id);
            exit(1);
        }
        break;
    case k_statementKindDeclarationAssignment:
        putSymbol(st, s->val.decl.id, s->val.decl.type);
        symEXP(s->val.declassign.exp, st);
        break;
    }
}

void symEXP(EXP *e, SymbolTable *st)
{
    switch (e->kind)
    {
    case k_expressionKindIdentifier:
        if (getSymbol(st, e->val.id) == NULL)
        {
            fprintf(stderr, "Error: %s not defined at line %d\n", e->val.id, e->lineno);
            exit(1);
        }
        break;
    case k_expressionKindIntLiteral:
        break;
    case k_expressionKindFloatLiteral:
        break;
    case k_expressionKindStringLiteral:
        break;
    case k_expressionKindNot:
        symEXP(e->val.unary.exp, st);
        break;
    case k_expressionKindNegative:
        symEXP(e->val.unary.exp, st);
        break;
    default:
        symEXP(e->val.binary.lhs, st);
        symEXP(e->val.binary.rhs, st);
        break;
    }
}

void typeSTATEMENT(STATEMENT *s, SymbolTable *st)
{
    if (s->next != NULL)
    {
        typeSTATEMENT(s->next, st);
    }
    switch (s->kind)
    {
    case k_statementKindWhile:
        typeEXP(s->val.loop.condition, st);
        typeSTATEMENT(s->val.loop.body, st);
        break;
    case k_statementKindPrint:
        typeEXP(s->val.print.exp, st);
        break;
    case k_statementKindRead:
        if (getSymbol(st, s->val.read.id) == NULL)
        {
            fprintf(stderr, "Error: %s not defined on line %d\n", s->val.read.id, s->lineno);
            exit(1);
        }
        break;
    case k_statementKindIf:
        typeEXP(s->val.ifstatement.condition, st);
        typeSTATEMENT(s->val.ifstatement.body, st);
        if (s->val.ifstatement.elsestatement != NULL)
        {
            typeSTATEMENT(s->val.ifstatement.elsestatement, st);
        }
        break;
    case k_statementKindElse:
        typeSTATEMENT(s->val.elsestatement.body, st);
        break;
    case k_statementKindElseIf:
        typeEXP(s->val.elseifstatement.condition, st);
        typeSTATEMENT(s->val.elseifstatement.body, st);
        if (s->val.elseifstatement.elsestatement != NULL)
        {
            typeSTATEMENT(s->val.elseifstatement.elsestatement, st);
        }
        break;
    case k_statementKindAssign:;
        SYMBOL *sym = getSymbol(st, s->val.assignment.id);
        TYPE *tassign = typeEXP(s->val.assignment.exp, st);
        if (sym->type.kind != tassign->kind)
        {
            fprintf(stderr, "Error: type error at line %d, expecting type %s.\n", s->lineno, sym->type.string);
            exit(1);
        }
        break;
    //dont need to consider declaration statement??
    case k_statementKindDeclarationAssignment:;
        TYPE *tdeclassign = typeEXP(s->val.declassign.exp, st);
        if (s->val.declassign.type->kind != tdeclassign->kind)
        {
            fprintf(stderr, "Error: type error at line %d, expecting type %s.\n", s->lineno, s->val.declassign.type->string);
            exit(1);
        }
        break;
    }
}

TYPE *typeEXP(EXP *e, SymbolTable *st)
{
    TYPE *t = malloc(sizeof(TYPE));
    switch (e->kind)
    {
    case k_expressionKindIdentifier:; //this is to prevent error from some whacky c syntax rule
        SYMBOL *sid = getSymbol(st, e->val.id);
        t->kind = sid->type.kind;
        break;
    case k_expressionKindIntLiteral:
        t->kind = k_typeInt;
        break;
    case k_expressionKindFloatLiteral:
        t->kind = k_typeFloat;
        break;
    case k_expressionKindStringLiteral:
        t->kind = k_typeFloat;
        break;
    case k_expressionKindNot:
        t->kind = k_typeBool;
        TYPE *tunary = typeEXP(e->val.unary.exp, st);
        if (t->kind != tunary->kind)
        {
            fprintf(stderr, "Error: type error at line %d\n, expecting type %s.", e->lineno, t->string);
            exit(1);
        }
        break;
    case k_expressionKindNegative:
        t->kind = k_typeInt;
        TYPE *tneg = typeEXP(e->val.unary.exp, st);
        if (t->kind != tneg->kind)
        {
            fprintf(stderr, "Error: type error at line %d\n, expecting type %s.", e->lineno, t->string);
            exit(1);
        }
        break;
    default:;
        TYPE *t1 = typeEXP(e->val.binary.lhs, st);
        TYPE *t2 = typeEXP(e->val.binary.rhs, st);
        if (t1->kind != t2->kind)
        {
            fprintf(stderr, "Error: type error at line %d\n, expecting type %s.", e->lineno, t1->string);
            exit(1);
        }
        else
        {
            t->kind = t1->kind;
        }
    }
    return t;
}

void printSymbolTable(SymbolTable *st)
{
    printf("TOP\n");
    while (st != NULL)
    {
        printf(" variable | type\n");
        printf("-------------------\n");
        for (int i = 0; i < HashSize; i++)
        {
            if (st->table[i] != NULL)
            {
                printf("        %s |   %s\n", st->table[i]->name, st->table[i]->type.string);
            }
        }
        st = st->parent;
        printf("\n");
    }
}
