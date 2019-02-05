
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
    t->typechecked = 0;
    for (i = 0; i < HashSize; i++)
        t->table[i] = NULL;
    t->parent = NULL;
    t->children = malloc(10 * sizeof(SymbolTable));
    return t;
}

SymbolTable *scopeSymbolTable(SymbolTable *st)
{
    SymbolTable *t;
    t = initSymbolTable();
    t->parent = st;
    int i = 0;
    while (st->children[i] != NULL)
    {
        i++;
    }
    st->children[i] = t;
    return t;
}

SymbolTable *getTypeScope(SymbolTable *st)
{
    if (st->typechecked == 0)
    {
        st->typechecked = 1;
        return st;
    }
    else
    {
        int i = 0;
        while (st->children[i] != NULL)
        {
            if (st->children[i]->typechecked == 0)
            {
                st->children[i]->typechecked = 1;
                return st->children[i];
            }
            i++;
        }
    }
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
        if (getSymbol(st, s->val.decl.id) != NULL)
        {
            fprintf(stderr, "Error: on line %d, %s already defined.\n", s->lineno, s->val.decl.id);
            exit(1);
        }
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
    case k_expressionKindNot:
        symEXP(e->val.unary.exp, st);
        break;
    case k_expressionKindNegative:
        symEXP(e->val.unary.exp, st);
        break;
    case k_expressionKindBracketed:
        symEXP(e->val.bracketed.exp, st);
        break;
    case k_expressionKindBinary:
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
        SymbolTable *t = getTypeScope(st);
        typeSTATEMENT(s->val.loop.body, t);
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
        SymbolTable *tif = getTypeScope(st);
        typeSTATEMENT(s->val.ifstatement.body, tif);
        if (s->val.ifstatement.elsestatement != NULL)
        {
            SymbolTable *telse = getTypeScope(st);
            typeSTATEMENT(s->val.ifstatement.elsestatement, telse);
        }
        break;
    case k_statementKindElse:
        typeSTATEMENT(s->val.elsestatement.body, st);
        break;
    case k_statementKindElseIf:
        typeEXP(s->val.elseifstatement.condition, st);
        SymbolTable *telseif = getTypeScope(st);
        typeSTATEMENT(s->val.elseifstatement.body, telseif);
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

//kinds are coded from 0 to 3 see tree.h
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
        t->kind = 0;
        t->string = "int";
        break;
    case k_expressionKindFloatLiteral:
        t->kind = 1;
        t->string = "float";
        break;
    case k_expressionKindBooleanLiteral:
        t->kind = 2;
        t->string = "boolean";
        break;
    case k_expressionKindStringLiteral:
        t->kind = 3;
        t->string = "string";
        break;
    case k_expressionKindNot:
        t->kind = 2;
        TYPE *tunary = typeEXP(e->val.unary.exp, st);
        if (t->kind != tunary->kind)
        {
            fprintf(stderr, "Error: type error at line %d, expecting type boolean", e->lineno);
            exit(1);
        }
        break;
    case k_expressionKindNegative:;
        TYPE *tneg = typeEXP(e->val.unary.exp, st);
        if (0 != tneg->kind && 1 != tneg->kind)
        {
            fprintf(stderr, "Error: type error at line %d, expecting type int or float", e->lineno);
            exit(1);
        }
        t->kind = tneg->kind;
        break;
    case k_expressionKindBracketed:;
        TYPE *tbrack = typeEXP(e->val.bracketed.exp, st);
        t->kind = tbrack->kind;
        break;
    case k_expressionKindBinary:;
        TYPE *t1 = typeEXP(e->val.binary.lhs, st);
        TYPE *t2 = typeEXP(e->val.binary.rhs, st);
        //cast int to float
        if ((t1->kind == 0 && t2->kind == 1) || (t1->kind == 1 && t2->kind == 0))
        {
            t->kind = 1;
        }
        //only string concat
        else if (t1->kind == 3 && t2->kind == 3 && strcmp(e->val.binary.opera, "+") == 0)
        {
        }
        //assure only boolean operators
        else if ((t1->kind != 2 || t2->kind != 2) &&
                 (strcmp(e->val.binary.opera, "||") == 0 || strcmp(e->val.binary.opera, "&&") == 0))
        {
            fprintf(stderr, "Error: type error at line %d, expecting boolean values for boolean operators\n", e->lineno);
            exit(1);
        }
        else if ((t1->kind == t2->kind) && ((strcmp(e->val.binary.opera, "==") == 0) ||
                                            (strcmp(e->val.binary.opera, "<=") == 0) ||
                                            (strcmp(e->val.binary.opera, ">=") == 0) ||
                                            (strcmp(e->val.binary.opera, ">") == 0) ||
                                            (strcmp(e->val.binary.opera, "<") == 0) ||
                                            (strcmp(e->val.binary.opera, "!=") == 0)))
        {
            t->kind = 2;
        }

        else if (t1->kind != t2->kind)
        {
            fprintf(stderr, "Error: type error at line %d.\n", e->lineno);
            exit(1);
        }
        else
        {
            t->kind = t1->kind;
        }
        break;
    }
    return t;
}

void printSymbolTable(SymbolTable *st, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("\t");
    }
    printf(" variable | type\n");
    for (int i = 0; i < depth; i++)
    {
        printf("\t");
    }
    printf("-------------------\n");
    for (int i = 0; i < HashSize; i++)
    {
        if (st->table[i] != NULL)
        {
            for (int i = 0; i < depth; i++)
            {
                printf("\t");
            }
            printf("        %s |   %s\n", st->table[i]->name, st->table[i]->type.string);
        }
    }
    printf("\n");
    int i = 0;
    depth++;
    while (st->children[i])
    {
        printSymbolTable(st->children[i], depth);
        i++;
    }
}
