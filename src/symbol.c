
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "symbol.h"

int Hash(char *str)
{ unsigned int hash = 0;
  while (*str) hash = (hash << 1) + *str++; 
  return hash % HashSize;
}

SymbolTable *initSymbolTable()
{ SymbolTable *t;
  int i;
  t = malloc(sizeof(SymbolTable));
  for (i=0; i < HashSize; i++) t->table[i] = NULL;
  t->next = NULL;
  return t;
}

SymbolTable *scopeSymbolTable(SymbolTable *s)
{ SymbolTable *t;
  t = initSymbolTable();
  t->next = s;
  return t;
}

SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return s;
  }
  s = malloc(sizeof(SYMBOL));
  s->name = name;
  s->kind = kind;
  s->next = t->table[i];
  t->table[i] = s;
  return s;
}
 
SYMBOL *getSymbol(SymbolTable *t, char *name)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return s;
  }
  if (t->next==NULL) return NULL;
  return getSymbol(t->next,name);
}
 
int defSymbol(SymbolTable *t, char *name)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return 1;
  }
  return 0;
}
