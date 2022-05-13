%{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "ast.h"

// using namespace std;

extern int yyparse(yyFlexLexer* yyflex);
%}

%union
{
    int int_val;
    float float_val;

    string* name;
    char* op; 
}

%token COLON SEMICOLON COMMA LC RC
%token DEF RETURN MAIN
%token <name> ID
%token <int_val> INT
%token <float_val> FLOAT

// %type <> Program ExtDefList ExtDef ExtDecList   //  High-level Definitions
// %type <> Specifier StructSpecifier OptTag Tag   //  Specifiers
// %type <> VarDec FunDec VarList ParamDec         //  Declarators
// %type <> CompSt StmtList Stmt                   //  Statements
// %type <> DefList Def Dec DecList                //  Local Definitions
// %type <> Exp Args                               //  Expressions

%right <op> ASSIGNOP
%left <op> OR
%left <op> AND
%left <op> RELOP
%left <op> ADD, SUB
%left <op> MUL, DIV
%right <op> NOT
%left <op> DOT
%left <op> LB, RB
%left <op> LP, RP
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

// High-level Definitions
Program:            ExtDefList                              { $$ = new ProgramAST($1); }
    ; 
ExtDefList:         ExtDef ExtDefList                       { $$ = $2; $$->push_back($1); }
    |               MainDef                                 { $$ = new ast_list();
                                                              $$->push_back($1); }
    |                                                       { $$ = new ast_list(); } 
    ; 
ExtDef:             ExtDecList SEMI                         { $$ = new GlobalDecListAST($1); }
    |               Specifier SEMI                          { //for struct }
    |               DEF FunDec COLON CompSt                 { $$ = new FunctionAST($2, $4); }
    |               error SEMI                              {  }
    ; 
MainDef:            DEF MainFunDec COLON CompSt             { $$ = new FunctionAST($2, $4); }
    |               error SEMI                              {  }
    ;
ExtDecList:         VarDec COLON Specifier                  { $$ = new dec_list(); $$->push_back(new DecExprAST($1, $3)); }
    |               VarDec COLON Specifier COMMA ExtDecList { $$ = $5; $$->push_back(new DecExprAST($1, $3)); }
    ; 

// Specifiers
Specifier:          TYPE                                    { $$ = new TypeAST(std::string($1)); }
    |               StructSpecifier                         {  }
    ; 
StructSpecifier:    STRUCT OptTag LC DefList RC             {  }
    |               STRUCT Tag                              {  }
    ; 
OptTag:             ID                                      {  }
    |                                                       {  }
    ; 
Tag:                ID                                      {  }
    ; 

// Declarators
VarDec:             ID                                      { $$ = new VariableExprAST(std::string($1)); }
    |               VarDec LB INT RB                        { //for array }
    |               error RB                                {  }
    ; 
FunDec:             ID LP VarList RP                        { $$ = new PrototypeAST(std::string($1), $3); }
    |               ID LP RP                                {  }
    |               error RP                                {  }
    ; 
MainFunDec:         MAIN LP RP                              { args = new ast_list(); 
                                                              args->push_back(new VoidExprAST());
                                                              $$ = new PrototypeAST(std::string("main"), args); }
    |               error RP                                {  }
    ; 
VarList:            ParamDec COMMA VarList                  { $$ = $3; $$->push_back($1); }
    |               ParamDec                                { $$ = new ast_list(); $$->push_back($1); }
    ; 
ParamDec:           VarDec COLON Specifier                  { $$ = new DecExprAST($1, $3); }
    ; 
// Statements
CompSt:             LC DefList StmtList RC                  { $$ = new BodyAST($2, $3, new VoidExprAST()); }
    |               LC DefList StmtList ReturnStmt RC       { $$ = new BodyAST($2, $3, $4); }
    |               error RC                                {  }
    ; 
StmtList:           Stmt StmtList                           { $$ = $2; $$->push_back($1); }
    |                                                       { $$ = new ast_list(); }
    ; 
Stmt:               Exp SEMI                                { $$ = $1; }
    |               CompSt                                  { $$ = $1; }   
    |               IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {  }
    |               IF LP Exp RP Stmt ELSE Stmt             {  }
    |               WHILE LP Exp RP Stmt                    {  }
    |               error SEMI                              {  }
    ; 
ReturnStmt:         RETURN Exp SEMI                         { $$ = $2; }
    |               RETURN SEMI                             { $$ = new VoidExprAST(); }
// Local Definitions
DefList:            Def DefList                             { $$ = $2; $$->push_back($1); }
    |                                                       { $$ = new ast_list(); }
    ;     
Def:                DecList SEMI                            { $$ = new DecListAST($1); }
    ; 
DecList:            Dec                                     { $$ = new dec_list(); $$->push_back($1); }
    |               Dec COMMA DecList                       { $$ = $3; $$->push_back($1); }
    ; 
Dec:                VarDec COLON Specifier                  { $$ = new DecExprAST($1, $3); }
    |               VarDec COLON Specifier ASSIGNOP Exp     { $$ = new DecExprAST($1, $3, $5); }
    ; 
//7.1.7 Expressions
Exp:                Exp ASSIGNOP Exp                        { $$ = new AssignExprAST(std::string($2), $1, $3); }
    |               Exp AND Exp                             { $$ = new BinaryExprAST(std::string($2), $1, $3); }
    |               Exp OR Exp                              { $$ = new BinaryExprAST(std::string($2), $1, $3); }
    |               Exp RELOP Exp                           { $$ = new BinaryExprAST(std::string($2), $1, $3); }
    |               Exp PLUS Exp                            { $$ = new BinaryExprAST(std::string($2), $1, $3); }
    |               Exp MINUS Exp                           { $$ = new BinaryExprAST(std::string($2), $1, $3); }
    |               Exp STAR Exp                            { $$ = new BinaryExprAST(std::string($2), $1, $3); }
    |               Exp DIV Exp                             { $$ = new BinaryExprAST(std::string($2), $1, $3); }
    |               LP Exp RP                               { $$ = $2; }
    |               MINUS Exp                               { $$ = new BinaryExprAST(std::string($1), new IntExprAST(0), $2); }
    |               NOT Exp                                 { $$ = new BinaryExprAST(std::string($1), new ExprAST(), $2); }
    |               ID LP Args RP                           { $$ = new CallExprAST($1, $3); }
    |               ID LP RP                                { $$ = new CallExprAST($1, new VoidExprAST()); }
    |               Exp LB Exp RB                           { //for array }
    |               Exp DOT ID                              { //for struct }
    |               ID                                      { $$ = new VariableExprAST($1); }
    |               INT                                     { $$ = new IntExprAST($1); }
    |               FLOAT                                   { $$ = new FloatExprAST($1); }
    ; 
Args :              Exp COMMA Args                          { $$ = $3; $$->push_back($1); }
    |               Exp                                     { $$ = new ast_list(); $$->push_back($1); }
    ; 
%%

yyerror(char* msg){
    fprintf(stderr, "Error type B at line %d: %s.\n", yylineno, msg);
}