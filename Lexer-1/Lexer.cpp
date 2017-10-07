#include "Lexer.h"

//字符串哈希
int Lexer::hashVal(const string &str){
    unsigned long h=0;
    unsigned long x=0;
    for(string::const_iterator i = str.begin(); i != str.end(); ++i){
        h=(h<<4)+*i;
        if( (x=h & 0xF0000000L)!=0)
        {
            h^=(x>>24);
            h&=~x;
        }
    }
    return h % HASHSIZE;
}

//直接插入哈希表以及列表
Token *Lexer::directInsert(const string &str){
    Token *token = new Token(str);
    int key = hashVal(str);
    hashMap[key].push_back(token);
    return token;
}

//默认插入，先检查是否存在再直接插入或直接返回
Token *Lexer::defaultInsert(const string &str){
    Token *token = isTokenExist(str);
    if(token == NULL){
        token = directInsert(str);
    }
    return token;
}

//查看单词是否存在
Token *Lexer::isTokenExist(const string &str){
    int key = hashVal(str);
    vector<Token*> &v = hashMap[key];
    for(const auto &i : v){
        if(*i == str)
            return i;
    }
    return NULL;
}

//加入关键字
void Lexer::initKeyWord(){
    directInsert("void");
    directInsert("char");
    directInsert("int");
    directInsert("float");
    directInsert("enum");
    directInsert("sizeof");
    directInsert("static");
    directInsert("const");
    directInsert("return");
    directInsert("continue");
    directInsert("break");
    directInsert("if");
    directInsert("else");
    directInsert("for");
    directInsert("while");
    directInsert("\'");
    directInsert("\"");
    directInsert(",");
    directInsert(";");
    directInsert(">");
    directInsert(">=");
    directInsert("<");
    directInsert("<=");
    directInsert("==");
    directInsert("!=");
    directInsert("+");
    directInsert("-");
    directInsert("*");
    directInsert("/");
    directInsert("%");
    directInsert("&");
    directInsert("|");
    directInsert("!");
    directInsert("^");
    directInsert("&&");
    directInsert("||");
    directInsert("=");
    directInsert("(");
    directInsert(")");
    directInsert("{");
    directInsert("}");
    directInsert("->");
}

//开始词法分析 融合了预处理
void Lexer::analyze(){
    file.open(filePath.c_str(), std::fstream::in);
    
    if(!file)
        return;
    
    char ch = file.get();
    while(!file.eof()){
        FA::skipSpace(ch, file);
        
        ch = file.get();
    }
    
    file.close();
}

//文件路径初始化，暂时只能绝对路径 mac？
Lexer::Lexer(const char *path){
    filePath.assign(path);
    initKeyWord();
    analyze();
}
