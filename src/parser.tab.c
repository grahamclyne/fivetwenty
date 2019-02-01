/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_C_INCLUDED
# define YY_YY_PARSER_TAB_C_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 16 "mini.y" /* yacc.c:1909  */

	#include <stdbool.h>
	#include "tree.h"

#line 49 "parser.tab.c" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tVAR = 258,
    tWHILE = 259,
    tFLOAT = 260,
    tREAD = 261,
    tELSE = 262,
    tBOOLEAN = 263,
    tINT = 264,
    tIF = 265,
    tPRINT = 266,
    tCHARCONST = 267,
    tSTRING = 268,
    tCOMMENT = 269,
    tEQ = 270,
    tLEQ = 271,
    tGEQ = 272,
    tNEQ = 273,
    tAND = 274,
    tOR = 275,
    tINTVAL = 276,
    tIDENTIFIER = 277,
    tFLOATVAL = 278,
    tSTRINGVAL = 279,
    tTRUE = 280,
    tFALSE = 281
  };
#endif
/* Tokens.  */
#define tVAR 258
#define tWHILE 259
#define tFLOAT 260
#define tREAD 261
#define tELSE 262
#define tBOOLEAN 263
#define tINT 264
#define tIF 265
#define tPRINT 266
#define tCHARCONST 267
#define tSTRING 268
#define tCOMMENT 269
#define tEQ 270
#define tLEQ 271
#define tGEQ 272
#define tNEQ 273
#define tAND 274
#define tOR 275
#define tINTVAL 276
#define tIDENTIFIER 277
#define tFLOATVAL 278
#define tSTRINGVAL 279
#define tTRUE 280
#define tFALSE 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "mini.y" /* yacc.c:1909  */

	int int_val;
	char *string_val;
	float float_val;
	char charconst;
	EXP *exp;
	bool bool_val;
	STATEMENT *statement;

#line 123 "parser.tab.c" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_C_INCLUDED  */
