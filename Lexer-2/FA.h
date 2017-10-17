#ifndef FA_h
#define FA_h

#include <iostream>
#include <fstream>

#include "CDEFINE.h"
#include "Token.h"
#include "Lexer.h"

using namespace std;

//FA：自动机
namespace FA {


    //判断是否是空白
    bool isSpace(char ch, int &currentLine);
    //判断是否是0-9数字
    bool is0to9(char c);
    //判断是否是1-9数字
    bool is1to9(char c);
    //判断是否是a-z,A-Z,_
    bool isLetter(char c);
    
    
    //预处理跳过空白自动机
    void skipSpace(char &ch, fstream &file, int &currentLine);
    
    //识别标识符以及关键字自动机
    void getLetters(char &ch, fstream &file, string &destStr);
    
    //识别可以0打头的纯数字自动机
    void getNums(char &ch, fstream &file, string &destStr);
    
    //识别单引号括起的单个字符
    void getChar(char &ch, fstream &file, string &destStr, Lexer &lexer);
    
    //识别双引号括起的字符串
    void getString(char &ch, fstream &file, string &destStr, Lexer &lexer);
}

#endif /* FA_h */
