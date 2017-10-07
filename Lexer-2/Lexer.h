#ifndef Lexer_h
#define Lexer_h

#include <vector>
#include <iostream>
#include <fstream>

#include "Token.h"
#include "FA.h"
#include "CDEFINE.h"

using namespace std;

class Lexer{
public:
    static const int    HASHSIZE = 1024;    //哈希表最大容量
    vector<Token*>      hashMap[HASHSIZE];  //哈希表
    vector<Token*>      tokenList;          //符号列表
    
    string              filePath;           //文件路径
    fstream             file;               //文件流
    
    int                 index;              //getToken 的指针位置
    
    //字符串哈希
    int hashVal(const string &str);
    
    //直接插入哈希表以及列表
    Token *directInsert(const string &str, TOKENTYPE type);
    
    //默认插入，先检查是否存在再直接插入或直接返回
    Token *defaultInsert(const string &str, TOKENTYPE type);
    
    //查看单词是否存在
    Token *isTokenExist(const string &str);
    
    //加入关键字
    void initKeyWord();
    
    //开始词法分析 融合了预处理
    void analyze();
    
    //判断是否文件尾部并且读取ch
    bool getCh(char &ch);
    
public:
    
    //文件路径初始化，暂时只能绝对路径 mac？
    Lexer(const char *path);
    
    //顺序获取单词 等待完成
    Token *getToken(){
        if(index < tokenList.size())
            return tokenList[index++];
        return NULL;
    }
    
    //单词表是否到尽头
    bool eof(){
        return index >= tokenList.size();
    }
    
};

#endif
