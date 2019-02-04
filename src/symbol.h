#include "tree.h"

#define HashSize 317

typedef enum{classSym,fieldSym,methodSym,formalSym,localSym} SymbolKind;

typedef struct SYMBOL {
    char *name;
    SymbolKind kind;
    union {
      struct CLASS *classS;
      struct FIELD *fieldS;
      struct METHOD *methodS;
      struct FORMAL *formalS;
      struct LOCAL *localS;
    } val;
    struct SYMBOL *next;
} SYMBOL; 

typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *next;
} SymbolTable;

SymbolTable *initSymbolTable();

SymbolTable *scopeSymbolTable(SymbolTable *t);

SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind);

SYMBOL *getSymbol(SymbolTable *t, char *name);

int defSymbol(SymbolTable *t, char *name);

//int subClass(CLASS *sub, CLASS *super);

