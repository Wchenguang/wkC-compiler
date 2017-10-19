#include <cstdio>

#include "Lexer.h"
#include "CDEFINE.h"

#include "Error.h"
#include "FA.h"

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
Token *Lexer::directInsert(const string &str, TOKENTYPE type){
    Token *token = new Token(str, type);
    int key = hashVal(str);
    hashMap[key].push_back(token);
    return token;
}

//默认插入，先检查是否存在再直接插入或直接返回
Token *Lexer::defaultInsert(const string &str, TOKENTYPE type){
    Token *token = isTokenExist(str);
    if(token == NULL){
        token = directInsert(str, type);
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
    directInsert("void", TkVoid);
    directInsert("char", TkChar);
    directInsert("int", TkInt);
    //directInsert("float", TkFloat);
    directInsert("sizeof", TkSizeof);
    directInsert("static", TkStatic);
    directInsert("const", TkConst);
    directInsert("return", TkReturn);
    directInsert("continue", TkContinue);
    directInsert("break", TkBreak);
    directInsert("if", TkIf);
    directInsert("else", TkElse);
    directInsert("while", TkWhile);
    directInsert("\'", TkSingleQuote);
    directInsert("\"", TkDoubleQuote);
    directInsert(";", TkSemicolon);
    directInsert(">", TkLarger);
    directInsert("<", TkSmaller);
    directInsert("==", TkEqual);
    directInsert("!=", TkNotEqual);
    directInsert("+", TkPlus);
    directInsert("-", TkMinus);
    directInsert("*", TkMulti);
    directInsert("/", TkDivide);
    directInsert("%", TkMod);
    //directInsert(".", TkDot);
    directInsert(",", TkComma);
    directInsert("=", TkAssign);
    directInsert("(", TkLeftBracket);
    directInsert(")", TkRightBracket);
    directInsert("{", TkLeftBrace);
    directInsert("}", TkRightBrace);
}

//判断是否文件尾部并且读取ch
bool Lexer::getCh(char &ch){
    if(file.eof())
        return false;
    ch = file.get();
    return true;
}

//开始词法分析 融合了预处理
void Lexer::analyze(){
    file.open(filePath.c_str(), std::fstream::in);

    if(!file)
        return;
    
    char        ch = file.get();
    TOKENTYPE   destTokenType;
    
    while(!file.eof()){
        string      destStr;
        
        //跳过空白,将ch置为第一个非空符
        FA::skipSpace(ch, file, currentLine);
        if(file.eof())
            break;
        
        //根据ch进入相应自动机
        //引用传递 destStr 即为解析结果
        //对于简单符号的自动机将直接在此写成
        if(FA::isLetter(ch)){
            FA::getLetters(ch, file, destStr);
            //以标识符尝试插入，若是关键字则type无效
            destTokenType = TkId;
            
        }else if(FA::is0to9(ch)){
            FA::getNums(ch, file, destStr);
            destTokenType = TkNum;
            
        }else if(ch == '\''){
            FA::getChar(ch, file, destStr, *this);
            destTokenType = TkSChar;
            
        }else if(ch == '\"'){
            FA::getString(ch, file, destStr, *this);
            destTokenType = TkStr;
            
        }else if(ch == ';'){
            destStr.push_back(ch);
            destTokenType = TkSemicolon;
            if(!getCh(ch))
                continue;
            
        }else if(ch == '>'){
            destStr.push_back(ch);
            destTokenType = TkLarger;
            if(!getCh(ch))
                continue;
            
        }else if(ch == '<'){
            destStr.push_back(ch);
            destTokenType = TkSmaller;
            if(!getCh(ch))
                continue;
            
        }else if(ch == '='){
            destStr.push_back(ch);
            if(!getCh(ch))
                continue;
            if(ch == '='){
                destStr.push_back(ch);
                destTokenType = TkEqual;
                if(!getCh(ch))
                    continue;
            }else{
                destTokenType = TkAssign;
            }
        }else if(ch == '!'){
            destStr.push_back(ch);
            if(!getCh(ch))
                continue;
            if(ch != '=')
                Error::ErrNotEqual(currentLine);
            destStr.push_back(ch);
            if(!getCh(ch))
                continue;
            
        }else if(ch == '+'){
            destStr.push_back(ch);
            destTokenType = TkPlus;
            if(!getCh(ch))
                continue;
            
        }else if(ch == '-'){
            destStr.push_back(ch);
            destTokenType = TkMinus;
            if(!getCh(ch))
                continue;
            
        }else if(ch == '*'){
            destStr.push_back(ch);
            destTokenType = TkMulti;
            if(!getCh(ch))
                continue;
            
        }else if(ch == '/'){
            destStr.push_back(ch);
            destTokenType = TkDivide;
            if(!getCh(ch))
                continue;
            
        }else if(ch == '%'){
            destStr.push_back(ch);
            destTokenType = TkMod;
            if(!getCh(ch))
                continue;
            
        }/*else if(ch == '.'){
            destStr.push_back(ch);
            destTokenType = TkDot;
            if(!getCh(ch))
                continue;
            
        }*/else if(ch == ','){
            destStr.push_back(ch);
            destTokenType = TkComma;
            if(!getCh(ch))
                continue;

        }else if(ch == '('){
            destStr.push_back(ch);
            destTokenType = TkLeftBracket;
            if(!getCh(ch))
                continue;
            
        }else if(ch == ')'){
            destStr.push_back(ch);
            destTokenType = TkRightBracket;
            if(!getCh(ch))
                continue;
            
        }else if(ch == '{'){
            destStr.push_back(ch);
            destTokenType = TkLeftBrace;
            if(!getCh(ch))
                continue;
            
        }else if(ch == '}'){
            destStr.push_back(ch);
            destTokenType = TkRightBrace;
            if(!getCh(ch))
                continue;
            
        }else{
            Error::notKnownChar(currentLine, ch);
        }
        
        //将解析出的字符串以默认方法插入哈希表，并添加至链表尾部
        tokenList.push_back(defaultInsert(destStr, destTokenType));
        
    }
    
    file.close();
    
}

//文件路径初始化，暂时只能绝对路径 mac？
Lexer::Lexer(const char *path){
    index = 0;
    currentLine = 1;
    filePath.assign(path);
    initKeyWord();
    analyze();
}

//顺序获取单词 等待完成
Token *Lexer::getToken(){
    if(index < tokenList.size())
        return tokenList[index++];
    return NULL;
}

//单词表是否到尽头
bool Lexer::eof(){
    return index >= tokenList.size();
}

/*******************************************/
//用于测试
//通过tokenType获取类型并输出至控制台
void Lexer::getTypeStr(TOKENTYPE tokentype){
    string res("");
    if(tokentype >= TkVoid && tokentype <= TkWhile){
        res.assign("keyWord");
    }else if(tokentype >= TkSingleQuote && tokentype <= TkRightBrace){
        res.assign("separator");
    }else if(tokentype == TkId){
        res.assign("identifier");
    }else if(tokentype == TkNum){
        res.assign("number");
    }else if(tokentype == TkSChar){
        res.assign("charavter");
    }else if(tokentype == TkStr){
        res.assign("string");
    }
    printf("%- 20s", res.c_str());
}
