#include <iostream>

#include "FA.h"
#include "Util.h"
#include "Error.h"

using namespace std;

//判断是否是空白
bool FA::isSpace(char ch, int &currentLine){
    /*if(ch == ' ')
        cout<<"空白"<<endl;
    if(ch == '\n')
        cout<<"换行"<<endl;
    if(ch == '\t')
        cout<<"tab"<<endl;
    if(ch == '\r')
        cout<<"ok"<<endl;*/
    if(ch == '\n')
        ++currentLine;
    if(ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\377')
        return true;
    //cout<<ch<<endl;
    return false;
}

//判断是否是0-9数字
bool FA::is0to9(char c){
    return c>='0' && c<='9';
}
//判断是否是1-9数字
bool FA::is1to9(char c){
    return c>='1' && c<='9';
}
//判断是否是a-z,A-Z,_
bool FA::isLetter(char c){
    return (c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_';
}

//预处理跳过空白自动机
void FA::skipSpace(char &ch, fstream &file, int &currentLine){
    if(isSpace(ch, currentLine) && !file.eof()){
        ch = file.get();
        skipSpace(ch, file, currentLine);
    }
}

//识别标识符以及关键字自动机
void FA::getLetters(char &ch, fstream &file, string &destStr){
    if(isLetter(ch)){
        destStr.push_back(ch);
        if(file.eof())
            return;
        ch = file.get();
        getLetters(ch, file, destStr);
    }else{
        return;
    }
}

//识别可以0打头的纯数字自动机
void FA::getNums(char &ch, fstream &file, string &destStr){
    if(is0to9(ch)){
        destStr.push_back(ch);
        if(file.eof())
            return;
        ch = file.get();
        getNums(ch, file, destStr);
    }else{
        return;
    }
}

//识别单引号括起的单个字符
void FA::getChar(char &ch, fstream &file, string &destStr, Lexer &lexer){
    destStr.push_back(ch);
    if(file.eof())
        Error::charNotMatch(lexer.getCurrentLine());
    ch = file.get();
    if(ch == '\'')
        Error::charNoContent(lexer.getCurrentLine());
    destStr.push_back(ch);
    if(file.eof())
        Error::charNotMatch(lexer.getCurrentLine());
    ch = file.get();
    if(ch != '\'')
        Error::charNotMatch(lexer.getCurrentLine());
    destStr.push_back(ch);
    if(!file.eof())
        ch = file.get();
}

//识别双引号括起的字符串
void FA::getString(char &ch, fstream &file, string &destStr, Lexer &lexer){
    destStr.push_back(ch);
    if(file.eof())
        Error::strNotMatch(lexer.getCurrentLine());
    ch = file.get();
    
    while(ch != '\"'){
        destStr.push_back(ch);
        if(file.eof())
            Error::strNotMatch(lexer.getCurrentLine());
        ch = file.get();
    }
    destStr.push_back(ch);
    if(!file.eof())
        ch = file.get();
}
