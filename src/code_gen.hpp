#pragma once

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <cstdlib>
#include <vector>
#include <memory>
#include <map>
#include <string>
#include "./ast.hpp"

//NOTE: every VariableExprAST that inserted into the symbol table get it's type changed into data type rather than type_ID

std::unique_ptr<ExprAST> LogError(const std::string& Str);
llvm::Value *LogErrorV(const std::string& Str);

class SymbolTable {
    std::vector<std::map<std::string, llvm::AllocaInst *>*> NamedValues; //stack, for local variables
    std::map<std::string, llvm::GlobalVariable *> GlobalNamedValues;

    std::vector<std::map<std::string, VariableExprAST *>*> IDTable; //stack, for local identifiers
    std::map<std::string, VariableExprAST *> GlobalIDTable;

    std::map<std::string, PrototypeAST *> PrototypeTable; 

public:

    int getType(std::string name){
        return FindID(name)->getType();
    }

    void addGlobalVal(std::string name, llvm::GlobalVariable * value){
        GlobalNamedValues[name] = value;
    }

    void addGlobalID(std::string name, VariableExprAST* Expr){
        GlobalIDTable[name] = Expr;
    }

    void addLocalVal(std::string name, llvm::AllocaInst * value){
        if (NamedValues.size()<0){
            pushNamedValue();
        }
        (*NamedValues.back())[name] = value;
    }

    void addLocalID(std::string name, VariableExprAST* Expr){
        if (IDTable.size()<0){
            pushIDTable();
        }
        (*IDTable.back())[name] = Expr;
    }

    void pushNamedValue(){
        NamedValues.push_back(new std::map<std::string, llvm::AllocaInst *>());
    }

    void pushIDTable(){
        IDTable.push_back(new std::map<std::string, VariableExprAST *>());
    }

    void popNamedValue(){
        if (NamedValues.size()>0) NamedValues.pop_back();
    }

    void popIDTable(){
        if (IDTable.size()>0) IDTable.pop_back();
    }

    void addProtoType(std::string name, PrototypeAST * proto){
        PrototypeTable[name] = proto;
    }

    PrototypeAST* getProtoType(std::string name){
        if(PrototypeTable.find(name) != PrototypeTable.end()){
            return PrototypeTable[name];
        }
        return nullptr;
    }

    llvm::Value *FindValue(std::string name){
        llvm::Value *value = _FindValue(name);
        if (!value){
            return _FindGlobalValue(name);
        }
        return value;
        return nullptr;
    }

    llvm::Value *_FindValue(std::string name){
        if(NamedValues.back()->find(name) != NamedValues.back()->end()){
            return (*NamedValues.back())[name];
        }
        return nullptr;
    }

    llvm::GlobalVariable *_FindGlobalValue(std::string name){
        if (GlobalNamedValues.find(name) != GlobalNamedValues.end()){
            return GlobalNamedValues[name];
        }
        return nullptr;
    }

    VariableExprAST* FindID(std::string name){
        if(IDTable.back()->find(name) != IDTable.back()->end()){
            return (*IDTable.back())[name];
        }
        if (GlobalIDTable.find(name) != GlobalIDTable.end()){
            return GlobalIDTable[name];
        }
        return nullptr;
    }
    
};

