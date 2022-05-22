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
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}

%option noyywrap
%option yylineno

ws [ \t]
digit [0-9]
letter [_a-zA-Z]
INT (0|[1-9]+{digit}*)
FLOAT ({digit}*\.?{digit}+|{digit}+\.)
ID {letter}[_0-9a-zA-Z]*
CHAR \'.\'
STRING \"(\\.|[^"\\])*\"

RELOP 	">"|"<"|">="|"<="|"=="|"!="
IF "if"
ELIF "elif"
ELSE "else"
WHILE "while"
FOR "for"
IN "in"
RANGE "range"
TYPE "int"|"float"|"bool"|"void"|"char"|"string"
STRUCT "struct"
DEF "def"
VAR "var"
STMT "stmt"
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
COMMENT "#".*

%%

{ws}+ { ; }
\n|\r { yycolumn = 0; }
{IF} { yylval.Str = new std::string(yytext); return IF;}
{ELIF} { yylval.Str = new std::string(yytext); return ELIF;}
{ELSE} { yylval.Str = new std::string(yytext); return ELSE; }
{WHILE} { yylval.Str = new std::string(yytext); return WHILE; }
{FOR} { yylval.Str = new std::string(yytext); return FOR; }
{IN} { yylval.Str = new std::string(yytext); return IN; }
{RANGE} { yylval.Str = new std::string(yytext); return RANGE; }
{TYPE} { yylval.Str = new std::string(yytext); return TYPE; }
{STRUCT} { yylval.Str = new std::string(yytext); return STRUCT; }

{DEF} { yylval.Str = new std::string(yytext); return DEF; }
{RETURN} { yylval.Str = new std::string(yytext); return RETURN; }
{MAIN} { yylval.Str = new std::string(yytext); return MAIN; }
{VAR} { yylval.Str = new std::string(yytext); return VAR; }
{STMT} { yylval.Str = new std::string(yytext); return STMT; }
{FUNCSPEC} { yylval.Str = new std::string(yytext); return FUNCSPEC; }

{SEMI} { yylval.Str = new std::string(yytext); return SEMI; }
{COMMA} { yylval.Str = new std::string(yytext); return COMMA; }
{COLON} { yylval.Str = new std::string(yytext); return COLON; }

{ASSIGNOP} { yylval.op = new std::string(yytext); return ASSIGNOP; }
{ADD} { yylval.op = new std::string(yytext); return ADD; }
{SUB} { yylval.op = new std::string(yytext); return SUB; }
{MUL} { yylval.op = new std::string(yytext); return MUL; }
{DIV} { yylval.op = new std::string(yytext); return DIV; }
{AND} { yylval.op = new std::string(yytext); return AND; }
{OR} { yylval.op = new std::string(yytext); return OR; }
{NOT} { yylval.op = new std::string(yytext); return NOT; }
{RELOP} { yylval.op = new std::string(yytext); return RELOP; }
{DOT} { yylval.op = new std::string(yytext); return DOT; }

{LP} { yylval.op = new std::string(yytext); return LP; }
{RP} { yylval.op = new std::string(yytext); return RP; }
{LB} { yylval.op = new std::string(yytext); return LB; }
{RB} { yylval.op = new std::string(yytext); return RB; }
{LC} { yylval.Str = new std::string(yytext); return LC; }
{RC} { yylval.Str = new std::string(yytext); return RC; }

{INT} { yylval.int_val = atoi(yytext); return INT;}
{FLOAT} { yylval.float_val = atof(yytext); return FLOAT;}
{ID} { yylval.name = new std::string(yytext); return ID; }
{STRING} { yylval.string_val = new std::string(yytext); return STRING; }

{COMMENT} {;}

. { ; }
%%

void yyerror(const char *s) {
    fprintf(stderr, "LexError: %s [yytext]: %s (at Line %d, Column%d)\n", s, yytext, yylloc.first_line, yylloc.first_column);
}