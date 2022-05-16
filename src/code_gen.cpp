#include "ast.hpp"
#include "code_gen.hpp"

static SymbolTable symbolTable;

std::unique_ptr<ExprAST> LogError(const std::string& Str) {
  fprintf(stderr, "Error: %s\n", Str);
  return nullptr;
}

llvm::Value *LogErrorV(const std::string& Str) {
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
    case type_char:
      return llvm::Type::getInt8Ty(TheContext);
    case type_float:
      return llvm::Type::getFloatTy(TheContext);
    default:
      return llvm::Type::getInt32Ty(TheContext);
  }
}

llvm::Function *getFunction(std::string Name) {
  // First, see if the function has already been added to the current module.
  if (auto *F = TheModule->getFunction(Name))
    return F;

  // If not, check whether we can codegen the declaration from some existing
  // prototype.
  // auto FI = FunctionProtos.find(Name);
  // if (FI != FunctionProtos.end())
  //   return FI->second->codegen();

  // If no existing prototype exists, return null.
  return nullptr;
}

/// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.  This is used for mutable variables etc.
static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction,
                                          const std::string &VarName, int dType) {
  llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                   TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(typeGen(dType), nullptr, VarName);
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
    if(!GV) return LogErrorV(std::string("Unknown variable name"));
    else return Builder.CreateLoad(GV, Name.c_str());
  }
  return Builder.CreateLoad(V, Name.c_str());
}

llvm::Value *GlobalDecListAST::codegen() {
  //TODO: to complete
}

llvm::Value *DecListAST::codegen(){
  for (int i = 0;i<VarList.size();i++){
    int type = VarList[i]->getType();
    if (type == type_Dec || type == type_assignExpr){ 
      VarList[i]->codegen();
    }
    else{
      // ERROR !!
      LogErrorV(std::string("illegal DecListAST!"));
    }
  }
}

llvm::Value *DecExprAST::codegen(){
  llvm::Function* Func = Builder.GetInsertBlock()->getParent();
  const std::string &VarName = name;
  int dType = Type->getType();

  //First check redefinition
  if (! symbolTable._FindValue(VarName)){
    symbolTable.addLocalID(VarName, Var.get());
  }
  else{
    std::string err = "Variable redefinition: " + VarName;
    LogErrorV(err);
  }

  llvm::Value* InitVal;
  switch (dType)
  {
  case type_bool:
    InitVal = llvm::ConstantInt::get(typeGen(type_bool), 0, false);
    break;
  case type_int:
    InitVal = llvm::ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    break;
  case type_float:
    InitVal = llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0));
    break;
  default:
    // ERROR
    LogErrorV(std::string("Unknown type!\n"));
    break;
  }

  llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(Func, VarName, dType);
  Builder.CreateStore(InitVal, Alloca);

  symbolTable.addLocalVal(VarName, Alloca);

  return Alloca;
}

llvm::Value *AssignExprAST::codegen(){
  std::string VarName;
  int LType, RType;

  if (LHS->getType() == type_ID){
    VarName = static_cast<VariableExprAST*>(LHS.get())->getName();
    LType = symbolTable.getType(VarName);
  }
  else if(LHS->getType() == type_Dec){
    DecExprAST* tmp = static_cast<DecExprAST*>(LHS.get());
    tmp->codegen();
    VarName = tmp->getName();
    LType = tmp->getDType();
  }
  else{
    std::string err = "Wrong LHS type: "+VarName+" !";
    LogErrorV(err);
  }

  llvm::Value* RHSVal = RHS->codegen();

  if(!RHSVal){
    LogErrorV(std::string("Wrong RHS!"));
    return nullptr;
  }

  llvm::Value* LHSAddr = symbolTable.FindValue(VarName);

  if (RType<LType && LType <= type_float) {
    if (RType == type_bool) RHSVal = Builder.CreateUIToFP(RHSVal, typeGen(LType));
    else RHSVal = Builder.CreateSIToFP(RHSVal, typeGen(LType));
  }
  else if (RType == LType){
    // do nothing
  }
  else{
    std::string err = "Wrong assignment for "+VarName+": type of RHS doesn't match!";
    LogErrorV(err);
  }

  Builder.CreateStore(RHSVal, LHSAddr);
  
  return RHSVal;
}

llvm::Value *BinaryExprAST::codegen() {
  llvm::Value *L = LHS->codegen();
  llvm::Value *R = RHS->codegen();
  if (!L || !R)
    return nullptr;

  int LType = LHS->getType();
  if(LHS->getType()==type_ID){
    std::string name = static_cast<VariableExprAST*>(LHS.get())->getName();
    LType = symbolTable.FindID(name)->getType();
  }

  int RType = RHS->getType();
  if(RHS->getType()==type_ID){
    std::string name = static_cast<VariableExprAST*>(RHS.get())->getName();
    RType = symbolTable.FindID(name)->getType();
  }

  int ThisType;
  if (Op=="+" || Op=="-" || Op=="*"){
    ThisType = (LType > RType)? LType : RType;
    if(LType<ThisType && ThisType == type_float){
      if (LType == type_bool) L = Builder.CreateUIToFP(L, typeGen(ThisType));
      else L = Builder.CreateSIToFP(L, typeGen(ThisType));
    }
    if(RType<ThisType && ThisType == type_float){
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
  else if(Op=="<" || Op==">" || Op=="<=" || Op==">=" || Op=="==" || Op=="!=" || Op=="&&" || Op=="||" || Op=="!"){
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
  else if(Op == "&&"){
    return Builder.CreateAnd(L, R, "andtmp");
  }
  else if(Op == "||"){
    return Builder.CreateOr(L, R, "ortmp");
  }
  else if(Op == "!"){
    return Builder.CreateNot(R, "nottmp");
  }
  else{
    return LogErrorV(std::string("invalid binary operator"));
  }
}

llvm::Value* FuncPrint(ast_list Args){
  static llvm::Function *printFunc = nullptr;
  // not defined before
  if(!printFunc){
    std::vector<llvm::Type*> Arg_List = {typeGen(type_char)};
    llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), Arg_List, false);
    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "printf", TheModule.get());
    //set calling conventions to be C calling conventions
    F->setCallingConv(llvm::CallingConv::C);
    printFunc = F;
  }

  std::string format;
  std::vector<llvm::Value*> printArgs = {nullptr};
  for (int i=0;i<Args.size();i++){
    int type = Args[i]->getType();
    llvm::Value *new_arg;
    if(type == type_binaryExpr){
      // for binary expression
      new_arg = Args[i]->codegen();
      type = Args[i]->getType();
    }
    else if(type == type_ID){
      // for variable
      new_arg = Args[i]->codegen();
      type = symbolTable.getType(static_cast<VariableExprAST*>(Args[i].get())->getName());
    }
    else if(type == type_CallFunc){
      // for function calls
      new_arg = Args[i]->codegen();
      std::string Callee = static_cast<CallExprAST *>(Args[i].get())->getCallee();
      type = symbolTable.getProtoType(Callee)->getRetType();
    }
    else if(type > 0 && type < type_float){
      // for numbers or bools
      new_arg = Args[i]->codegen();
    }
    else{
      LogErrorV(std::string("Wrong type for print"));
      return nullptr;
    }

    if (type == type_bool || type == type_int){
      format += "%d";
      printArgs.push_back(new_arg);
    }
    else if(type == type_float){
      format += "%f";
      printArgs.push_back(new_arg);
    }
  }

  printArgs[0] = Builder.CreateGlobalStringPtr(format, "printfomat");
  return Builder.CreateCall(printFunc, printArgs, "printtmp");
}

llvm::Value *CallExprAST::codegen() {
  if (Callee == "print"){
    return FuncPrint(std::move(Args));
  }
  
  // Look up the name in the global module table.
  llvm::Function *CalleeF = getFunction(Callee);
  if (!CalleeF)
    return LogErrorV(std::string("Unknown function referenced"));

  // If argument mismatch error.
  if (CalleeF->arg_size() != Args.size())
    return LogErrorV(std::string("Incorrect # arguments passed"));

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
  // check the data type for every arg
  std::vector<llvm::Type *> Arg_List;
  int returnType = retType->getType();
  llvm::FunctionType *FT;

  if (Name == "main"){
     FT = llvm::FunctionType::get(typeGen(returnType), false);
  }
  else{
    for (int i=0;i<Args.size();i++){
      int type = static_cast<DecExprAST*>(Args[i].get())->getDType();
      Arg_List.push_back(typeGen(type));
    }
    FT = llvm::FunctionType::get(typeGen(returnType), Arg_List, false);
  }

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, TheModule.get());

  // Set names for all arguments.
  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(static_cast<DecExprAST*>(Args[Idx++].get())->getName());

  symbolTable.addProtoType(Name, this);

  return F;
}

llvm::Value *BodyAST::codegen() {
  for (int i=0;i<DefList.size();i++){
    DefList[i]->codegen();
  }
  for (int i=0;i<StmtList.size();i++){
    // tell the type of stmt
    StmtList[i]->codegen();
  }
  if (ReturnExpr){
    return ReturnExpr->codegen();
  }
  return llvm::ConstantPointerNull::getNullValue(typeGen(type_int));;
}

llvm::Function *FunctionAST::codegen() {
  // First, check for an existing function from a previous 'extern' declaration.
  llvm::Function *TheFunction = getFunction(Proto->getName());

  if (!TheFunction)
    TheFunction = Proto->codegen();

  if (!TheFunction){
    std::string err = "No prototype defined for function!";
    LogErrorV(err);
    return nullptr;
  }
  // Create a new basic block to start insertion into.
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
  Builder.SetInsertPoint(BB);

  // add new variable field into symboltable
  symbolTable.pushIDTable();
  symbolTable.pushNamedValue();

  if (llvm::Value *RetVal = Body->codegen()) {
    // Finish off the function.
    Builder.CreateRet(RetVal);

    // Validate the generated code, checking for consistency.
    llvm::verifyFunction(*TheFunction);
    // pop variable field from symboltable
    symbolTable.popIDTable();
    symbolTable.popNamedValue();

    return TheFunction;
  }

  // pop variable field from symboltable
  symbolTable.popIDTable();
  symbolTable.popNamedValue();

  // Error reading body, remove function.
  TheFunction->eraseFromParent();
  std::string err = "Fail to generate body for function "+Proto->getName();
  LogErrorV(err);
  return nullptr;
}

void *ProgramAST::codegen(){
    // for C++ 14
    TheModule = std::make_unique<llvm::Module>("Code Gen", TheContext);

    for(int i=0;i<ElementList.size();i++){
        ElementList[i]->codegen();
    }

    // print out TheModule
    TheModule->print(llvm::errs(), nullptr);
}