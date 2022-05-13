#ifndef _AST_H
#define _AST_H

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
#define type_int 3
#define type_float 4

#define type_Expr 99
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

typedef std::vector<std::unique_ptr<ExprAST>> ast_list;
typedef std::vector<std::unique_ptr<DecExprAST>> dec_list;
// typedef std::vector<std::unique_ptr<PrototypeAST>> proto_list;
// typedef std::vector<std::unique_ptr<FunctionAST>> func_list;

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;

/// ExprAST - Base class for all expression nodes.
class ExprAST {
  int type;
  bool global;
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
    else{
      this->SetType(type_error);
    }
  }

  int getType(){
    return type;
  }

  virtual llvm::Value *codegen() = 0;
};

/// TypeAST - Expression class for different types.
class TypeAST : public ExprAST {
  
public:
  TypeAST(const std::string &TypeName) {
    this->SetTypeStr(TypeName);
  }

  llvm::Value *codegen() override;
};

/// IntExprAST - Expression class for integers like "1".
class IntExprAST : public ExprAST {
  int Val;

public:
  IntExprAST(int Val) : Val(Val) {this->SetType(type_int);}

  llvm::Value *codegen() override;
};

/// FloatExprAST - Expression class for floats like "1.0".
class FloatExprAST : public ExprAST {
  float Val;

public:
  FloatExprAST(float Val) : Val(Val) {this->SetType(type_float);}

  llvm::Value *codegen() override;
};

/// FloatExprAST - Expression class for void.
class VoidExprAST : public ExprAST {

public:
  VoidExprAST() {this->SetType(type_void);}

  llvm::Value *codegen() override;
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {this->SetType(type_ID);}

  std::string getName() {return Name;}

  llvm::Value *codegen() override;
};

/// GlobalDecListAST - Expression class for referencing a list of global declarations
/// ATTENTION: Global decalarations with assignments are not allowed!
class GlobalDecListAST : public ExprAST{
  ast_list VarList;

public:
  GlobalDecListAST(ast_list List) : VarList(List) {this->SetType(type_GlobalDec);}

  llvm::Value *codegen() override;
};

/// DecListAST - Expression class for referencing a list of declarations.
class DecListAST : public ExprAST{
  ast_list VarList;

public:
  DecListAST(ast_list List) : VarList(List) {this->SetType(type_DecList);}

  llvm::Value *codegen() override;
};

/// DecExprAST - Expression class for referencing a declaration, like "a:int".
class DecExprAST : public ExprAST{
  std::unique_ptr<VariableExprAST> Var;
  std::unique_ptr<TypeAST> Type;
  std::string name;

public:
  DecExprAST(std::unique_ptr<VariableExprAST> Var, 
             std::unique_ptr<TypeAST> Type) : Var(std::move(Var)), Type(std::move(Type)) {
               Var->SetType(Type->getType());
               this->SetType(type_Dec);
               name = Var->getName();
             }
  
  std::string getName() {return name;}
  
  int getDType() {return Type->getType();}
             
  llvm::Value *codegen() override;
};

// /// DefListAST - Expression class for referencing a list of definitions.
// class DefListAST : public ExprAST{
//   ast_list DefList;

// public:
//   DefListAST(ast_list DefList) : DefList(std::move(DefList)) {}

//   llvm::Value *codegen() override;
// };

/// AssignExprAST - Expression class for a binary operator.
class AssignExprAST : public ExprAST {
  std::string Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  AssignExprAST(std::string Op, std::unique_ptr<ExprAST> LHS,
                std::unique_ptr<ExprAST> RHS)
      : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {this->SetType(type_assignExpr);}

  llvm::Value *codegen() override;
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  std::string Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(std::string Op, std::unique_ptr<ExprAST> LHS,
                std::unique_ptr<ExprAST> RHS)
      : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {this->SetType(type_binaryExpr);}

  llvm::Value *codegen() override;
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
  std::string Callee;
  ast_list Args;

public:
  CallExprAST(const std::string &Callee,
              ast_list Args)
      : Callee(Callee), Args(std::move(Args)) {this->SetType(type_CallFunc);}

  llvm::Value *codegen() override;
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST : public ExprAST{
  std::string Name;
  ast_list Args;

public:
  PrototypeAST(const std::string &Name, ast_list Args)
      : Name(Name), Args(std::move(Args)) {this->SetType(type_FuncProto);}

  llvm::Function *codegen();
  const std::string &getName() const { return Name; }
};

/// BodyAST - This class represents a function body.
class BodyAST : public ExprAST {
  ast_list DefList;
  ast_list StmtList;
  std::unique_ptr<ExprAST> ReturnExpr;

public:
  BodyAST(ast_list DefList,
              ast_list StmtList)
      : DefList(std::move(DefList)), StmtList(std::move(StmtList)) {this->SetType(type_FuncBody);}
  
  llvm::Function *codegen();
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST : public ExprAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<ExprAST> Body;
  // std::unique_ptr<ExprAST> ReturnExpr;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<ExprAST> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {this->SetType(type_Func);}
  
  void SetReturnExpr(std::unique_ptr<ExprAST> ReturnExpr){
    ReturnExpr = std::move(ReturnExpr);
  }

  llvm::Function *codegen();
};

/// PorgramAST - This class represents a Program, also used as root.
class ProgramAST {
  ast_list ElementList;

public:
  ProgramAST(ast_list List) : ElementList(std::move(List)) {}
  
  llvm::Function *codegen();
};

std::unique_ptr<ExprAST> LogError(const char *Str);
llvm::Value *LogErrorV(const char *Str);

#endif