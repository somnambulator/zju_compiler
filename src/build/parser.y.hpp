/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_Y_HPP_INCLUDED
# define YY_YY_PARSER_Y_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COLON = 258,
    COMMA = 259,
    LC = 260,
    RC = 261,
    FUNCSPEC = 262,
    SEMI = 263,
    STRUCT = 264,
    IF = 265,
    WHILE = 266,
    FOR = 267,
    TYPE = 268,
    ELSE = 269,
    ELIF = 270,
    IN = 271,
    RANGE = 272,
    DEF = 273,
    RETURN = 274,
    MAIN = 275,
    VAR = 276,
    STMT = 277,
    ID = 278,
    INT = 279,
    FLOAT = 280,
    STRING = 281,
    ASSIGNOP = 282,
    OR = 283,
    AND = 284,
    RELOP = 285,
    ADD = 286,
    SUB = 287,
    MUL = 288,
    DIV = 289,
    NOT = 290,
    DOT = 291,
    LB = 292,
    RB = 293,
    LP = 294,
    RP = 295,
    LOWER_THAN_ELSE = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "/home/yuanli/zju_compiler/src/parser.ypp"

    int int_val;
    float float_val;
    char char_val;
    std::string* string_val;

    std::string* name;
    std::string* op; 
    std::string* Str;

    ast_list* AST_list;
    ExprAST* exprAST;
    FunctionAST* functionAST;
    TypeAST* typeAST;
    PrototypeAST* prototypeAST;
    BodyAST* bodyAST;
    VariableExprAST* variableexprAST;
    DecExprAST* decexprAST;
    DecListAST* declistAST;

#line 120 "parser.y.hpp"

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

#endif /* !YY_YY_PARSER_Y_HPP_INCLUDED  */
