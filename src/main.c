#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "pretty.h"
#include "tree.h"
#include "symbol.h"

void yyparse();
int yylex();
int yyval();
char *yytext;
int g_tokens;
STATEMENT *root;
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("enter tokens|scan|parse|pretty|symbol|typecheck\n");
        return -1;
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
        yyparse();
        printf("OK\n");
        return 0;
    }
    else if (strcmp("pretty", argv[1]) == 0)
    {
        yyparse();
        prettySTATEMENT(root);
    }
    else if (strcmp("symbol", argv[1]) == 0)
    {
        yyparse();
        SymbolTable *st = initSymbolTable();
        symSTATEMENT(root, st);
        printSymbolTable(st);
    }
    else if (strcmp("typecheck", argv[1]) == 0)
    {
    }
    else if (strcmp("codegen", argv[1]) == 0)
    {
        char *filename = argv[1];
        for (int i = 0; i < sizeof(filename) / sizeof(filename[0]); i++)
        {
            if (filename[i] == '.')
            {
                filename[i + 1] = 'c';
                filename[i + 2] = '\0';
                break;
            }
        }
        //  fgets(filename, 10, stdin);
        //  printf("%s", filename);

        yyparse();
        freopen("output.c", "w", stdout);
        printf("#include <stdbool.h>\n");
        printf("#include <stdlib.h>\n");
        printf("int main() {\n");
        prettySTATEMENT(root);
        printf("}");
        fclose(stdout);
        return 0;
    }
    else
    {
        return 0;
    }
}