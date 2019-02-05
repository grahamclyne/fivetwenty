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
	#include "pretty.h"

#line 50 "parser.tab.c" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tVAR = 258,
    tWHILE = 259,
    tREAD = 260,
    tELSE = 261,
    tIF = 262,
    tPRINT = 263,
    tEQ = 264,
    tLEQ = 265,
    tGEQ = 266,
    tNEQ = 267,
    tAND = 268,
    tOR = 269,
    tBOOLEAN = 270,
    tSTRING = 271,
    tINT = 272,
    tFLOAT = 273,
    tINTVAL = 274,
    tIDENTIFIER = 275,
    tFLOATVAL = 276,
    tSTRINGVAL = 277,
    tTRUE = 278,
    tFALSE = 279,
    tCOMMENT = 280
  };
#endif
/* Tokens.  */
#define tVAR 258
#define tWHILE 259
#define tREAD 260
#define tELSE 261
#define tIF 262
#define tPRINT 263
#define tEQ 264
#define tLEQ 265
#define tGEQ 266
#define tNEQ 267
#define tAND 268
#define tOR 269
#define tBOOLEAN 270
#define tSTRING 271
#define tINT 272
#define tFLOAT 273
#define tINTVAL 274
#define tIDENTIFIER 275
#define tFLOATVAL 276
#define tSTRINGVAL 277
#define tTRUE 278
#define tFALSE 279
#define tCOMMENT 280

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "mini.y" /* yacc.c:1909  */

	int int_val;
	char *string_val;
	float float_val;
	char charconst;
	char *comment_val;
	EXP *exp;
	char* bool_val;
	TYPE *type;
	STATEMENT *statement;
	PROGRAM *program;

#line 125 "parser.tab.c" /* yacc.c:1909  */
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
