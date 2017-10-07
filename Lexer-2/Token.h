#ifndef Token_h
#define Token_h

#include <string>

#include "CDEFINE.h"

using namespace std;

class Token{
private:
    string          sourceStr;  //单词字符串
    TOKENTYPE       tokenType;    //字符串类型
public:
    Token(const string &str, TOKENTYPE type){
        sourceStr.assign(str);
        tokenType = type;
    }
    
    bool operator==(const Token &token){
        return token.sourceStr == sourceStr;
    }
    
    bool operator==(const string &str){
        return str == sourceStr;
    }
    
    const char *c_str(){
        return sourceStr.c_str();
    }
    
};

#endif 
