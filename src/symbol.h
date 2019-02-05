#include "tree.h"

#define HashSize 317

typedef enum {exp, type} SymbolKind;

typedef struct SYMBOL {
    char *name;
    TYPE type;
 
    struct SYMBOL *next;
} SYMBOL; 

typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    int typechecked;
    struct SymbolTable *parent;
    struct SymbolTable **children;
} SymbolTable;

SymbolTable *initSymbolTable();
SymbolTable *scopeSymbolTable(SymbolTable *t);
SYMBOL *putSymbol(SymbolTable *t, char *name, TYPE *type);
SYMBOL *getSymbol(SymbolTable *t, char *name);
void symSTATEMENT(STATEMENT *s, SymbolTable *st);
void symEXP(EXP *exp, SymbolTable *st);
void typeSTATEMENT(STATEMENT *s, SymbolTable *st);
TYPE *typeEXP(EXP *exp, SymbolTable *st);
void printSymbolTable(SymbolTable *st, int depth);