%{
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
extern int g_tokens;
extern char *yytext;
extern EXP *root;
void yyerror(const char *s) { fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); exit(1); }
int yylex();

%}

%code requires
{
	#include <stdbool.h>
	#include "tree.h"
}

%union {
	int int_val;
	char *string_val;
	float float_val;
	char charconst;
	EXP *exp;
	STATEMENT *statement;
}

%type <exp> program exp tTRUE tFALSE type tBOOLEAN tINT tBOOLEAN tFLOAT tSTRING

%type <statement> statements statement assignment ifstatement elseifstatement comment
%token	tVAR tWHILE tTRUE tFALSE tFLOAT tREAD tELSE 
		tBOOLEAN tINT tIF tPRINT tCHARCONST 
		tSTRING tCOMMENT tEQ tLEQ tGEQ tNEQ tAND tOR
%token <int_val> tINTVAL
%token <string_val> tIDENTIFIER
%token <float_val> tFLOATVAL
%token <string_val> tSTRINGVAL


%left tOR
%left tAND 
%left tEQ tNEQ
%left tGEQ tLEQ '<' '>'
%left '*' '/'
%left '+' '-'

%start program

%error-verbose
%locations
%% 
program : statements { root = $1; }
	;
statements : statement statements { $$ = $2; $$->next = $1; }
	| %empty { $$ = NULL; }
	;

statement : tREAD '(' tIDENTIFIER ')' ';' { $$ = makeSTATEMENT_read($3); }
	| tPRINT '(' exp ')' ';' { $$ = makeSTATEMENT_print($3); }
	| assignment { $$ = $1; } 
	| ifstatement { $$ = $1;}
	| tWHILE '(' exp ')' '{' statements '}' { $$ = makeSTATEMENT_while($3, $6); }
	| comment
	; 

ifstatement : tIF '(' exp ')'  '{' statements '}' { $$ = makeSTATEMENT_if($3, $6); }
	| tIF '(' exp ')'  '{' statements '}'  elseifstatement { $$ = makeSTATEMENT_ifelse($3, $6, $8);}
	| tIF '(' exp ')'  '{' statements '}'  tELSE '{' statements '}' { $$ = makeSTATEMENT_ifelse($3, $6, $10); }
	;

elseifstatement : tELSE tIF '(' exp ')'  '{' statements '}'  elseifstatement { $$ = makeSTATEMENT_elseif($3, $6); }
	| tELSE tIF '(' exp ')'  '{' statements '}' { $$ = makeSTATEMENT_if($3, $6); }
	| tELSE tIF '(' exp ')'  '{' statements '}'  tELSE '{' statements '}' { $$ = makeSTATEMENT_if($3, $6); }
	;

assignment : tVAR tIDENTIFIER ':' type '=' exp ';' { $$ = makeSTATEMENT_assign($3, $6); }
	| tIDENTIFIER '=' exp ';' { $$ = makeSTATEMENT_assign($3, $6); }
	| tVAR tIDENTIFIER ':' type ';' { $$ = makeSTATEMENT_assign($3, $6); }
	;

comment : tCOMMENT tIDENTIFIER comment { $$ = NULL; }
	| tIDENTIFIER { $$ = NULL; }
	;

type : tBOOLEAN { $$ = $1; }
	| tINT  { $$ = $1; }
	| tFLOAT  { $$ = $1; }
	| tSTRING  { $$ = $1; }
	;

exp : tIDENTIFIER { $$ = makeEXP_identifier($1); }
 	| tINTVAL { $$ = makeEXP_intLiteral($1); }
 	| tFLOATVAL { $$ = makeEXP_floatLiteral($1); }
	| tTRUE { $$ = makeEXP_boolLiteral($1); }
	| tSTRINGVAL { $$ = makeEXP_stringLiteral($1); }
	| tFALSE  { $$ = makeEXP_boolLiteral($1); }
	| exp '+' exp { $$ = makeEXP_binary(k_expressionKindAddition, $1, $3); }
	| exp '*' exp { $$ = makeEXP_binary(k_expressionKindMultiplication, $1, $3); }
	| exp '-' exp { $$ = makeEXP_binary(k_expressionKindSubtraction, $1, $3); }
	| exp '/' exp { $$ = makeEXP_binary(k_expressionKindDivision, $1, $3); }
	| exp tEQ exp { $$ = makeEXP_binary(k_expressionKindEquality, $1, $3); }
	| exp tGEQ exp { $$ = makeEXP_binary(k_expressionKindGreaterThan, $1, $3); }
	| exp tLEQ exp { $$ = makeEXP_binary(k_expressionKindLessThan, $1, $3); }
	| exp tNEQ exp { $$ = makeEXP_binary(k_expressionKindAddition, $1, $3); }
	| exp '<' exp { $$ = makeEXP_binary(k_expressionKindAddition, $1, $3); }
	| exp '>' exp { $$ = makeEXP_binary(k_expressionKindAddition, $1, $3); }
	| exp tAND exp { $$ = makeEXP_binary(k_expressionKindAddition, $1, $3); }
	| exp tOR exp { $$ = makeEXP_binary(k_expressionKindAddition, $1, $3); }
	| '-' exp %prec '-' { $$ = $2; }
	| '(' exp ')'{ $$ = $2; }
	;

%%
