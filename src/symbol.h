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
    struct SymbolTable *parent;
} SymbolTable;

SymbolTable *initSymbolTable();

SymbolTable *scopeSymbolTable(SymbolTable *t);

SYMBOL *putSymbol(SymbolTable *t, char *name, TYPE *type);

SYMBOL *getSymbol(SymbolTable *t, char *name);

int defSymbol(SymbolTable *t, char *name);

void symSTATEMENT(STATEMENT *s, SymbolTable *st);
void symEXP(EXP *exp, SymbolTable *st);
void printSymbolTable();