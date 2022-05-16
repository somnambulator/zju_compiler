#include <cstdio>
#include <iostream>
#include ".ast.hpp"
#include ".code_gen.cpp"
#include ".parser.hpp"

extern ExprAST* Program;

int main(int argc, char** argv){
    if (argc<=1) return 1;
    FILE* f = fopen(argv[1], "r");
    if(!f){
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();

    Program->codegen();
    return 0;
}