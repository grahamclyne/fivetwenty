#ifndef CODE_H
#define CODE_H


#include "tree.h"
#include "symbol.h"

void codeSTATEMENT(STATEMENT *s, SymbolTable *st);
void codeEXP(EXP *exp, SymbolTable *st);
void codeTYPE(TYPE *t); 
SYMBOL* codePRINT(EXP *exp, SymbolTable *st);


#endif