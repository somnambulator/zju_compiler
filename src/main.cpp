#include <cstdio>
#include <iostream>
#include "json/json.h"
#include "./ast.hpp"
#include "./code_gen.hpp"
#include "./build/parser.y.hpp"

extern int yylex(void);
extern int yyparse(void);
extern void yyrestart(FILE*);
int errorLexFlag;
int errorSyntaxFlag;

extern ProgramAST* Program;

std::string out_name;
bool err_flag;

void parse_arg(int argc, char** argv){
    for(int i=0;i<argc;i++){
        std::string arg(argv[i]);
        if(arg=="-o"){
            i++;
            if(i>=argc){
                std::cerr<<"Invalid output filename"<<std::endl;
                err_flag=1;
                return;
            }
            out_name = std::string(argv[i]);
        }
        else{
            std::string err(argv[i]);
            std::cerr<<"Invalid command option: "<<err<<" !"<<std::endl;
            err_flag=1;
            return;
        }
    }
}

int main(int argc, char** argv){
    err_flag=0;
    out_name = std::string("a");
    if (argc<=1) return 1;
    FILE* f = fopen(argv[1], "r");
    
    if(!f){
        perror(argv[1]);
        return 1;
    }

    parse_arg(argc-2, argv+2);

    yyrestart(f);
    std::cout<< "Start to parse." <<std::endl;
    yyparse();
    std::cout<< "Finish parsing." <<std::endl;

    std::cout<< "Start to print AST to Json." <<std::endl;
    Json::Value root = Program->print();
    std::ofstream jsonfile(out_name+".json");
    if(jsonfile.is_open()){
        jsonfile << root;
        jsonfile.close();
    }
    std::cout<< "Finish AST printing." <<std::endl;

    std::cout<< "Start to generate code." <<std::endl;
    std::string Str = Program->codegen();
    std::ofstream outfile;
    outfile.open(out_name+".ll");
    if(outfile.is_open()){
        outfile << Str;
        outfile.close();
    }
    std::cout<< "Finish code generation." <<std::endl;
    return 0;
}