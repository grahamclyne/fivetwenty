
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

int defSymbol(SymbolTable *st, char *name)
{
    int i = Hash(name);
    SYMBOL *s;
    for (s = st->table[i]; s; s = s->next)
    {
        if (strcmp(s->name, name) == 0)
            return 1;
    }
    return 0;
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
        symSTATEMENT(s->val.loop.body, st);
        symEXP(s->val.loop.condition, st);
        break;
    case k_statementKindPrint:
        symEXP(s->val.print.exp, st);
        break;
    case k_statementKindRead:
        if(!defSymbol(st,s->val.read.id)) {
            printf("error at %d, %s\n", s->lineno, s->val.read.id);
            exit(-1);
        }
        break;
    case k_statementKindIf:
        symEXP(s->val.ifstatement.condition, st);
        symSTATEMENT(s->val.ifstatement.body, st);
        if(s->val.ifstatement.elsestatement != NULL) {
            symSTATEMENT(s->val.ifstatement.elsestatement, st);
        }
        break;
    case k_statementKindElse:
        symSTATEMENT(s->val.elsestatement.body,st);
        break;
    case k_statementKindElseIf:
        symEXP(s->val.elseifstatement.condition, st);
        symSTATEMENT(s->val.elseifstatement.body,st);
        if(s->val.elseifstatement.elsestatement != NULL) {
            symSTATEMENT(s->val.elseifstatement.elsestatement,st);
        }
        break;
    case k_statementKindAssign:
        if(!defSymbol(st,s->val.assignment.id)){
            printf("error");
            exit(-1);
        }
        symEXP(s->val.assignment.exp, st);
        break;
    case k_statementKindDeclaration:
        putSymbol(st, s->val.decl.id, s->val.decl.type);
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
    k_expressionKindIdentifier:
        if(!defSymbol(st,e->val.id)) {
            printf("error");
            exit(-1);
        }
        break;
    k_expressionKindIntLiteral:
        break;
    k_expressionKindFloatLiteral:
        break;
    k_expressionKindStringLiteral:
        break;
    k_expressionKindNot:
        symEXP(e->val.unary.exp,st);
        break;
    k_expressionKindNegative:
        symEXP(e->val.unary.exp,st);
        break;
    default:
        symEXP(e->val.binary.lhs, st);
        symEXP(e->val.binary.rhs, st);
    }
}
void printSymbolTable(SymbolTable *st)
{
    for (int i = 0; i < HashSize; i++)
    {
        if(st->table[i] != NULL) {
        printf("%s | %s\n", st->table[i]->name, st->table[i]->type.string);
        }
    }
}
