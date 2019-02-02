#include <string.h>
#include <stdio.h>
void yyparse();
int yylex();
int yyval();
char *yytext;
int g_tokens = 0;
int main(int argc, char *argv[])
{
    g_tokens = 0;
    if (strcmp("tokens", argv[1]) == 0)
    {
        g_tokens = 1;
        while(yylex()) {}
        return 0;
    }
    else if (strcmp("scan", argv[1]) == 0) {
        int x = yylex();
        while(yylex() != 0) {
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
}