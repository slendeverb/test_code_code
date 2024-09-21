#include "header.h"

class Expression{
public:
    virtual int interpreter(std::map<char,int>& var)=0;
    virtual ~Expression(){}
};

class VarExpression:public Expression{
public:
    VarExpression(const char& key):key{key}{}
    virtual int interpreter(std::map<char,int>& var) override{
        return var[key];
    }
private:
    char key;
};

class SymbolExpression:public Expression{
public:
    SymbolExpression(Expression* left, Expression* right):left{left},right{right}{}
    virtual ~SymbolExpression(){
        if(left!=nullptr){
            delete left;
        }
        if(right!=nullptr){
            delete right;
        }
    }
protected:
    Expression* left;
    Expression* right;
};

class AddExpression:public SymbolExpression{
public:
    AddExpression(Expression* left,Expression* right):SymbolExpression(left,right){}
    virtual int interpreter(std::map<char,int>& var) override{
        return left->interpreter(var)+right->interpreter(var);
    }
};

class SubExpression:public SymbolExpression{
public:
    SubExpression(Expression* left, Expression* right):SymbolExpression(left,right){}
    virtual int interpreter(std::map<char,int>& var) override{
        return left->interpreter(var)-right->interpreter(var);
    }
};

Expression* analyse(std::string& expStr){
    std::stack<Expression*> expStack;
    Expression* left=nullptr;
    Expression* right=nullptr;
    for(int i=0;i<expStr.size();++i){
        switch(expStr[i]){
            case '+':
                left=expStack.top();
                right=new VarExpression(expStr[++i]);
                expStack.push(new AddExpression(left,right));
                break;
            case '-':
                left=expStack.top();
                right=new VarExpression(expStr[++i]);
                expStack.push(new SubExpression(left,right));
                break;
            default:
                expStack.push(new VarExpression(expStr[i]));
        }
    }
    Expression* expression=expStack.top();
    return expression;
}

void release(Expression* expression){
    if(expression!=nullptr){
        delete expression;
        expression=nullptr;
    }
}

int main(int argc, char** argv) {
    std::string expStr="a+b-c+d";
    std::map<char,int> var{{'a',5},{'b',2},{'c',1},{'d',6}};
    Expression* expression=analyse(expStr);
    int res=expression->interpreter(var);
    std::println("{}",res);
    release(expression);
}