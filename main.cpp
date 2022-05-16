#include <iostream>
#include "./src/ast.hpp"
#include "./src/code_gen.cpp"
#include "./src/parser.hpp"

extern ExprAST* Program;

int main(int argc, char** argv){
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    }
    yyparse();

    Program->codegen();
    return 0;
}