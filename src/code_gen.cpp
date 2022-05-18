#include "ast.hpp"
#include "code_gen.hpp"

static SymbolTable symbolTable;

std::unique_ptr<ExprAST> LogError(const std::string& Str) {
  std::cerr<<"[Code Gen]ERROR: "<<Str<<std::endl;
  return nullptr;
}

llvm::Value *LogErrorV(int lineno, const std::string& Str) {
  LogError("In line: "+std::to_string(lineno)+" "+Str);
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
    case type_charptr:
      return llvm::Type::getInt8PtrTy(TheContext);
    case type_float:
      return llvm::Type::getDoubleTy(TheContext);
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

static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction,
                                          const std::string &VarName, llvm::Type* dType) {
  llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                   TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(dType, nullptr, VarName);
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
    if(!GV) {
      std::string err = "Unknown variable name: "+Name;
      return LogErrorV(this->getLineno(), err);
    }
    else {
      //set type recursively
      this->SetType(symbolTable.getType(Name));
      return Builder.CreateLoad(GV, Name.c_str());
    }
  }
  //set type recursively
  this->SetType(symbolTable.getType(Name));
  return Builder.CreateLoad(V, Name.c_str());
}

llvm::Value *GlobalDecListAST::codegen() {
  //TODO: to complete
  for (int i = VarList.size()-1;i>=0;i--){
    int type = VarList[i]->getType();
    if (type == type_Dec || type == type_assignExpr){ 
      VarList[i]->codegen();
    }
    else{
      // ERROR !!
      LogErrorV(this->getLineno(), std::string("illegal Global DecListAST!"));
    }
  }
}

llvm::Value *DecListAST::codegen(){
  for (int i = VarList.size()-1;i>=0;i--){
    int type = VarList[i]->getType();
    if (type == type_Dec || type == type_assignExpr){ 
      VarList[i]->codegen();
    }
    else{
      // ERROR !!
      LogErrorV(this->getLineno(), std::string("illegal DecListAST!"));
    }
  }
}

llvm::GlobalVariable *createGlob(llvm::Type *type, std::string name) {
  TheModule->getOrInsertGlobal(name, type);
  llvm::GlobalVariable *gVar = TheModule->getNamedGlobal(name);
  return gVar;
}

llvm::Value *DecExprAST::codegen(){
  if(!global){
    llvm::Function* Func = Builder.GetInsertBlock()->getParent();
    const std::string &VarName = name;
    int dType = Type->getType();

    //First check redefinition
    if (! symbolTable._FindValue(VarName)){
      symbolTable.addLocalID(VarName, getDType());
    }
    else{
      std::string err = "Variable redefinition: " + VarName;
      LogErrorV(this->getLineno(), err);
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
      LogErrorV(this->getLineno(), std::string("Unknown type!\n"));
      break;
    }

    llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(Func, VarName, dType);
    Builder.CreateStore(InitVal, Alloca);

    symbolTable.addLocalVal(VarName, Alloca);

    return Alloca;
  }
  else {
    // llvm::Function* Func = Builder.GetInsertBlock()->getParent();
    const std::string &VarName = name;
    int dType = Type->getType();

    //First check redefinition
    if (! symbolTable._FindGlobalValue(VarName)){
      symbolTable.addGlobalID(VarName, getDType());
    }
    else{
      std::string err = "Global Variable redefinition: " + VarName;
      LogErrorV(this->getLineno(), err);
    }

    llvm::GlobalVariable* gVar;
    switch (dType)
    {
    case type_bool:
      gVar = createGlob(typeGen(type_bool), VarName);
      gVar->setInitializer(llvm::ConstantInt::get(typeGen(type_bool), 0, false));
      break;
    case type_int:
      gVar = createGlob(typeGen(type_int), VarName);
      gVar->setInitializer(llvm::ConstantInt::get(TheContext, llvm::APInt(32, 0, true)));
      break;
    case type_float:
      gVar = createGlob(typeGen(type_float), VarName);
      gVar->setInitializer(llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)));
      break;
    default:
      // ERROR
      LogErrorV(this->getLineno(), std::string("Unknown type!\n"));
      break;
    }
    
    symbolTable.addGlobalVal(VarName, gVar);

    return gVar;
  }
}

llvm::Value *IfExprAST::codegen(){
  llvm::Value *Condv = Cond->codegen();
  if(!Condv){
    std::string err = "No arg for IF condition!";
    LogErrorV(this->getLineno(), err);
    return nullptr;
  }
  
  int dType = Cond->getType();
  if (dType == type_float){
    Condv = Builder.CreateFCmpONE(Condv, llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)), "ifcond");
  }
  else if(dType == type_bool){
    Condv = Builder.CreateICmpNE(Condv, llvm::ConstantInt::get(typeGen(type_bool), 0, false), "ifcond");
  }
  else if(dType == type_int){
    Condv = Builder.CreateICmpNE(Condv, llvm::ConstantInt::get(typeGen(type_int), 0, false), "ifcond");
  }
  else{
    std::string err = "Wrong condition type!";
    LogErrorV(this->getLineno(), err);
    return nullptr;
  }

  llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

  llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
  llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(TheContext, "else");
  llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(TheContext, "ifcont");
  Builder.CreateCondBr(Condv, ThenBB, ElseBB);

  // place holder
  IntExprAST* intexpr = new IntExprAST(0);
  llvm::Value* intVal = intexpr->codegen();

  // Emit then value.
  Builder.SetInsertPoint(ThenBB);
  llvm::Value *ThenV = Then->codegen();
  if (!ThenV)
    return nullptr;
  Builder.CreateBr(MergeBB);
  // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
  ThenBB = Builder.GetInsertBlock();

  // Emit else block.
  TheFunction->getBasicBlockList().push_back(ElseBB);
  Builder.SetInsertPoint(ElseBB);
  llvm::Value *ElseV = Else->codegen();
  if (!ElseV)
    return nullptr;
  Builder.CreateBr(MergeBB);
  // codegen of 'Else' can change the current block, update ElseBB for the PHI.
  ElseBB = Builder.GetInsertBlock();

  TheFunction->getBasicBlockList().push_back(MergeBB);
  Builder.SetInsertPoint(MergeBB);

  llvm::PHINode *PN = Builder.CreatePHI(typeGen(type_int), 2, "iftmp");

  PN->addIncoming(intVal, ThenBB);
  PN->addIncoming(intVal, ElseBB);
  return PN;
}

llvm::Value* ForExprAST::codegen(){
  AssignExprAST* StartExpr = new AssignExprAST(ID.get(), Start.get());
  llvm::Value* StartVal = StartExpr->codegen();
  if(!StartVal){
    return nullptr;
  }
  // placegolder
  IntExprAST* intexpr = new IntExprAST(0);
  llvm::Value* intVal = intexpr->codegen();
  // Make the new basic block for the loop header, inserting after current
  // block.
  llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
  llvm::BasicBlock *PreheaderBB = Builder.GetInsertBlock();
  llvm::BasicBlock *LoopBB =
      llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
  // Insert an explicit fall through from the current block to the LoopBB.
  Builder.CreateBr(LoopBB);
  // Start insertion in LoopBB.
  Builder.SetInsertPoint(LoopBB);
  // Start the PHI node with an entry for Start.
  llvm::PHINode *Variable = Builder.CreatePHI(typeGen(type_int), 2, "loopentry");
  Variable->addIncoming(intVal, PreheaderBB);
  // Emit the body of the loop.  This, like any other expr, can change the
  // current BB.  Note that we ignore the value computed by the body, but don't
  // allow an error.
  if (!Body->codegen())
    return nullptr;
  
  BinaryExprAST* AddStep = new BinaryExprAST(std::string("+"), ID.get(), Step.get());
  AssignExprAST* StepExpr = new AssignExprAST(ID.get(), AddStep);
  llvm::Value* StepVal = StepExpr->codegen();
  if (!StepVal)
    return nullptr;

  // llvm::Value *NextVar = Builder.CreateAdd(Variable, StepVal, "nextvar");

  // Compute the end condition.
  BinaryExprAST* EndExpr = new BinaryExprAST(std::string("<"), ID.get(), End.get());
  llvm::Value* EndCond = EndExpr->codegen();
  if (!EndCond)
    return nullptr;

  // Convert condition to a bool by comparing non-equal to 0.0.
  EndCond = Builder.CreateICmpNE(EndCond, llvm::ConstantInt::get(typeGen(type_bool), 0, false), "loopcond");

  // Create the "after loop" block and insert it.
  llvm::BasicBlock *LoopEndBB = Builder.GetInsertBlock();
  llvm::BasicBlock *AfterBB =
      llvm::BasicBlock::Create(TheContext, "afterloop", TheFunction);
  // Insert the conditional branch into the end of LoopEndBB.
  Builder.CreateCondBr(EndCond, LoopBB, AfterBB);
  // Any new code will be inserted in AfterBB.
  Builder.SetInsertPoint(AfterBB);

  // Add a new entry to the PHI node for the backedge.
  Variable->addIncoming(intVal, LoopEndBB);
  
  // for expr always returns 0.0.
  return llvm::Constant::getNullValue(llvm::Type::getDoubleTy(TheContext));
}

llvm::Value* WhileExprAST::codegen(){
  // placegolder
  IntExprAST* intexpr = new IntExprAST(0);
  llvm::Value* intVal = intexpr->codegen();
  // Make the new basic block for the loop header, inserting after current
  // block.
  llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
  llvm::BasicBlock *PreheaderBB = Builder.GetInsertBlock();
  llvm::BasicBlock *LoopBB =
      llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
  // Insert an explicit fall through from the current block to the LoopBB.
  Builder.CreateBr(LoopBB);
  // Start insertion in LoopBB.
  Builder.SetInsertPoint(LoopBB);
  // Start the PHI node with an entry for Start.
  llvm::PHINode *Variable = Builder.CreatePHI(typeGen(type_int), 2, "loopentry");
  Variable->addIncoming(intVal, PreheaderBB);
  // Emit the body of the loop.  This, like any other expr, can change the
  // current BB.  Note that we ignore the value computed by the body, but don't
  // allow an error.
  if (!Body->codegen())
    return nullptr;
  
  // Compute the end condition.
  llvm::Value* EndCond = Condv->codegen();
  if (!EndCond)
    return nullptr;

  // Convert condition to a bool by comparing non-equal to 0.0.
  EndCond = Builder.CreateICmpNE(EndCond, llvm::ConstantInt::get(typeGen(type_bool), 0, false), "loopcond");

  // Create the "after loop" block and insert it.
  llvm::BasicBlock *LoopEndBB = Builder.GetInsertBlock();
  llvm::BasicBlock *AfterBB =
      llvm::BasicBlock::Create(TheContext, "afterloop", TheFunction);
  // Insert the conditional branch into the end of LoopEndBB.
  Builder.CreateCondBr(EndCond, LoopBB, AfterBB);
  // Any new code will be inserted in AfterBB.
  Builder.SetInsertPoint(AfterBB);

  // Add a new entry to the PHI node for the backedge.
  Variable->addIncoming(intVal, LoopEndBB);
  
  // for expr always returns 0.0.
  return llvm::Constant::getNullValue(llvm::Type::getDoubleTy(TheContext));
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
    LogErrorV(this->getLineno(), err);
  }

  llvm::Value* RHSVal = RHS->codegen();

  if(!RHSVal){
    LogErrorV(this->getLineno(), std::string("Wrong RHS!"));
    return nullptr;
  }

  llvm::Value* LHSAddr = symbolTable.FindValue(VarName);
  if(!LHSAddr){
    std::string err = "Unknown variable name: "+VarName;
    return LogErrorV(this->getLineno(), err);
  }

  // get the type of expression recursicely
  RType = RHS->getType();
  if (RType<LType && LType <= type_float) {
    if (RType == type_bool) RHSVal = Builder.CreateUIToFP(RHSVal, typeGen(LType));
    else RHSVal = Builder.CreateSIToFP(RHSVal, typeGen(LType));
  }
  else if (RType == LType){
    // do nothing
  }
  else{
    std::string rhs_type;
    switch (RType)
    {
    case type_bool:
      rhs_type="bool";
      break;
    case type_int:
      rhs_type="int";
      break;
    case type_float:
      rhs_type="float";
      break;
    default:
      rhs_type="unknown type";
      break;
    }
    std::string err = "Wrong assignment for "+VarName+": type of RHS doesn't match! RHS type:"+rhs_type+"!";
    LogErrorV(this->getLineno(), err);
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
    LType = symbolTable.FindID(name);
  }

  int RType = RHS->getType();
  if(RHS->getType()==type_ID){
    std::string name = static_cast<VariableExprAST*>(RHS.get())->getName();
    RType = symbolTable.FindID(name);
  }

  int ThisType, MaxType;
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
    MaxType = (LType > RType)? LType : RType;
    if(LType<MaxType && MaxType == type_float){
      if (LType == type_bool) L = Builder.CreateUIToFP(L, typeGen(MaxType));
      else L = Builder.CreateSIToFP(L, typeGen(MaxType));
    }
    if(RType<MaxType && MaxType == type_float){
      if (RType == type_bool) R = Builder.CreateUIToFP(R, typeGen(MaxType));
      else R = Builder.CreateSIToFP(R, typeGen(MaxType));
    }
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
    if (MaxType==type_float){
      return Builder.CreateFCmpOLT(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpSLT(L, R, "cmptmp");
    }
  }
  else if(Op == ">"){
    if (MaxType==type_float){
      return Builder.CreateFCmpOGT(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpSGT(L, R, "cmptmp");
    }
  }
  else if(Op == "<="){
    if (MaxType==type_float){
      return Builder.CreateFCmpOLE(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpSLE(L, R, "cmptmp");
    }
  }
  else if(Op == ">="){
    if (MaxType==type_float){
      return Builder.CreateFCmpOGE(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpSGE(L, R, "cmptmp");
    }
  }
  else if(Op == "=="){
    if (MaxType==type_float){
      return Builder.CreateFCmpOEQ(L, R, "cmptmp");
    }
    else{
      return Builder.CreateICmpEQ(L, R, "cmptmp");
    }
  }
  else if(Op == "!="){
    if (MaxType==type_float){
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
    return LogErrorV(this->getLineno(), std::string("invalid binary operator"));
  }
}

llvm::Value* FuncPrint(int lineno, ast_list Args){
  static llvm::Function *printFunc = nullptr;
  // not defined before
  if(!printFunc){
    std::vector<llvm::Type*> Arg_List = {typeGen(type_charptr)};
    llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), Arg_List, true);
    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "printf", TheModule.get());
    //set calling conventions to be C calling conventions
    F->setCallingConv(llvm::CallingConv::C);
    printFunc = F;
  }

  std::string format;
  std::vector<llvm::Value*> printArgs = {nullptr};
  for (int i=Args.size()-1;i>=0;i--){
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
    else if(type > 0 && type <= type_float){
      // for numbers or bools
      new_arg = Args[i]->codegen();
    }
    else{
      LogErrorV(lineno, std::string("Wrong type for print"));
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

  format += "\n";

  printArgs[0] = Builder.CreateGlobalStringPtr(format, "printfomat");
  return Builder.CreateCall(printFunc, printArgs, "printtmp");
}

llvm::Value *CallExprAST::codegen() {
  if (Callee == "print"){
    return FuncPrint(this->getLineno(), std::move(Args));
  }
  
  // Look up the name in the global module table.
  llvm::Function *CalleeF = getFunction(Callee);
  if (!CalleeF)
    return LogErrorV(this->getLineno(), std::string("Unknown function referenced"));

  // If argument mismatch error.
  if (CalleeF->arg_size() != Args.size())
    return LogErrorV(this->getLineno(), std::string("Incorrect # arguments passed"));

  std::vector<llvm::Value *> ArgsV;
  for (unsigned i = 0, e = Args.size(); i != e; ++i) {
    ArgsV.push_back(Args[i]->codegen());
    if (!ArgsV.back())
      return nullptr;
  }

  // set data type recursively
  int retDtype = symbolTable.getProtoType(Callee)->getRetType();
  this->SetType(retDtype);

  // bool HasReturn = symbolTable.getProtoType(Callee)->hasReturn();
  int retType = symbolTable.getProtoType(Callee)->getRetType();
  if(retType == type_void){
    return Builder.CreateCall(CalleeF, ArgsV);
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
  // add new variable field into symboltable
  symbolTable.pushIDTable();
  symbolTable.pushNamedValue();
  for (int i=DefList.size()-1;i>=0;i--){
    DefList[i]->codegen();
  }
  for (int i=StmtList.size()-1;i>=0;i--){
    // tell the type of stmt
    StmtList[i]->codegen();
  }
  if(RetType>type_void && HasReturn==1){ //return type not void, has return expr
    llvm::Value* val = ReturnExpr->codegen();
    Builder.CreateRet(val);
    symbolTable.popIDTable();
    symbolTable.popNamedValue();
    return val;
  }
  else if(RetType==type_void && HasReturn==1){ //return type void, has return expr
    Builder.CreateRet(nullptr);
    symbolTable.popIDTable();
    symbolTable.popNamedValue();
    return nullptr;
  }
  else if(RetType==0 && HasReturn==1){ //has return expr, for if, while, for
    llvm::Value* val = ReturnExpr->codegen();
    if(ReturnExpr->getType()!=type_void){
      Builder.CreateRet(val);
    }
    else{
      Builder.CreateRet(nullptr);
    }
    // insert new block
    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *afterRetBB = llvm::BasicBlock::Create(TheContext, "after_ret");
    TheFunction->getBasicBlockList().push_back(afterRetBB);
    Builder.SetInsertPoint(afterRetBB);
    symbolTable.popIDTable();
    symbolTable.popNamedValue();
    return val;
  }
  else if (RetType>type_void && HasReturn==0){ //return type not void, doesn't has return expr
    ExprAST* DefaultReturnExpr;
    llvm::Value *val;
    if (RetType == type_float){
      val = llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0));
    }
    else if(RetType == type_bool || RetType == type_int){
      val = llvm::ConstantInt::get(typeGen(RetType), 0, false);
    }
    Builder.CreateRet(val);
    
    // IntExprAST* intexpr = new IntExprAST(0);
    // BinaryExprAST* placeholder = new BinaryExprAST("+", intexpr, intexpr);
    // placeholder->codegen();
    symbolTable.popIDTable();
    symbolTable.popNamedValue();
    return val;
  }
  symbolTable.popIDTable();
  symbolTable.popNamedValue();
  return llvm::ConstantPointerNull::getNullValue(typeGen(type_int));;
}

llvm::Function *FunctionAST::codegen() {
  // First, check for an existing function from a previous 'extern' declaration.
  llvm::Function *TheFunction = getFunction(Proto->getName());

  if (!TheFunction)
    TheFunction = Proto->codegen();

  if (!TheFunction){
    std::string err = "No prototype defined for function!";
    LogErrorV(this->getLineno(), err);
    return nullptr;
  }
  // Create a new basic block to start insertion into.
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
  Builder.SetInsertPoint(BB);

  // add new variable field into symboltable
  symbolTable.pushIDTable();
  symbolTable.pushNamedValue();

  int i=0;
  for (auto &Arg : TheFunction->args()) {
    // Create an alloca for this variable.
    llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, Arg.getName().str(), Arg.getType());

    // Store the initial value into the alloca.
    Builder.CreateStore(&Arg, Alloca);

    // Add arguments to variable symbol table.
    symbolTable.addLocalVal(Arg.getName().str(), Alloca);
    symbolTable.addLocalID(Arg.getName().str(), Proto->getArgType(i++));
  }

  if(Proto->getRetType()!=type_void){
    if (llvm::Value *RetVal = Body->codegen()) {
      // Finish off the function.
      // Builder.CreateRet(RetVal);

      // Validate the generated code, checking for consistency.
      llvm::verifyFunction(*TheFunction);
      // pop variable field from symboltable
      symbolTable.popIDTable();
      symbolTable.popNamedValue();

      return TheFunction;
    }
  }
  else{
    Body->codegen();
    // Validate the generated code, checking for consistency.
    llvm::verifyFunction(*TheFunction);
    Builder.CreateRet(nullptr);
    // insert new block
    // llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
    // llvm::BasicBlock *afterRetBB = llvm::BasicBlock::Create(TheContext, "after_ret");
    // TheFunction->getBasicBlockList().push_back(afterRetBB);
    // Builder.SetInsertPoint(afterRetBB);

    // IntExprAST* intexpr = new IntExprAST(0);
    // BinaryExprAST* placeholder = new BinaryExprAST("+", intexpr, intexpr);
    // placeholder->codegen();
    
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
  LogErrorV(this->getLineno(), err);
  return nullptr;
}

void *ProgramAST::codegen(){
  // for C++ 14
  TheModule = std::make_unique<llvm::Module>("Code Gen", TheContext);

  for(int i=ElementList.size()-1;i>=0;i--){
    ElementList[i]->codegen();
  }

  // // print TheModule to raw_ostream    
  // TheModule->print(llvm::errs(), nullptr);
  // print TheModule to file
  std::string Str;
  llvm::raw_string_ostream OS(Str);
  OS << *TheModule.get();
  OS.flush();
  std::ofstream outfile;
  outfile.open("a.ll");
  outfile << Str;
  outfile.close();
}