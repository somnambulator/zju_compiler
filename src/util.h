#ifndef _UTIL_H
#define _UTIL_H

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
#include "./ast.h"


class SymbolTable {
    std::vector<std::map<std::string, llvm::Value *>*> NamedValues; //stack, for local variables
    std::map<std::string, llvm::GlobalVariable *> GlobalNamedValues;

    std::vector<std::map<std::string, DecExprAST *>*> IDTable; //stack, for local identifiers
    std::map<std::string, DecExprAST *> GlobalIDTable;

public:

    void addGlobalVal(std::string name, llvm::GlobalVariable * value){
        GlobalNamedValues[name] = value;
    }

    void addGlobalID(std::string name, DecExprAST* Expr){
        GlobalIDTable[name] = Expr;
    }

    void addLocalVal(std::string name, llvm::Value * value){
        if (NamedValues.size()<0){
            pushNamedValue();
        }
        (*NamedValues.back())[name] = value;
    }

    void addLocalID(std::string name, DecExprAST* Expr){
        if (IDTable.size()<0){
            pushIDTable();
        }
        (*IDTable.back())[name] = Expr;
    }

    void pushNamedValue(){
        NamedValues.push_back(new std::map<std::string, llvm::Value *>());
    }

    void pushIDTable(){
        IDTable.push_back(new std::map<std::string, DecExprAST *>());
    }

    void popNamedValue(){
        if (NamedValues.size()>0) NamedValues.pop_back();
    }

    void popIDTable(){
        if (IDTable.size()>0) IDTable.pop_back();
    }

    llvm::Value *FindValue(ExprAST* Expr){
        if(Expr->getType() == type_ID){
            std::string name = static_cast<DecExprAST *>(Expr)->getName();
            llvm::Value *value = _FindValue(name);
            if (!value){
                return _FindGlobalValue(name);
            }
            return value;
        }
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

    DecExprAST* FindID(std::string name){
        if(IDTable.back()->find(name) != IDTable.back()->end()){
            return (*IDTable.back())[name];
        }
        if (GlobalIDTable.find(name) != GlobalIDTable.end()){
            return GlobalIDTable[name];
        }
        return nullptr;
    }
    
};

#endif