#ifndef Token_h
#define Token_h

#include <string>

using namespace std;

class Token{
private:
    string  sourceStr;  //单词字符串
    int     StrType;    //字符串类型
public:
    Token(const string &str){
        sourceStr.assign(str);
    }
    
    bool operator==(const Token &token){
        return token.sourceStr == sourceStr;
    }
    
    bool operator==(const string &str){
        return str == sourceStr;
    }
    
};

#endif 
