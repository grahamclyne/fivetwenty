#include <stdlib.h>
#include "tree.h"

extern int yylineno;
PROGRAM *makePROGRAM(STATEMENT *root)
{
	PROGRAM *p = malloc(sizeof(PROGRAM));
	p->next = root;
}
EXP *makeEXP_identifier(char *identifier)
{
	EXP *e = malloc(sizeof(EXP));
	e->lineno = yylineno;
	e->kind = k_expressionKindIdentifier;
	e->val.stringLiteral = identifier;
	return e;
}

EXP *makeEXP_intLiteral(int intLiteral)
{
	EXP *e = malloc(sizeof(EXP));
	e->lineno = yylineno;
	e->kind = k_expressionKindIntLiteral;
	e->val.intLiteral = intLiteral;
	return e;
}

EXP *makeEXP_binary(ExpressionKind op, EXP *lhs, EXP *rhs)
{
	EXP *e = malloc(sizeof(EXP));
	e->lineno = yylineno;
	e->kind = op;
	e->val.binary.lhs = lhs;
	e->val.binary.rhs = rhs;
	return e;
}

EXP *makeEXP_stringLiteral(char *stringLiteral)
{
	EXP *e = malloc(sizeof(EXP));
	e->lineno = yylineno;
	e->kind = k_expressionKindStringLiteral;
	e->val.stringLiteral = stringLiteral;
	return e;
}

EXP *makeEXP_floatLiteral(float floatLiteral)
{
	EXP *e = malloc(sizeof(EXP));
	e->lineno = yylineno;
	e->kind = k_expressionKindFloatLiteral;
	e->val.floatLiteral = floatLiteral;
	return e;
}

EXP *makeEXP_booleanLiteral(int boolLiteral)
{
	EXP *e = malloc(sizeof(EXP));
	e->lineno = yylineno;
	e->kind = k_expressionKindIntLiteral;
	e->val.boolLiteral = boolLiteral;
	return e;
}

STATEMENT *makeSTATEMENT_assign(char *id, EXP *exp)
{
	STATEMENT *s = malloc(sizeof(STATEMENT));
	s->lineno = yylineno;
	s->kind = k_statementKindAssign;
	s->val.assignment.id = id;
	s->val.assignment.exp = exp;
	return s;
}

STATEMENT *makeSTATEMENT_read(char *id)
{
	STATEMENT *s = malloc(sizeof(STATEMENT));
	s->lineno = yylineno;
	s->kind = k_statementKindRead;
	s->val.read.id = id;
	return s;
}

STATEMENT *makeSTATEMENT_decl(char *id, TYPE *type)
{
	STATEMENT *s = malloc(sizeof(STATEMENT));
	s->lineno = yylineno;
	s->kind = k_statementKindDeclaration;
	s->val.decl.id = id;
	s->val.decl.type = type;
	return s;
}

STATEMENT *makeSTATEMENT_declassign(char *id, TYPE *type, EXP *value)
{
	STATEMENT *s = malloc(sizeof(STATEMENT));
	s->lineno = yylineno;
	s->kind = k_statementKindDeclarationAssignment;
	s->val.declassign.id = id;
	s->val.declassign.type = type;
	s->val.declassign.exp = value;
	return s;
}

STATEMENT *makeSTATEMENT_while(EXP *condition, STATEMENT *body)
{
	STATEMENT *s = malloc(sizeof(STATEMENT));
	s->lineno = yylineno;
	s->kind = k_statementKindWhile;
	s->val.loop.condition = condition;
	s->val.loop.body = body;
	return s;
}

STATEMENT *makeSTATEMENT_print(EXP *exp)
{
	STATEMENT *s = malloc(sizeof(STATEMENT));
	s->lineno = yylineno;
	s->kind = k_statementKindPrint;
	s->val.print.exp = exp;
	return s;
}

STATEMENT *makeSTATEMENT_if(EXP *exp, STATEMENT *statements)
{
	STATEMENT *s = malloc(sizeof(STATEMENT));
	s->lineno = yylineno;
	s->kind = k_statementKindIf;
	s->val.ifstatement.condition = exp;
	s->val.ifstatement.body = statements;
	return s;
}
STATEMENT *makeSTATEMENT_else(STATEMENT *body)
{
	STATEMENT *s = malloc(sizeof(STATEMENT));
	s->lineno = yylineno;
	s->kind = k_statementKindElse;
	s->val.elsestatement.body = body;
	return s;
}
STATEMENT *makeSTATEMENT_elseif(EXP *exp, STATEMENT *body)
{
	STATEMENT *s = malloc(sizeof(STATEMENT));
	s->lineno = yylineno;
	s->kind = k_statementKindElseIf;
	s->val.elseifstatement.condition = exp;
	s->val.elseifstatement.body = body;
	return s;
}
TYPE *makeTYPEbool()
{
	TYPE *t = malloc(sizeof(TYPE));
	t->lineno = yylineno;
	t->kind = k_typeBool;
	return t;
}

TYPE *makeTYPEint()
{
	TYPE *t = malloc(sizeof(TYPE));
	t->lineno = yylineno;
	t->kind = k_typeInt;
	return t;
}

TYPE *makeTYPEfloat()
{
	TYPE *t = malloc(sizeof(TYPE));
	t->lineno = yylineno;
	t->kind = k_typeFloat;
	return t;
}

TYPE *makeTYPEstring()
{
	TYPE *t = malloc(sizeof(TYPE));
	t->lineno = yylineno;
	t->kind = k_typeString;
	return t;
}
