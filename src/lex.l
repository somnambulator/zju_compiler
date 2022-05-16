%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include "ast.hpp"
#include "parser.y.hpp"
using namespace std;

int yycolumn = 1;
%}

%option noyywrap
%option yylineno

ws [ \t]
digit [0-9]
letter [_a-zA-Z]
INT [+-]?(0|[1-9]+{digit}*)
FLOAT [+-]?({digit}*\.?{digit}+|{digit}+\.)
ID {letter}[_0-9a-zA-Z]*
RELOP 	">"|"<"|">="|"<="|"=="|"!="
IF "if"
ELSE "else"
WHILE "while"
TYPE "int"|"float"
STRUCT "struct"
DEF "def"
MAIN "main"
RETURN "return"
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

{ws}+ { ; }
\n|\r { ; }
{IF} { yylval.Str = new std::string(yytext); return IF;}
{ELSE} { yylval.Str = new std::string(yytext); return ELSE; }
{WHILE} { yylval.Str = new std::string(yytext); return WHILE; }
{TYPE} { yylval.Str = new std::string(yytext); return TYPE; }
{STRUCT} { yylval.Str = new std::string(yytext); return STRUCT; }
{RELOP} { yylval.Str = new std::string(yytext); return RELOP; }

{DEF} { yylval.Str = new std::string(yytext); return DEF; }
{RETURN} { yylval.Str = new std::string(yytext); return RETURN; }
{MAIN} { yylval.Str = new std::string(yytext); return MAIN; }
{FUNCSPEC} { yylval.Str = new std::string(yytext); return FUNCSPEC; }

{ADD} { yylval.op = new std::string(yytext); return ADD; }
{SUB} { yylval.op = new std::string(yytext); return SUB; }
{MUL} { yylval.op = new std::string(yytext); return MUL; }
{DIV} { yylval.op = new std::string(yytext); return DIV; }
{AND} { yylval.op = new std::string(yytext); return AND; }
{OR} { yylval.op = new std::string(yytext); return OR; }
{NOT} { yylval.op = new std::string(yytext); return NOT; }

{DOT} { yylval.op = new std::string(yytext); return DOT; }
{SEMI} { yylval.op = new std::string(yytext); return SEMI; }
{COMMA} { yylval.Str = new std::string(yytext); return COMMA; }
{COLON} { yylval.Str = new std::string(yytext); return COLON; }
{ASSIGNOP} { yylval.op = new std::string(yytext); return ASSIGNOP; }

{LP} { yylval.op = new std::string(yytext); return LP; }
{RP} { yylval.op = new std::string(yytext); return RP; }
{LB} { yylval.op = new std::string(yytext); return LB; }
{RB} { yylval.op = new std::string(yytext); return RB; }
{LC} { yylval.Str = new std::string(yytext); return LC; }
{RC} { yylval.Str = new std::string(yytext); return RC; }
{INT} { yylval.int_val = atoi(yytext); return INT;}
{FLOAT} { yylval.float_val = atof(yytext); return FLOAT;}
{ID} { yylval.name = new std::string(yytext); return ID; }

. { ; }
%%