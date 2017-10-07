#ifndef FA_h
#define FA_h

#include <iostream>
#include <fstream>

#include "CDEFINE.h"
#include "Token.h"

using namespace std;

//FA：自动机
namespace FA {
    
    //判断是否是空白
    bool isSpace(char ch);
    //判断是否是0-9数字
    bool is0to9(char c);
    //判断是否是1-9数字
    bool is1to9(char c);
    //判断是否是a-z,A-Z,_
    bool isLetter(char c);
    
    
    //预处理跳过空白自动机
    void skipSpace(char &ch, fstream &file);
    
    
}

#endif /* FA_h */
