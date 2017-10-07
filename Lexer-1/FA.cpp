#include "FA.h"

#include <iostream>

using namespace std;

//判断是否是空白
bool FA::isSpace(char ch){
    if(ch == ' ')
        cout<<"空白"<<endl;
    if(ch == '\n')
        cout<<"换行"<<endl;
    if(ch == '\t')
        cout<<"tab"<<endl;
    if(ch == '\r')
        cout<<"ok"<<endl;
    if(ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')
        return true;
    cout<<ch<<endl;
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
void FA::skipSpace(char &ch, fstream &file){
    if(isSpace(ch) && !file.eof()){
        ch = file.get();
        skipSpace(ch, file);
    }
}


