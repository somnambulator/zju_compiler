#include "ast.hpp"

Json::Value TypeAST::print(){
    Json::Value root;
    root["name"] = "TypeAST: " + this->getTypeStr();
    return root;
}

Json::Value IntExprAST::print(){
    Json::Value root;
    root["name"] = "IntExprAST: " + std::to_string(Val);
    return root;
}

Json::Value FloatExprAST::print(){
    Json::Value root;
    root["name"] = "FloatExprAST: " + std::to_string(Val);
    return root;
}

Json::Value VoidExprAST::print(){
    Json::Value root;
    root["name"] = "VoidExprAST";
    return root;
}

Json::Value StringExprAST::print(){
    Json::Value root;
    root["name"] = "StringExprAST";
    return root;
}

Json::Value ArrayDecAST::print(){
    Json::Value root;
    root["name"] = "ArrayDecAST: "+Name+", size:"+std::to_string(size);
    return root;
}

Json::Value ArrayEleAST::print(){
    Json::Value root;
    root["name"] = "ArrayEleAST: "+Name;
    return root;
}

Json::Value VariableExprAST::print(){
    Json::Value root;
    root["name"] = "VariableExprAST: "+Name;
    return root;
}

Json::Value GlobalDecListAST::print(){
    Json::Value root;
    root["name"] = "GlobalDecListAST";
    for (int i=VarList.size()-1;i>=0;i--){
        root["children"].append(VarList[i]->print());
    }
    return root;
}

Json::Value DecListAST::print(){
    Json::Value root;
    root["name"] = "DecListAST";
    for (int i=VarList.size()-1;i>=0;i--){
        root["children"].append(VarList[i]->print());
    }
    return root;
}

Json::Value STDecListAST::print(){
    Json::Value root;
    root["name"] = "STDecListAST";
    // for (int i=VarList.size()-1;i>=0;i--){
    //     root["children"].append(VarList[i]->print());
    // }
    return root;
}

Json::Value DecExprAST::print(){
    Json::Value root;
    root["name"] = "DecExprAST";
    if(Var) root["children"].append(Var->print());
    else if(Array) root["children"].append(Array->print());
    root["children"].append(Type->print());
    if(global) {
        root["global"] = true;
    } else {
        root["global"] = false;
    }
    return root;
}

Json::Value IfExprAST::print(){
    Json::Value root;
    root["name"] = "IfExprAST";
    root["children"].append(Cond->print());
    root["children"].append(Then->print());
    root["children"].append(Else->print());
    return root;
}

Json::Value ForExprAST::print(){
    Json::Value root;
    root["name"] = "ForExprAST";
    root["children"].append(ID->print());
    root["children"].append(Start->print());
    root["children"].append(End->print());
    root["children"].append(Step->print());
    root["children"].append(Body->print());
    return root;
}

Json::Value WhileExprAST::print(){
    Json::Value root;
    root["name"] = "WhileExprAST";
    root["children"].append(Condv->print());
    root["children"].append(Body->print());
    return root;
}

Json::Value AssignExprAST::print(){
    Json::Value root;
    std::string Op = ":=";
    root["name"] = "AssignExprAST "+Op;
    root["children"].append(LHS->print());
    root["children"].append(RHS->print());
    return root;
}

Json::Value BinaryExprAST::print(){
    Json::Value root;
    root["name"] = "BinaryExprAST "+Op;
    root["children"].append(LHS->print());
    root["children"].append(RHS->print());
    return root;
}

Json::Value CallExprAST::print(){
    Json::Value root;
    root["name"] = "CallExprAST: "+Callee;
    for (int i=Args.size()-1;i>=0;i--){
        root["children"].append(Args[i]->print());
    }
    return root;
}

Json::Value PrototypeAST::print(){
    Json::Value root;
    root["name"] = "PrototypeAST: "+Name;
    root["children"].append(retType->print());
    for (int i=Args.size()-1;i>=0;i--){
        root["children"].append(Args[i]->print());
    }
    return root;
}

Json::Value BodyAST::print(){
    Json::Value root;
    root["name"] = "BodyAST";
    for (int i=DefList.size()-1;i>=0;i--){
        root["children"].append(DefList[i]->print());
    }
    for (int i=StmtList.size()-1;i>=0;i--){
        root["children"].append(StmtList[i]->print());
    }
    root["children"].append(ReturnExpr->print());
    return root;
}

Json::Value FunctionAST::print(){
    Json::Value root;
    root["name"] = "FunctionAST";
    root["children"].append(Proto->print());
    root["children"].append(Body->print());
    return root;
}

Json::Value ProgramAST::print(){
    Json::Value root;
    root["name"] = "Program";
    for (int i=ElementList.size()-1;i>=0;i--){
        root["children"].append(ElementList[i]->print());
    }
    return root;
}

Json::Value StructAST::print(){
    Json::Value root;
    root["name"] = "StructAST:"+Name;
    for(int i = MemberNames.size()-1;i>=0;i--){
        root["children"].append(MemberNames[i]);
    }
    return root;
}

Json::Value StructEleAST::print() {
    Json::Value root;
    root["name"] = "StructEleAST:"+Name+" "+eleName;
    return root;
}