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

llvm::Type *typeGen(int type, std::string* name=nullptr){
  static llvm::Type* Type_String = nullptr;
  if (type == type_string) { 
    if(!Type_String){
      char buffer[256];
      memset(buffer, 0, 256);
      llvm::StringRef bufferRef(buffer, 255);
      llvm::Constant *strname = llvm::ConstantDataArray::getString(TheContext, bufferRef);
      TheModule->getOrInsertGlobal("strtype", strname->getType());
      llvm::GlobalVariable *gVar = TheModule->getNamedGlobal("strtype");
      Type_String = gVar->getType();
    }
  }
  switch (type){
    case type_void:
      return llvm::Type::getVoidTy(TheContext);
    case type_bool:
      return llvm::Type::getInt1Ty(TheContext);
    case type_int:
      return llvm::Type::getInt32Ty(TheContext);
    case type_intptr:
      return llvm::Type::getInt32PtrTy(TheContext);
    case type_char:
      return llvm::Type::getInt8Ty(TheContext);
    case type_charptr:
      return llvm::Type::getInt8PtrTy(TheContext);
    case type_float:
      return llvm::Type::getDoubleTy(TheContext);
    case type_floatptr:
      return llvm::Type::getDoublePtrTy(TheContext);
    case type_string:
      return Type_String;
    case type_struct:
      return symbolTable.FindStruct(*name)->getStructType();
    case type_structptr:
      return symbolTable.FindStruct(*name)->getStructPtrType();
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
                                          const std::string &VarName, int dType, std::string* typeName = nullptr) {
  llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                   TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(typeGen(dType, typeName), nullptr, VarName);
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

llvm::Value *CreateStringMem(llvm::StringRef bufferRef) {
  llvm::Constant *strname = llvm::ConstantDataArray::getString(TheContext, bufferRef);
  llvm::Value *strmem = Builder.CreateAlloca(strname->getType(), llvm::ConstantExpr::getSizeOf(strname->getType()));

  std::vector<llvm::Value*> index_vector;
  index_vector.push_back(llvm::ConstantInt::get(typeGen(type_int), 0));
  llvm::Value *valueAsPtr = Builder.CreateGEP(strmem, index_vector, "strtmp");
  
  Builder.CreateStore(strname, valueAsPtr);
  return strmem;
}

llvm::Value *StringExprAST::codegen() {
  char buffer[256];
  memset(buffer, 0, 256);
  if(Str.length()>=256){
    std::string err = "The length of string is too long(>255)!";
    LogErrorV(this->getLineno(), err);
    return nullptr;
  }
  Str.copy(buffer, Str.length(), 0);
  // std::string tmpstr(buffer);
  llvm::StringRef bufferRef(buffer, 255);
  // if(global){
  //   return Builder.CreateGlobalString(bufferRef, "str");
  // }
  // return Builder.CreateLoad(straddr, "tmpstr");
  return CreateStringMem(bufferRef);
}

llvm::Value *ArrayDecAST::codegen() {
  if(size >= 0){
    int dType;
    switch (this->getType())
    {
    case type_intptr:
      dType = type_int;
      break;
    case type_floatptr:
      dType = type_float;
      break;
    default:
      break;
    }
    llvm::ArrayType *arrayType = llvm::ArrayType::get(typeGen(dType), size);
    llvm::Function* Func = Builder.GetInsertBlock()->getParent();
    
    llvm::Value *arrayptr = CreateEntryBlockAlloca(Func, Name, arrayType);
    return arrayptr;
  }
  else{ // for parameters like "a[]" with size=-1
    std::string err;
    llvm::Value *arrayptr = symbolTable.FindValue(Name);
    if(!arrayptr){
      return LogErrorV(this->getLineno(), std::string("No such array!"));
    }
    IntExprAST *zero = new IntExprAST(0);
    llvm::Value* Index = zero->codegen();
    llvm::Value* eleAddr = Builder.CreateInBoundsGEP(arrayptr, Index, "arrayStartAddr");
    return eleAddr;
  }
}

llvm::Value *ArrayEleAST::codegen() {
  // Look this variable.
  llvm::Value *arrayptr = symbolTable._FindValue(Name);
  
  std::string err;
  // ast_list MaxIndexList(arraydec->getMaxIndex());
  llvm::Value *index;
  if(idx_list.size()>1){
    /////////////////////////////////////////////////////////
    ArrayDecAST *arraydec = symbolTable.FindArray(Name);
    if(!arraydec){
      return LogErrorV(this->getLineno(), std::string("No such global array!"));
    }
    BinaryExprAST *result;
    IntExprAST *init = new IntExprAST(0);
    std::string mul = "*";
    std::string add = "+";
    for (int i=idx_list.size()-1;i>=0;i--){
      if(i == idx_list.size()-1) result = new BinaryExprAST(mul, arraydec->getMaxIndex(i), init);
      else result = new BinaryExprAST(mul, arraydec->getMaxIndex(i), result);

      result = new BinaryExprAST(add, idx_list[i].get(), result);
    }
    // get the index for array element access
    index = result->codegen();
    ///////////////////////for multiple dimension global array
  }
  else { // for one dimension local array
    index = idx_list[0]->codegen();
  }
  int dType;

  if (!arrayptr){
    llvm::GlobalVariable *Garrayptr = symbolTable._FindGlobalValue(Name);
    if(!Garrayptr) {
      err = "Unknown variable name: "+Name;
      return LogErrorV(this->getLineno(), err);
    }
    else {
      //set type recursively
      dType = symbolTable.getType(Name);
      if (dType == type_intptr){ 
        this->SetType(type_int);
      }
      else if(dType == type_floatptr){
        this->SetType(type_float);
      }
      // arrayptr = Builder.CreateBitCast(Garrayptr, typeGen(dType), "ElementwiseAddr");
      arrayptr = llvm::GetElementPtrInst::CreateInBounds(Garrayptr, index, "arrayele");
      arrayptr = Builder.CreateBitCast(Garrayptr, typeGen(dType), "ElementwiseAddr");
      llvm::Value* eleAddr = Builder.CreateInBoundsGEP(arrayptr, index, "arrayele");
      return eleAddr;
    }
  }
  // //set type recursively
  dType = symbolTable.getType(Name); // dType is the data type of element rather than pointer type of the whole array
  // // if the array is a parameter rather than declared locally
  if (dType == type_intptr){ 
    this->SetType(type_int);
  }
  else if(dType == type_floatptr){
    this->SetType(type_float);
  }

  llvm::Value* eleAddr = Builder.CreateInBoundsGEP(arrayptr, index, "arrayele");
  return eleAddr;
}

llvm::Value *VariableExprAST::codegen() {
  // Look this variable up in the function.
  llvm::Value *V = symbolTable._FindValue(Name);
  
  if (!V){
    llvm::Value *GV = symbolTable._FindGlobalValue(Name);
    if(!GV) {
      std::string err = "Unknown variable name: "+Name;
      return LogErrorV(this->getLineno(), err);
    }
    else {
      //set type recursively
      this->SetType(symbolTable.getType(Name));
      if(symbolTable.getType(Name)!=type_string){
        return Builder.CreateLoad(GV, Name.c_str());
      }
      else{
        return GV;
      }
    }
  }
  //set type recursively
  this->SetType(symbolTable.getType(Name));
  if(symbolTable.getType(Name)!=type_string and symbolTable.getType(Name) != type_struct) {
    return Builder.CreateLoad(V, Name.c_str());
  }
  else{
    return V;
  }
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

llvm::Value* STDecListAST::codegen() {}

llvm::GlobalVariable *createGlob(std::string name, int dType) {
  TheModule->getOrInsertGlobal(name, typeGen(dType));
  llvm::GlobalVariable *gVar = TheModule->getNamedGlobal(name);
  switch (dType)
    {
    case type_bool:
      gVar->setInitializer(llvm::ConstantInt::get(typeGen(type_bool), 0, false));
      break;
    case type_int:
      gVar->setInitializer(llvm::ConstantInt::get(TheContext, llvm::APInt(32, 0, true)));
      break;
    case type_float:
      gVar->setInitializer(llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)));
      break;
    default:
      // ERROR
      gVar = nullptr;
      break;
    }
  return gVar;
}

llvm::Value *DecExprAST::codegen(){
  if(!global){
    llvm::Function* Func = Builder.GetInsertBlock()->getParent();
    const std::string &VarName = Name;
    int dType = Type->getType();
    std::string* typeName = Type->getNamePtr();
    //First check redefinition
    if (! symbolTable._FindValue(VarName)){
      symbolTable.addLocalID(VarName, getDType());
    }
    else{
      std::string err = "Variable redefinition: " + VarName;
      LogErrorV(this->getLineno(), err);
      return nullptr;
    }

    if(Array != nullptr){
      if(Array->getType() == type_arrayDec){
        Array->SetType(dType);
        // get the memory pointer in [n*i32]* type etc.
        llvm::Value* arrayptr = Array->codegen();
        if(!arrayptr){
          return LogErrorV(this->getLineno(), std::string("Fail to generate array!"));
        }
        // convert ptr into bytewise
        arrayptr = Builder.CreateBitCast(arrayptr, typeGen(dType, typeName), "ElementwiseAddr"); // create element wise ptr like i32* rather than ptr like [n*i32]*
        
        symbolTable.addLocalID(VarName, dType);
        symbolTable.addLocalVal(VarName, arrayptr);
        symbolTable.addArray(VarName, Array.get());
        return arrayptr;
      }
      else if(Array->getType() == type_arrayParam){
        return LogErrorV(this->getLineno(), std::string("Wrong declaration for Array! Size needed!\n"));
      }
    }

    llvm::Value* InitVal;
    char buffer[256];
    memset(buffer, 0, 256);
    llvm::StringRef bufferRef(buffer, 255);
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
    case type_string:
      InitVal = CreateStringMem(bufferRef);
      break;
    case type_struct:
      break;
    default:
      // ERROR
      LogErrorV(this->getLineno(), std::string("Unknown type!"));
      break;
    }
    
    if (dType>0 && dType<type_string){
      llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(Func, VarName, dType);
      Builder.CreateStore(InitVal, Alloca);
      symbolTable.addLocalVal(VarName, Alloca);
      return Alloca;
    } else if(dType == type_string){
      // no need to store, since string is a global variable
      symbolTable.addLocalVal(VarName, InitVal);
      return InitVal;
    } else if(dType == type_struct) {
      llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(Func, VarName, dType, typeName);
      symbolTable.addLocalVal(VarName, Alloca);
      auto* structAST = symbolTable.FindStruct(*typeName);
      symbolTable.mapStruct(VarName, structAST);
    }
    return nullptr;
  }
  else { //for global variables
    // llvm::Function* Func = Builder.GetInsertBlock()->getParent();
    const std::string &VarName = Name;
    int dType = Type->getType();

    //First check redefinition
    if (!symbolTable._FindGlobalValue(VarName)){
      symbolTable.addGlobalID(VarName, getDType());
    }
    else{
      std::string err = "Global Variable redefinition: " + VarName;
      LogErrorV(this->getLineno(), err);
    }

    if(Array != nullptr){
      if(Array->getType() == type_arrayDec){
        Array->SetType(dType);
        // get the memory pointer in [n*i32]* type etc.
        llvm::ArrayType *arrayType = llvm::ArrayType::get(typeGen(this->getType()), Array->getSize());
        // TheModule->getOrInsertGlobal(VarName, arrayType);
        llvm::GlobalVariable *arrayptr = new llvm::GlobalVariable(*TheModule.get(), arrayType, false, llvm::GlobalValue::InternalLinkage, 0, VarName);
        arrayptr->setAlignment(llvm::MaybeAlign(4));
        if(!arrayptr){
          return LogErrorV(this->getLineno(), std::string("Fail to generate array!"));
        }
        // here we don't convert ptr into bytewise
        llvm::ConstantAggregateZero* const_array = llvm::ConstantAggregateZero::get(arrayType);
        arrayptr->setInitializer(const_array);

        symbolTable.addGlobalID(VarName, dType);
        symbolTable.addGlobalVal(VarName, arrayptr);
        symbolTable.addArray(VarName, Array.get());
        return arrayptr;
      }
      else if(Array->getType() == type_arrayParam){
        return LogErrorV(this->getLineno(), std::string("Wrong Global declaration for Array! Size needed!\n"));
      }
    }

    llvm::GlobalVariable* gVar;
    char buffer[256];
    memset(buffer, 256, 0);
    llvm::StringRef bufferRef(buffer, 255);
    if(dType>=0 && dType<=type_float){
      gVar = createGlob(VarName, dType);
      if(!gVar){
        std::string err = "Unknown type!";
        LogErrorV(this->getLineno(), err);
        return nullptr;
      }
    }
    else if(dType == type_string){
      // gVar = Builder.CreateGlobalString(bufferRef, "globalstr");
      // llvm::ArrayType* stringType = llvm::ArrayType::get(typeGen(type_char), 255);
      llvm::Constant *strname = llvm::ConstantDataArray::getString(TheContext, bufferRef);
      TheModule->getOrInsertGlobal(VarName, strname->getType());
      gVar = TheModule->getNamedGlobal(VarName);
      gVar->setInitializer(strname);
    }
    else{
      std::string err = "Unknown type!";
      LogErrorV(this->getLineno(), err);
      return nullptr;
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

  llvm::BasicBlock *CondBB = llvm::BasicBlock::Create(TheContext, "CondBB", TheFunction);
  llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
  llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "afterloop", TheFunction);

  Builder.CreateBr(CondBB);
  Builder.SetInsertPoint(CondBB);
  // Compute the end condition.
  llvm::Value* EndCond = Condv->codegen();
  if (!EndCond)
    return nullptr;

  // Convert condition to a bool by comparing non-equal to 0.0.
  EndCond = Builder.CreateICmpNE(EndCond, llvm::ConstantInt::get(typeGen(type_bool), 0, false), "loopcond");

  llvm::BasicBlock *PreloopBB = Builder.GetInsertBlock();
  // Insert the conditional branch into the end of LoopEndBB.
  Builder.CreateCondBr(EndCond, LoopBB, AfterBB);
  // Start insertion in LoopBB.
  Builder.SetInsertPoint(LoopBB);
  // Emit the body of the loop.  This, like any other expr, can change the
  // current BB.  Note that we ignore the value computed by the body, but don't
  // allow an error.
  if (!Body->codegen())
    return nullptr;

  // Create the "after loop" block and insert it.
  llvm::BasicBlock *LoopEndBB = Builder.GetInsertBlock();

  Builder.CreateBr(CondBB);
  // Any new code will be inserted in AfterBB.
  Builder.SetInsertPoint(AfterBB);

  // Start the PHI node with an entry for Start.
  llvm::PHINode *Variable = Builder.CreatePHI(typeGen(type_int), 2, "loopexit");

  Variable->addIncoming(intVal, CondBB);
  Variable->addIncoming(intVal, LoopEndBB);
  
  // for expr always returns 0.0.
  return llvm::Constant::getNullValue(llvm::Type::getDoubleTy(TheContext));
}

llvm::Value *AssignExprAST::codegen(){
  std::string VarName;
  int LType, RType;
  llvm::Value *RHSVal, *LHSAddr;
  RHSVal = nullptr;
  LHSAddr = nullptr;

  if (LHS->getType() == type_ID){
    VarName = static_cast<VariableExprAST*>(LHS.get())->getName();
    LType = symbolTable.getType(VarName);
  }
  else if(LHS->getType() == type_Dec){
    DecExprAST* tmp = static_cast<DecExprAST*>(LHS.get());
    tmp->codegen(); // recursively set data type
    VarName = tmp->getName();
    LType = symbolTable.getType(VarName);
  }
  else if(LHS->getType() == type_arrayEle){
    ArrayEleAST* tmp = static_cast<ArrayEleAST*>(LHS.get());
    LHSAddr = tmp->codegen(); // get the address of the element
    VarName = tmp->getName();
    LType = symbolTable.getType(VarName);
    if(LType == type_intptr){ // get the type of the pointer
      LType = type_int; // get the data type of element
    }
    else if(LType == type_floatptr){
      LType = type_float;
    }
  }
  else if(LHS->getType() == type_structEle) {
    auto* tmp = static_cast<StructEleAST*>(LHS.get());
    LHSAddr = tmp->codegen();
    LType = tmp->getEleType();
  }
  else{
    std::string err = "Wrong LHS type: "+VarName+" !";
    return LogErrorV(this->getLineno(), err);
  }

  if(RHS->getType() == type_arrayEle){
    RHSVal = Builder.CreateLoad(RHS->codegen(), "arrayElement");
  }
  else if(RHS->getType() == type_structEle) {
    RHSVal = Builder.CreateLoad(RHS->codegen(), "structElement");
  }
  else{
    RHSVal = RHS->codegen();
  }
  
  if(!RHSVal){
    LogErrorV(this->getLineno(), std::string("Wrong RHS!"));
    return nullptr;
  }

  if(!LHSAddr){
    LHSAddr = symbolTable.FindValue(VarName); // get the address of lhs expression
    if(!LHSAddr){
      std::string err = "Unknown variable name: "+VarName;
      return LogErrorV(this->getLineno(), err);
    }
  }

  // get the data type of expression recursicely
  RType = RHS->getType();
  if(RType == type_structEle) {
    auto* tmp = static_cast<StructEleAST*>(RHS.get());
    RType = tmp->getEleType();
  }
  if(LType == type_string && RType == type_string){
    llvm::Value* RHSstr = Builder.CreateLoad(RHSVal, "assigntmpstr");
    std::vector<llvm::Value*> index_vector;
    index_vector.push_back(llvm::ConstantInt::get(typeGen(type_int), 0));
    llvm::Value *valueAsPtr = Builder.CreateGEP(LHSAddr, index_vector, "strtmp");
    Builder.CreateStore(RHSstr, valueAsPtr);
    // llvm::MaybeAlign align(1);
    // Builder.CreateMemCpy(LHSAddr, align, RHSVal, align, 256);
    return RHSVal;
  }
  else if(LType == type_string && RType != type_string){
    std::string err = "Wrong assignment for string!";
    LogErrorV(this->getLineno(), err);
    return nullptr;
  }

  if (RType<LType && LType <= type_float) {
    if (RType == type_bool) RHSVal = Builder.CreateUIToFP(RHSVal, typeGen(LType));
    else RHSVal = Builder.CreateSIToFP(RHSVal, typeGen(LType));
  }
  else if (RType == LType && LType <= type_float){
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
    return nullptr;
  }

  Builder.CreateStore(RHSVal, LHSAddr);
  
  return RHSVal;
}

llvm::Value *BinaryExprAST::codegen() {
  llvm::Value *L;
  llvm::Value *R;
  
  int LType = LHS->getType();
  if(LType==type_ID){
    std::string name = static_cast<VariableExprAST*>(LHS.get())->getName();
    L = LHS->codegen();
    LType = symbolTable.FindID(name);
  }
  else if(LType == type_arrayEle){
    ArrayEleAST* tmp = static_cast<ArrayEleAST*>(LHS.get());
    L = LHS->codegen();
    std::string VarName = tmp->getName();
    LType = LHS->getType();
    L = Builder.CreateLoad(L, "arrayElementValue");
  }
  else{
    L = LHS->codegen();
    LType = LHS->getType();
  }

  int RType = RHS->getType();
  if(RType==type_ID){
    std::string name = static_cast<VariableExprAST*>(RHS.get())->getName();
    R = RHS->codegen();
    RType = symbolTable.FindID(name);
  }
  else if(RType == type_arrayEle){
    ArrayEleAST* tmp = static_cast<ArrayEleAST*>(RHS.get());
    R = RHS->codegen();
    std::string VarName = tmp->getName();
    RType = RHS->getType();
    R = Builder.CreateLoad(R, "arrayElementValue");
  }
  else{
    R = RHS->codegen();
    RType = RHS->getType();
  }

  if (!L || !R)
    return nullptr;

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
  if(ThisType >= type_string){
    std::string err = "Wrong type for binary operation!";
    LogErrorV(this->getLineno(), err);
    return nullptr;
  }

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
    else if(type == type_arrayEle){
      // for array elements
      new_arg = Args[i]->codegen();
      new_arg = Builder.CreateLoad(new_arg, "arrayelement");
      // type = symbolTable.getType(static_cast<ArrayEleAST*>(Args[i].get())->getName());
      type = Args[i]->getType();
    }
    else if(type == type_structEle) {
      // for struct elements
      auto* tmp = static_cast<StructEleAST*>(Args[i].get());
      new_arg = tmp->codegen();
      new_arg = Builder.CreateLoad(new_arg, "structelement");
      type = tmp->getEleType();
    }
    else if(type > 0 && type <= type_float){
      // for numbers or bools
      new_arg = Args[i]->codegen();
    }
    else if(type == type_string){
      new_arg = Args[i]->codegen();    
    }
    else{
      return LogErrorV(lineno, std::string("Wrong type for print"));
    }

    if (type == type_bool || type == type_int){
      format += "%d";
      printArgs.push_back(new_arg);
    }
    else if(type == type_float){
      format += "%f";
      printArgs.push_back(new_arg);
    }
    else if(type == type_string){
      format += "%s";
      printArgs.push_back(new_arg);
    }
    else{
      return LogErrorV(lineno, std::string("Wrong type for print"));
    }
  }
  // if(newline){
  //   format += "\n";
  // }

  printArgs[0] = Builder.CreateGlobalStringPtr(format, "printfomat");
  return Builder.CreateCall(printFunc, printArgs, "printtmp");
}

llvm::Value* FuncRead(int lineno, ast_list Args){
  if(Args.size() > 1){
    return LogErrorV(lineno, std::string("Too much arguments for read!"));
  }
  static llvm::Function *readFunc = nullptr;
  // not defined before
  if(!readFunc){
    std::vector<llvm::Type*> Arg_List = {typeGen(type_charptr)};
    llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), Arg_List, true);
    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "scanf", TheModule.get());
    //set calling conventions to be C calling conventions
    F->setCallingConv(llvm::CallingConv::C);
    readFunc = F;
  }
  
  std::string format;
  std::vector<llvm::Value*> readArgs = {nullptr};
  for (int i=Args.size()-1;i>=0;i--){
    int type = Args[i]->getType();
    llvm::Value *new_arg;
    if(type == type_ID){
      // for variable
      // new_arg = Args[i]->codegen();
      std::string VarName = static_cast<VariableExprAST*>(Args[i].get())->getName();
      type = symbolTable.getType(VarName);
      new_arg = symbolTable.FindValue(VarName);
    }
    else if(type == type_arrayEle){
      // for array elements
      new_arg = Args[i]->codegen();
      // new_arg = Builder.CreateLoad(new_arg, "arrayelement");
      // type = symbolTable.getType(static_cast<ArrayEleAST*>(Args[i].get())->getName());
      type = Args[i]->getType();
    }
    else if(type > 0 && type <= type_float){
      // for numbers or bools
      new_arg = Args[i]->codegen();
    }
    else if(type == type_string){
      new_arg = Args[i]->codegen();    
    }
    else{
      return LogErrorV(lineno, std::string("Wrong type for read"));
    }

    if (type == type_bool || type == type_int){
      format += "%d";
      readArgs.push_back(new_arg);
    }
    else if(type == type_float){
      format += "%f";
      readArgs.push_back(new_arg);
    }
    else if(type == type_string){
      format += "%s";
      readArgs.push_back(new_arg);
    }
    else{
      return LogErrorV(lineno, std::string("Wrong type for read"));
    }
  }

  readArgs[0] = Builder.CreateGlobalStringPtr(format, "readfomat");
  return Builder.CreateCall(readFunc, readArgs, "readtmp");
}

llvm::Value *CallExprAST::codegen() {
  if (Callee == "print"){
    return FuncPrint(this->getLineno(), std::move(Args));
  }
  if (Callee == "read"){
    return FuncRead(this->getLineno(), std::move(Args));
  }
  // Look up the name in the global module table.
  if (this->isMember) {
    auto* tmp = static_cast<VariableExprAST*>(Args[0].get());
    auto* structAST = symbolTable.FindStructDec(tmp->getName());
    Callee = structAST->getName() + "::" + Callee;
  }
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
  if(retDtype == type_void){
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
      auto* tmp = static_cast<DecExprAST*>(Args[i].get());
      int type = tmp->getDType();
      Arg_List.push_back(typeGen(type, tmp->getTypeName()));
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
  // for (int i=DefList.size()-1;i>=0;i--){
  //   DefList[i]->codegen();
  // }
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
  std::cout << "Constructing function: " + Proto->getName() << std::endl;
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
    if (Proto->getArgType(i) == type_intptr || Proto->getArgType(i) == type_floatptr){
      symbolTable.addLocalVal(Arg.getName().str(), &Arg);
    } 
    else if(Proto->getArgType(i) == type_struct) {
      symbolTable.addLocalVal(Arg.getName().str(), Alloca);
      symbolTable.mapStruct(Arg.getName().str(), static_cast<StructAST*>(Proto->getStructName(i)));
    } else if(Proto->getArgType(i) == type_structptr) {
      symbolTable.addLocalVal(Arg.getName().str(), &Arg);
      symbolTable.mapStruct(Arg.getName().str(), static_cast<StructAST*>(Proto->getStructName(i)));
    }
    else {
      symbolTable.addLocalVal(Arg.getName().str(), Alloca);
    }
    // Add arguments to variable symbol table.
    symbolTable.addLocalID(Arg.getName().str(), Proto->getArgType(i++));
  }

  if(Proto->getRetType()!=type_void){
    if (llvm::Value *RetVal = Body->codegen()) {
      // Finish off the function.
      // Builder.CreateRet(RetVal);

      // Validate the generated code, checking for consistency.
      llvm::verifyFunction(*TheFunction);
      // TheFPM->run(*TheFunction);
      // pop variable field from symboltable
      symbolTable.popIDTable();
      symbolTable.popNamedValue();

      return TheFunction;
    }
  }
  else{
    Body->codegen();
    // Validate the generated code, checking for consistency.
    
    Builder.CreateRet(nullptr);
    llvm::verifyFunction(*TheFunction);
    // TheFPM->run(*TheFunction);
    
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

llvm::Value* StructAST::codegen() {
  /*
  Code generation for struct declartion ast.
  Two tasks:
  -> add struct type into symbol table.
  -> generate llvm struct type code.
  */
  llvm::ArrayRef<llvm::Type*> StructFields(this->MemberTypes);
  auto* StructTy = llvm::StructType::create(TheContext, StructFields, this->Name, false);
  auto* StructPtrTy = llvm::PointerType::getUnqual(StructTy);
  this->setStructType(StructTy);
  this->setStructPtrType(StructPtrTy);

  // symbol table
  auto* structSymbol = symbolTable.FindStruct(this->Name);
  if(structSymbol!=nullptr){
    std::string err = "Redefinition of struct "+this->Name;
    LogErrorV(this->getLineno(), err);
    return nullptr;
  }
  else{
    symbolTable.addStruct(this->Name, this);
  }
  for(auto* member: this->MemberFunctions) {
    member->codegen();
  }
}

llvm::Value* StructEleAST::codegen() {
  auto* base_addr = symbolTable.FindValue(this->Name);
  if(base_addr==nullptr){
    std::string err = "Undefined variable "+this->Name;
    LogErrorV(this->getLineno(), err);
    return nullptr;
  }
  auto* struct_def = symbolTable.FindStructDec(this->Name);
  if(struct_def==nullptr){
    std::string err = "Undefined struct "+this->Name;
    LogErrorV(this->getLineno(), err);
    return nullptr;
  }
  auto* st_type = struct_def->getStructType();
  auto* memberNames = struct_def->getMemberNames();
  auto it = std::find(memberNames->begin(), memberNames->end(), this->eleName);
  if(it == memberNames->end()){
    std::string err = "Undefined member "+this->eleName+" in struct "+this->Name;
    LogErrorV(this->getLineno(), err);
    return nullptr;
  }
  auto indice = it - memberNames->begin();
  auto type = struct_def->getMemberTypes()[indice];
  this->eleType = type;
  auto indice_llvm = llvm::ConstantInt::get(typeGen(type_int), indice, false);
  auto indice_zero = llvm::ConstantInt::get(typeGen(type_int), 0, false);
  std::vector<llvm::Value*> indices_vec;
  indices_vec.push_back(indice_zero);
  indices_vec.push_back(indice_llvm);
  llvm::ArrayRef<llvm::Value*> indices(indices_vec);
  // auto* gep_inst = llvm::GetElementPtrInst::Create(st_type, base_addr, indices, "struct_ele");
  auto* value = Builder.CreateGEP(st_type, base_addr, indices, "struct_ele");
  return value;
  // int indice = struct_def->getMemberNames()->indexOf(this->eleName);
  // auto* gep_inst =  
}


StructAST::StructAST(std::string *Name, st_ast_list Members) : Name(*Name) {
  this->SetType(type_structDec);
  // for(auto& member: *Members) {
  //   auto* member_dec = static_cast<DecExprAST*>(member);
  //   MemberNames.push_back(member_dec->getName()); 
  //   MemberTypes.push_back(typeGen(member_dec->getDType()));
  //   MemberTypesInt.push_back(member_dec->getDType());
  // }
  for(auto& member: Members) {
    if(member->getType() == type_DecList) {
      auto* tmp = static_cast<STDecListAST*>(member);
      auto varlist = tmp->getVarList();
      for(auto& var: varlist) {
        auto* var_dec = static_cast<DecExprAST*>(var);
        MemberNames.push_back(var_dec->getName()); 
        MemberTypes.push_back(typeGen(var_dec->getDType()));
        MemberTypesInt.push_back(var_dec->getDType());
      }
    } else if(member->getType() == type_Func) {
       auto* tmp = static_cast<FunctionAST*>(member); 
       tmp->appendClassName(*Name);
       this->MemberFunctions.push_back(tmp);
    }
  }
}

ExprAST* PrototypeAST::getStructName(int i) {
  auto* tmp = static_cast<DecExprAST*>(Args[i].get());
  auto* name = tmp->getTypeName();
  auto* ret = symbolTable.FindStruct(*name);
  return static_cast<ExprAST*>(ret);
}

std::string ProgramAST::codegen(){
  // for C++ 14
  TheModule = std::make_unique<llvm::Module>("Code Gen", TheContext);

  // // Create a new pass manager attached to it.
  // TheFPM = std::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());
  // // Do simple "peephole" optimizations and bit-twiddling optzns.
  // // TheFPM->add(llvm::createInstructionCombiningPass());
  // // Reassociate expressions.
  // TheFPM->add(llvm::createReassociatePass());
  // // Eliminate Common SubExpressions.
  // TheFPM->add(llvm::createGVNPass());
  // // Simplify the control flow graph (deleting unreachable blocks, etc).
  // TheFPM->add(llvm::createCFGSimplificationPass());

  // TheFPM->doInitialization();

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
  return Str;
}