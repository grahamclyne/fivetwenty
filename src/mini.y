%{

#include <stdio.h>
#include <stdlib.h>
#include "tree.h" 
extern int yylineno;
extern int g_tokens;
extern char *yytext;
#define YYDEBUG 1
void yyerror(const char *s) { fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); exit(1); }
int yylex();
extern STATEMENT *root;
%}

%code requires
{
	#include <stdbool.h>
	#include "tree.h"
	#include "pretty.h"
}

%union {
	int int_val;
	char *string_val;
	float float_val;
	char charconst;
	EXP *exp;
	int bool_val;
	TYPE *type;
	STATEMENT *statement;
	PROGRAM *program;
}

%type <exp> exp
%type <program> program 
%type <type> type 
%type <statement>  statements statement elseifstatement declaration 
%token	tVAR tWHILE tREAD tELSE tIF tPRINT tCOMMENT tEQ tLEQ tGEQ tNEQ tAND tOR tBOOLEAN tSTRING tINT tFLOAT 
%token <int_val> tINTVAL
%token <string_val> tIDENTIFIER
%token <float_val> tFLOATVAL
%token <string_val> tSTRINGVAL
%token <bool_val> tTRUE tFALSE


%left tOR
%left tAND 
%left tEQ tNEQ
%left tGEQ tLEQ '<' '>'
%left '*' '/'
%left '+' '-' '!'

%start program 

%error-verbose
%locations
%% 
program : statements { root = $1;}
			;

statements : statements statement { $$ = $2; $$->next = $1; }
			| %empty { $$ = NULL; }
			;

statement : tREAD '(' tIDENTIFIER ')' ';' { $$ = makeSTATEMENT_read($3); }
			| tPRINT '(' exp ')' ';' { $$ = makeSTATEMENT_print($3); }
			| declaration { $$ = $1; } 
			| tIDENTIFIER '=' exp ';' { $$ = makeSTATEMENT_assign($1, $3); }
			| tIF '(' exp ')' '{' statements '}'  { $$ = makeSTATEMENT_if($3, $6); }
			| tIF '(' exp ')' '{' statements '}' elseifstatement { $$ = makeSTATEMENT_if($3, $6); $$ = $8; }
			| tWHILE '(' exp ')' '{' statements '}' { $$ = makeSTATEMENT_while($3, $6); }
			| tCOMMENT tIDENTIFIER  { $$ = NULL; }
			; 

elseifstatement : tELSE tIF '(' exp ')'  '{' statements '}' elseifstatement { $$ = makeSTATEMENT_elseif($4, $7); }
			| tELSE '{' statements '}' { $$ = makeSTATEMENT_else($3); }
			;

declaration : tVAR tIDENTIFIER ':' type '=' exp ';' { $$ = makeSTATEMENT_declassign($2, $4, $6); }
			| tVAR tIDENTIFIER ':' type ';' { $$ = makeSTATEMENT_decl($2, $4); }
			;


type : tBOOLEAN { $$ =	makeTYPEbool(); }
		| tINT  { $$ = makeTYPEint(); }
		| tFLOAT  { $$ = makeTYPEfloat(); }
		| tSTRING  { $$ = makeTYPEstring(); }
		;

exp : tIDENTIFIER { $$ = makeEXP_identifier($1); }
 		| tINTVAL { $$ = makeEXP_intLiteral($1); }
 		| tFLOATVAL { $$ = makeEXP_floatLiteral($1); }
		| tTRUE { $$ = makeEXP_booleanLiteral($1); }
		| tSTRINGVAL { $$ = makeEXP_stringLiteral($1); }
		| tFALSE  { $$ = makeEXP_booleanLiteral($1); }
		| exp '+' exp { $$ = makeEXP_binary(k_expressionKindAddition, $1, $3); }
		| exp '*' exp { $$ = makeEXP_binary(k_expressionKindMultiplication, $1, $3); }
		| exp '-' exp { $$ = makeEXP_binary(k_expressionKindSubtraction, $1, $3); }
		| exp '/' exp { $$ = makeEXP_binary(k_expressionKindDivision, $1, $3); }
		| exp tEQ exp { $$ = makeEXP_binary(k_expressionKindEquality, $1, $3); }
		| exp tGEQ exp { $$ = makeEXP_binary(k_expressionKindGreaterThanEquals, $1, $3); }
		| exp tLEQ exp { $$ = makeEXP_binary(k_expressionKindLessThan, $1, $3); }
		| exp tNEQ exp { $$ = makeEXP_binary(k_expressionKindNotEqual, $1, $3); }
		| exp '<' exp { $$ = makeEXP_binary(k_expressionKindLessThan, $1, $3); }
		| exp '>' exp { $$ = makeEXP_binary(k_expressionKindGreaterThan, $1, $3); }
		| exp tAND exp { $$ = makeEXP_binary(k_expressionKindAnd, $1, $3); }
		| exp tOR exp { $$ = makeEXP_binary(k_expressionKindOr, $1, $3); }
		| '-' exp %prec '-' { $$ = $2; }
		| '!' exp %prec '!' { $$ = $2; }
		| '(' exp ')'{ $$ = $2; }
		;

%%
