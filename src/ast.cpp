#include "./ast.h"
#include "./util.h"

static SymbolTable symbolTable;

std::unique_ptr<ExprAST> LogError(const char *Str) {
  fprintf(stderr, "Error: %s\n", Str);
  return nullptr;
}

llvm::Value *LogErrorV(const char *Str) {
  LogError(Str);
  return nullptr;
}

llvm::Type *typeGen(int type){
  switch (type){
    case type_void:
      return llvm::Type::getVoidTy(TheContext);
    case type_bool:
      return llvm::Type::getInt1Ty(TheContext);
    case type_int:
      return llvm::Type::getInt32Ty(TheContext);
    case type_float:
      return llvm::Type::getFloatTy(TheContext);
    default:
      return llvm::Type::getInt32Ty(TheContext);
  }
}

llvm::Value *TypeAST::codegen() {
    //TODO: COMPLETE TYPEAST
    //nothing to do
    return nullptr;
}

llvm::Value *IntExprAST::codegen() {
  return llvm::ConstantInt::get(TheContext, llvm::APInt(32, Val, true));
}

llvm::Value *FloatExprAST::codegen() {
  return llvm::ConstantFP::get(TheContext, llvm::APFloat(Val));
}

llvm::Value *VoidExprAST::codegen() {
  return llvm::ConstantPointerNull::getNullValue(typeGen(type_int));
}

llvm::Value *VariableExprAST::codegen() {
  // Look this variable up in the function.
  llvm::Value *V = symbolTable._FindValue(Name);
  if (!V){
    llvm::GlobalVariable *GV = symbolTable._FindGlobalValue(Name);
    if(!GV) return LogErrorV("Unknown variable name");
    else return Builder.CreateLoad(GV, Name.c_str());
  }
  return Builder.CreateLoad(V, Name.c_str());
}

llvm::Value *DecListAST::codegen(){
  for (int i = 0;i<VarList.size();i++){
    VarList[i]->codegen();
  }
}

llvm::Value *DecExprAST::codegen(){

}

llvm::Value *BinaryExprAST::codegen() {
  llvm::Value *L = LHS->codegen();
  llvm::Value *R = RHS->codegen();
  if (!L || !R)
    return nullptr;

  int LType = LHS->getType();
  if(LHS->getType()==type_ID){
    std::string name = static_cast<VariableExprAST*>(LHS.get())->getName();
    LType = symbolTable.FindID(name)->getDType();
  }

  int RType = RHS->getType();
  if(RHS->getType()==type_ID){
    std::string name = static_cast<VariableExprAST*>(RHS.get())->getName();
    RType = symbolTable.FindID(name)->getDType();
  }

  int ThisType;
  if (Op=="+" || Op=="-" || Op=="*"){
    ThisType = (LType > RType)? LType : RType;
    if(LType<ThisType){
      if (LType == type_bool) L = Builder.CreateUIToFP(L, typeGen(ThisType));
      else L = Builder.CreateSIToFP(L, typeGen(ThisType));
    }
    if(RType<ThisType){
      if (RType == type_bool) R = Builder.CreateUIToFP(R, typeGen(ThisType));
      else R = Builder.CreateSIToFP(R, typeGen(ThisType));
    }
  }
  else if(Op=="/"){
    ThisType = type_float;
    if(LType<ThisType){
      if (LType == type_bool) L = Builder.CreateUIToFP(L, typeGen(ThisType));
      else L = Builder.CreateSIToFP(L, typeGen(ThisType));
    }
    if(RType<ThisType){
      if (RType == type_bool) R = Builder.CreateUIToFP(R, typeGen(ThisType));
      else R = Builder.CreateSIToFP(R, typeGen(ThisType));
    }
  }
  else if(Op=="<" || Op==">" || Op=="<=" || Op==">=" || Op=="==" || Op=="!="){
    ThisType = type_bool;
  }
  
  // recursively set type
  this->SetType(ThisType);

  // do arithmetic
  if(Op == "+"){
    return (ThisType==type_float)? Builder.CreateFAdd(L, R, "addtmp"): Builder.CreateAdd(L, R, "addtmp");
  }
  else if(Op == "-"){
    return (ThisType==type_float)? Builder.CreateFSub(L, R, "subtmp"): Builder.CreateSub(L, R, "subtmp");
  }
  else if(Op == "*"){
    return (ThisType==type_float)? Builder.CreateFMul(L, R, "multmp"): Builder.CreateMul(L, R, "multmp");
  }
  else if(Op == "/"){
    return (ThisType==type_float)? Builder.CreateFDiv(L, R, "divtmp"): Builder.CreateFDiv(L, R, "divtmp");
  }
  else if(Op == "<"){
    if (ThisType==type_float){
      return Builder.CreateFCmpOLT(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpSLT(L, R, "cmptmp");
    }
  }
  else if(Op == ">"){
    if (ThisType==type_float){
      return Builder.CreateFCmpOGT(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpSGT(L, R, "cmptmp");
    }
  }
  else if(Op == "<="){
    if (ThisType==type_float){
      return Builder.CreateFCmpOLE(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpSLE(L, R, "cmptmp");
    }
  }
  else if(Op == ">="){
    if (ThisType==type_float){
      return Builder.CreateFCmpOGE(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpSGE(L, R, "cmptmp");
    }
  }
  else if(Op == "=="){
    if (ThisType==type_float){
      return Builder.CreateFCmpOEQ(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpEQ(L, R, "cmptmp");
    }
  }
  else if(Op == "!="){
    if (ThisType==type_float){
      return Builder.CreateFCmpONE(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpNE(L, R, "cmptmp");
    }
  }
  else{
    return LogErrorV("invalid binary operator");
  }
}

llvm::Value *CallExprAST::codegen() {
  // Look up the name in the global module table.
  llvm::Function *CalleeF = TheModule->getFunction(Callee);
  if (!CalleeF)
    return LogErrorV("Unknown function referenced");

  // If argument mismatch error.
  if (CalleeF->arg_size() != Args.size())
    return LogErrorV("Incorrect # arguments passed");

  std::vector<llvm::Value *> ArgsV;
  for (unsigned i = 0, e = Args.size(); i != e; ++i) {
    ArgsV.push_back(Args[i]->codegen());
    if (!ArgsV.back())
      return nullptr;
  }

  return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

llvm::Function *PrototypeAST::codegen() {
  // Make the function type:  double(double,double) etc.
  std::vector<llvm::Type *> Doubles(Args.size(), llvm::Type::getDoubleTy(TheContext));
  llvm::FunctionType *FT =
      llvm::FunctionType::get(llvm::Type::getDoubleTy(TheContext), Doubles, false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, TheModule.get());

  // Set names for all arguments.
  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(Args[Idx++]);

  return F;
}

llvm::Function *FunctionAST::codegen() {
  // First, check for an existing function from a previous 'extern' declaration.
  llvm::Function *TheFunction = TheModule->getFunction(Proto->getName());

  if (!TheFunction)
    TheFunction = Proto->codegen();

  if (!TheFunction)
    return nullptr;

  // Create a new basic block to start insertion into.
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
  Builder.SetInsertPoint(BB);

  // Record the function arguments in the NamedValues map.
  // NamedValues.clear();
  // for (auto &Arg : TheFunction->args())
  //   NamedValues[Arg.getName()] = &Arg;

  if (llvm::Value *RetVal = Body->codegen()) {
    // Finish off the function.
    Builder.CreateRet(RetVal);

    // Validate the generated code, checking for consistency.
    verifyFunction(*TheFunction);

    return TheFunction;
  }

  // Error reading body, remove function.
  TheFunction->eraseFromParent();
  return nullptr;
}