#pragma once

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "json/json.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

// using namespace llvm;
#define type_error -1
#define type_void 1
#define type_bool 2
#define type_char 3
#define type_int 4
#define type_float 5
#define type_charptr 6
#define type_string 7

#define type_ID 100
#define type_binaryExpr 101
#define type_Dec 102
#define type_DecList 103
#define type_CallFunc 104
#define type_FuncProto 105
#define type_FuncBody 106
#define type_Func 107
#define type_Array 108
#define type_assignExpr 109
#define type_GlobalDec 110
#define type_Expr 111
#define type_ifelse 112
#define type_for 113
#define type_while 114

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;

/// ExprAST - Base class for all expression nodes.
class ExprAST {
  int type;
  bool global;
  int lineno;
public:
  ExprAST() : type(type_Expr){}
  virtual ~ExprAST() = default;

  void SetGlobal(){
    global=true;
  }

  void SetType(int def_type){
    type = def_type;
  }

  void SetTypeStr(const std::string &TypeName){
    if(TypeName == "int"){
      this->SetType(type_int);
    } 
    else if (TypeName == "float"){
      this->SetType(type_float);
    }
    else if (TypeName == "bool"){
      this->SetType(type_bool);
    }
    else if (TypeName == "void"){
      this->SetType(type_void);
    }
    else if (TypeName == "string"){
      this->SetType(type_string);
    }
    else{
      this->SetType(type_error);
    }
  }

  std::string getTypeStr(){
    std::string ret;
    switch (type)
    {
    case type_void:
      ret = "Void";
      break;
    case type_bool:
      ret = "Bool";
      break;
    case type_int:
      ret = "Int";
      break;
    case type_float:
      ret = "Float";
      break;
    case type_char:
      ret = "Char";
      break;
    case type_string:
      ret = "String";
      break;
    default:
      ret = "Unknown Type";
      break;
    }
    return ret;
  }

  int getType(){
    return type;
  }

  void setLineno(int line){ lineno = line; }
  int getLineno() {return lineno;}

  virtual llvm::Value *codegen() = 0;
  // virtual llvm::Value *GlobalCodegen() = 0;
  virtual Json::Value print() = 0;
};

typedef std::vector<std::unique_ptr<ExprAST>> ast_list;
// typedef std::vector<std::unique_ptr<DecExprAST>> dec_list;
// typedef std::vector<std::unique_ptr<PrototypeAST>> proto_list;
// typedef std::vector<std::unique_ptr<FunctionAST>> func_list;

/// TypeAST - Expression class for different types.
class TypeAST : public ExprAST {
  
public:
  TypeAST(const std::string &TypeName) {
    this->SetTypeStr(TypeName);
  }

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// IntExprAST - Expression class for integers like "1".
class IntExprAST : public ExprAST {
  int Val;

public:
  IntExprAST(int Val) : Val(Val) {this->SetType(type_int);}

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// FloatExprAST - Expression class for floats like "1.0".
class FloatExprAST : public ExprAST {
  double Val;

public:
  FloatExprAST(double Val) : Val(Val) {this->SetType(type_float);}

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// StringExprAST - Expression class for Stings.
class StringExprAST : public ExprAST {
  std::string Str;
  bool global;

public:
  StringExprAST(std::string InStr) {
      Str = InStr.substr(1,InStr.length()-2);
      this->SetType(type_string);
      global = 0;
    }

  void setGlobal(bool glb){global = glb;}

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// FloatExprAST - Expression class for void.
class VoidExprAST : public ExprAST {

public:
  VoidExprAST() {this->SetType(type_void);}

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {this->SetType(type_ID);}

  std::string getName() {return Name;}

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// GlobalDecListAST - Expression class for referencing a list of global declarations
/// ATTENTION: Global decalarations with assignments are not allowed!
class GlobalDecListAST : public ExprAST{
  ast_list VarList;

public:
  GlobalDecListAST(ast_list List) : VarList(std::move(List)) {
      this->SetType(type_GlobalDec);
    }

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// DecListAST - Expression class for referencing a list of declarations.
class DecListAST : public ExprAST{
  ast_list VarList;

public:
  DecListAST(ast_list List) : VarList(std::move(List)) {this->SetType(type_DecList);}

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// DecExprAST - Expression class for referencing a declaration, like "a:int".
class DecExprAST : public ExprAST{
  bool global;
  std::unique_ptr<VariableExprAST> Var;
  std::unique_ptr<TypeAST> Type;
  std::string name;

public:
  DecExprAST(VariableExprAST* Var, 
             TypeAST* Type,
             bool global) : Var(std::move(Var)), Type(std::move(Type)), global(global) {
               assert(Var != nullptr);
               assert(Type != nullptr);
               Var->SetType(Type->getType());
               this->SetType(type_Dec);
               name = Var->getName();
             }
  
  std::string getName() {return name;}
  
  int getDType() {return Type->getType();}
  VariableExprAST* getVar() {return Var.get();}
             
  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// IfExprAST - Expression class for if/then/else.
class IfExprAST : public ExprAST {
  std::unique_ptr<ExprAST> Cond, Then, Else;

public:
  IfExprAST(ExprAST* Cond, ExprAST* Then,ExprAST* Else)
      : Cond(std::move(Cond)), Then(std::move(Then)), Else(std::move(Else)) { this->SetType(type_ifelse); }

  IfExprAST(ExprAST* Cond, ExprAST* Then)
      : Cond(std::move(Cond)), Then(std::move(Then)), Else(new VoidExprAST()) { this->SetType(type_ifelse); }

  llvm::Value *codegen() override;
  Json::Value print() override;
};

// ForExprAST - Expression class for for/in.
class ForExprAST : public ExprAST {
  std::unique_ptr<VariableExprAST> ID;
  std::unique_ptr<ExprAST> Start, End, Step;
  std::unique_ptr<ExprAST>Body;

public:
  ForExprAST(VariableExprAST* ID, 
             ExprAST* Start,
             ExprAST* End, ExprAST* Step,
             ExprAST* Body)
      : ID(std::move(ID)), Start(std::move(Start)), End(std::move(End)),
        Step(std::move(Step)), Body(std::move(Body)) { this->SetType(type_for); }
  
  ForExprAST(VariableExprAST* ID, 
             ExprAST* Start,
             ExprAST* End, 
             ExprAST* Body)
      : ID(std::move(ID)), Start(std::move(Start)), End(std::move(End)),
        Step(new IntExprAST(1)), Body(std::move(Body)) { this->SetType(type_for); }

  llvm::Value *codegen() override;
  Json::Value print() override;
};

// WhileExprAST - Expression class for while.
class WhileExprAST : public ExprAST {
  std::unique_ptr<ExprAST> Condv;
  std::unique_ptr<ExprAST> Body;

public:
  WhileExprAST(ExprAST* Condv, ExprAST* Body)
      : Condv(std::move(Condv)), Body(std::move(Body)) { this->SetType(type_while); }

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// AssignExprAST - Expression class for a binary operator.
class AssignExprAST : public ExprAST {
  // we have to tell the type of LHS(can be VariableExprAST or DecExprAST)
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  AssignExprAST(ExprAST* LHS,
                ExprAST* RHS)
      : LHS(std::move(LHS)), RHS(std::move(RHS)) { 
          assert(LHS!=nullptr);
          assert(RHS!=nullptr);
          this->SetType(type_assignExpr);
        }

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  std::string Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(std::string Op, 
                ExprAST* LHS,
                ExprAST* RHS)
      : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {
          assert(LHS!=nullptr);
          assert(RHS!=nullptr);
          this->SetType(type_binaryExpr);
        }

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
  std::string Callee;
  ast_list Args;

public:
  CallExprAST(const std::string &Callee,
              ast_list Args)
      : Callee(Callee), Args(std::move(Args)) {this->SetType(type_CallFunc);}

  std::string getCallee() {return Callee;}

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST : public ExprAST{
  bool HasReturn;
  std::unique_ptr<TypeAST> retType;
  std::string Name;
  ast_list Args;

public:
  PrototypeAST(TypeAST* retType, const std::string &Name, ast_list Args)
      : retType(std::move(retType)), Name(Name), Args(std::move(Args)) {
          assert(retType!=nullptr);
          // if (retType->getType()!=type_void){
          //   HasReturn = 1;
          // }
          this->SetType(type_FuncProto);
        }

  int getArgType(int i) {
    return static_cast<DecExprAST*>(Args[i].get())->getDType();
  }

  void setReturn(bool ret) { HasReturn = ret; }
  bool hasReturn() { return HasReturn; }

  int getRetType() {return retType->getType();}

  llvm::Function *codegen();
  Json::Value print() override;
  const std::string &getName() const { return Name; }
};

/// BodyAST - This class represents a function body.
class BodyAST : public ExprAST {
  bool HasReturn;
  int RetType;
  ast_list DefList;
  ast_list StmtList;
  std::unique_ptr<ExprAST> ReturnExpr;

public:
  BodyAST(ast_list DefList,
          ast_list StmtList,
          ExprAST* ReturnExpr)
      : DefList(std::move(DefList)), StmtList(std::move(StmtList)), ReturnExpr(ReturnExpr) {
          assert(ReturnExpr!=nullptr);
          this->SetType(type_FuncBody);
          HasReturn = 1;
          RetType = 0;
        }
  BodyAST(ast_list DefList,
          ast_list StmtList)
      : DefList(std::move(DefList)), StmtList(std::move(StmtList)), ReturnExpr(new VoidExprAST()) {
          assert(ReturnExpr!=nullptr);
          this->SetType(type_FuncBody);
          HasReturn = 0;
          RetType = 0;
        }
  
  void setReturn(bool ret) { HasReturn=ret; }
  bool hasReturn() { return HasReturn; }

  void setRetType(int retType) { RetType = retType; }

  llvm::Value *codegen() override;
  Json::Value print() override;
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST : public ExprAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<BodyAST> Body;

public:
  FunctionAST(PrototypeAST* Proto,
              BodyAST* Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {
          assert(Proto!=nullptr);
          assert(Body!=nullptr);
          this->SetType(type_Func);
          Proto->setReturn(Body->hasReturn());
          Body->setRetType(Proto->getRetType());
        }

  llvm::Function *codegen();
  Json::Value print() override;
};

/// PorgramAST - This class represents a Program, also used as root.
class ProgramAST {
  ast_list ElementList;

public:
  ProgramAST(ast_list List) : ElementList(std::move(List)) {}
  
  std::string codegen();
  Json::Value print();
};
