%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include "paser.hpp"
using namespace std;

int yycolumn = 1;
%}

%option noyywrap

ws [ \t]
digit [0-9]
letter [_a-zA-Z]
INT [+-]?(0|[1-9]+{digit}*)
FLOAT [+-]?({digit}*\.?{digit}+|{digit}+\.)
ID {letter}[_0-9a-zA-Z]*
RELOP 	>|<|>=|<=|==|!=
IF if
ELSE else
WHILE while
TYPE int|float
STRUCT struct
DEF def
MAIN main
RETURN return
ADD "+"
SUB "-"
MUL "*"
DIV "/"
AND "&&"
OR "||"
NOT "!"
DOT "."
SEMI ";"
COLON ":"
FUNCSPEC "->"
COMMA ","
ASSIGNOP ":="
LP "("
RP ")"
LB "["
RB "]"
LC "{"
RC "}"

%%

{ws}+ { }
\n|\r { }
{IF} { return IF;}
{ELSE} { return ELSE; }
{WHILE} {  return WHILE; }
{TYPE} { return TYPE; }
{STRUCT} { return STRUCT; }
{RELOP} { return RELOP; }

{DEF} { return def; }
{RETURN} { return RETURN; }
{MAIN} { return MAIN; }

{ADD} { return ADD; }
{SUB} { return SUB; }
{MUL} { return MUL; }
{DIV} { return DIV; }
{AND} { return AND; }
{OR} { return OR; }
{NOT} { return NOT; }

{DOT} { return DOT; }
{SEMI} { return SEMI; }
{COMMA} { return COMMA; }
{COLON} { return COLON; }
{ASSIGNOP} { return ASSIGNOP; }

{LP} { return LP; }
{RP} { return RP; }
{LB} { return LB; }
{RB} { return RB; }
{LC} { return LC; }
{RC} { return RC; }
{INT} { yyval.int_val = atoi(yytext); return INT;}
{FLOAT} { yyval.float_val = atof(yytext); return FLOAT;}
{ID} { yyval.name = new string(yytext); return ID}
%%