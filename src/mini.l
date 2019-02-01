%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
void yyerror();
%}

%option yylineno
%option noinput
%option nounput

%%

[ \t\n\r]+ /* this is ignored */

var		{ if (g_tokens) printf("tVAR\n"); return  tVAR;}
string	{ if (g_tokens) printf("tSTRING\n"); return  tSTRING;}
while	{ if (g_tokens) printf("tWHILE\n"); return  tWHILE;}
true	{ if (g_tokens) printf("tTRUE \n"); return  tTRUE;}
false	{ if (g_tokens) printf("tFALSE \n"); return  tFALSE;}
float	{ if (g_tokens) printf("tFLOAT \n"); return  tFLOAT;}
boolean	{ if (g_tokens) printf("tBOOLEAN \n"); return  tBOOLEAN;}
read	{ if (g_tokens) printf("tREAD \n"); return  tREAD;}
int		{ if (g_tokens) printf("tINT \n"); return  tINT;}
if		{ if (g_tokens) printf("tIF \n"); return  tIF;}
else 	{ if (g_tokens) printf("tELSE \n"); return  tELSE;}
print	{ if (g_tokens) printf("tPRINT \n"); return  tPRINT;}
"*"		{ if (g_tokens) printf("tTIMES \n"); return  '*' ;}
"/"    	{ if (g_tokens) printf("tSLASH \n"); return  '/' ;}
"+"    	{ if (g_tokens) printf("tPLUS \n"); return  '+' ;}
"-"    	{ if (g_tokens) printf("tMINUS \n"); return  '-' ;}
"("    	{ if (g_tokens) printf("tLEFTPAREN \n"); return  '(' ;}
")" 	{ if (g_tokens) printf("tRIGHTPAREN \n"); return  ')' ;}
":" 	{ if (g_tokens) printf("tCOLON \n"); return  ':' ;}
"=" 	{ if (g_tokens) printf("tASSIGN \n"); return  '=' ;}
";"		{ if (g_tokens) printf("tSEMICOLON \n"); return  ';' ;}
"}" 	{ if (g_tokens) printf("tRIGHTBRACE \n"); return  '}' ;}
"{"		{ if (g_tokens) printf("tLEFTBRACE \n"); return  '{' ;}
"<" 	{ if (g_tokens) printf("tLESSTHAN \n"); return  '<' ;}
">" 	{ if (g_tokens) printf("tGREATERTHAN \n"); return  '>' ;}
"==" 	{ if (g_tokens) printf("tEQ \n"); return  tEQ;}
"!="	{ if (g_tokens) printf("tNEQ \n"); return  tNEQ;}
">=" 	{ if (g_tokens) printf("tGEQ \n"); return  tGEQ;}
"<="	{ if (g_tokens) printf("tLEQ \n"); return  tLEQ;}
"&&" 	{ if (g_tokens) printf("tAND \n"); return  tAND;}
"||" 	{ if (g_tokens) printf("tOR \n"); return  tOR;}

0|([1-9][0-9]*) {
	yylval.int_val = atoi(yytext);
	{ if (g_tokens) printf("tINTVAL(%s) \n", yytext); return  tINTVAL;}
}

(([0]|([1-9][0-9]*))(\.[0-9]+)) {
	yylval.float_val = atof(yytext);
	{ if (g_tokens) printf("tFLOATVAL(%s)\n", yytext); return  tFLOATVAL;}
}

(["][a-zA-Z0-9_ !~`'@#$%^&*()\[\]{}<>=+\-*/:;.,?]*(\\[abnfrtv"\\])*[a-zA-Z0-9_ !~`'@#$%^&*()\[\]{}<>=+\-*/:;.,?]*["])	 { 
	yylval.string_val = strdup(yytext);
	{ if (g_tokens) printf("tSTRINGVAL(%s)\n", yytext); return  tSTRINGVAL;}
}

([a-zA-Z_]+[a-zA-Z0-9]*) {
	yylval.string_val = strdup(yytext);
	{ if (g_tokens) printf("tIDENTIFIER(%s)\n", yytext); return  tIDENTIFIER;}
	yyerror(yylval.string_val);
}

((\/\/).*) /* ignore comments */

.  { fprintf(stderr, "Error: (line %d) unexpected char ’%s’\n", yylineno, yytext);
exit(1);
}

%%
