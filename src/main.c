#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "pretty.h"
#include "tree.h"
#include "symbol.h"
#include "code.h"

void yyparse();
int yylex();
int yyval();
char *yytext;
int g_tokens;
STATEMENT *root;
int main(int argc, char *argv[])
{
    yyparse();
    if (argc < 2)
    {
        printf("enter tokens|scan|parse|pretty|symbol|typecheck|codegen\n");
        return 1;
    }
    g_tokens = 0;
    if (strcmp("tokens", argv[1]) == 0)
    {
        g_tokens = 1;
        while (yylex())
        {
        }
        return 0;
    }
    else if (strcmp("scan", argv[1]) == 0)
    {
        int x = yylex();
        while (yylex() != 0)
        {
        }
        printf("OK\n");
        return 0;
    }
    else if (strcmp("parse", argv[1]) == 0)
    {
        printf("OK\n");
        return 0;
    }
    else if (strcmp("pretty", argv[1]) == 0)
    {
        //COMMENTS DO NOT WORK!!!
        prettySTATEMENT(root);
    }
    else if (strcmp("symbol", argv[1]) == 0)
    {
        SymbolTable *st = initSymbolTable();
        symSTATEMENT(root, st);
        printSymbolTable(st);
    }
    else if (strcmp("typecheck", argv[1]) == 0)
    {
        SymbolTable *st = initSymbolTable();
        symSTATEMENT(root,st);
        typeSTATEMENT(root,st);
        printf("OK\n");
        return 0;
    }
    else if (strcmp("codegen", argv[1]) == 0)
    {
        char *filename = argv[2];
        char *output = strcat(filename, ".c");
        FILE *fptr = fopen(output, "w");
        freopen(output, "w", stdout);
        printf("#include<stdbool.h>\n");
        printf("int main() {\n");
        codeSTATEMENT(root);
        printf("}");
        fclose(fptr);
        return 0;
    }
    else
    {
        return 0;
    }
}