%{

#include <stdio.h>
#include <stdlib.h>
#include "tree.h" 
extern int yylineno;
extern int g_tokens;
extern char *yytext;
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
	int bool_val;
	TYPE *type;
	STATEMENT *statement;
}

%type <exp> exp
%type <type> type 
%type <statement> statements statement assignment ifstatement elseifstatement comment elsestatement
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
%left '+' '-'

%start statements

%error-verbose
%locations
%% 


statements : statement statements { $$ = $1; $$->next = $2; }
	| %empty { $$ = NULL; }
	;

statement : tREAD '(' tIDENTIFIER ')' ';' { $$ = makeSTATEMENT_read($3); }
	| tPRINT '(' exp ')' ';' { $$ = makeSTATEMENT_print($3); }
	| assignment { $$ = $1; } 
	| ifstatement { $$ = $1;}
	| tWHILE '(' exp ')' '{' statements '}' { $$ = makeSTATEMENT_while($3, $6); }
	| comment 
	; 

ifstatement : tIF '(' exp ')'  '{' statements '}' elsestatement { $$ = makeSTATEMENT_if($3, $6); }
	| tIF '(' exp ')'  '{' statements '}'  elseifstatement { $$ = makeSTATEMENT_if($3, $6);}
	;

elseifstatement : tELSE tIF '(' exp ')'  '{' statements '}'  elseifstatement { $$ = makeSTATEMENT_if($4, $7); $$ = $9; }
	| tELSE tIF '(' exp ')'  '{' statements '}'  elsestatement { $$ = makeSTATEMENT_if($4, $7); $$ = $9; }
	;

elsestatement : tELSE '{' statements '}' { $$ = $3; }
	| %empty { $$ = NULL; }
	;

assignment : tVAR tIDENTIFIER ':' type '=' exp ';' { $$ = makeSTATEMENT_declassign($2, $4, $6); }
	| tIDENTIFIER '=' exp ';' { $$ = makeSTATEMENT_assign($1, $3); }
	| tVAR tIDENTIFIER ':' type ';' { $$ = makeSTATEMENT_decl($2, $4); }
	;

comment : tCOMMENT tIDENTIFIER comment { $$ = NULL; }
	| tIDENTIFIER { $$ = NULL; }
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
