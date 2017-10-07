#include <iostream>
#include <vector>

#include <cstdio>

#include "Lexer.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    
    Lexer l("//Users//wk1997//Documents//a.c");
    
    
    while (!l.eof()) {
        Token *token = l.getToken();
        printf("%d ", token);
        cout<<token->c_str()<<endl;
    }
    
    return 0;
}
