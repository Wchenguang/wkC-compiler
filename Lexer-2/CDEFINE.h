
#ifndef CDEFINE_h
#define CDEFINE_h

#define MAXSTRLENGTH 256

enum TOKENTYPE{
    TkVoid,         //void
    TkChar,         //char
    TkInt,          //int
    //TkFloat,        //float
    TkSizeof,       //sizeof
    TkStatic,       //static
    TkConst,        //const
    TkReturn,       //return
    TkContinue,     //continue
    TkBreak,        //break
    TkIf,           //if
    TkElse,         //else
    TkWhile,        //while
    TkSingleQuote,  //'
    TkDoubleQuote,  //"
    TkSemicolon,    //;
    TkLarger,       //>
    TkSmaller,      //<
    TkEqual,        //==
    TkNotEqual,     //!=
    TkPlus,         //+
    TkMinus,        //-
    TkMulti,        //*
    TkDivide,       // /
    TkMod,          //%
    //TkDot,          //.
    TkComma,        //,
    TkAssign,       //=
    TkLeftBracket,  //(
    TkRightBracket, //)
    TkLeftBrace,    //{
    TkRightBrace,   //}
    
    /**************************/
    TkId,           //标识符
    TkNum,          //纯数字 可以0开头
    TkSChar,        //单引号括起的字符
    TkStr           //双引号括起的字符串
};

#endif
