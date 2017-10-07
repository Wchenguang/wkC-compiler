#ifndef Error_h
#define Error_h

#include <iostream>
#include "CDEFINE.h"

using namespace std;

class Error{

public:
    static void strTooLong(){
        cout<<"string too long max: "<<MAXSTRLENGTH<<endl;
        exit(-1);
    }
    
    static void charNoContent(){
        cout<<"expected statement"<<endl;
        exit(-1);
    }
    
    static void charNotMatch(){
        cout<<"expected \'"<<endl;
        exit(-1);
    }
    
    static void strNotMatch(){
        cout<<"expected \""<<endl;
        exit(-1);
    }
    
    static void ErrNotEqual(){
        cout<<"expected = after !"<<endl;
        exit(-1);
    }
    
    static void notKnownChar(){
        cout<<"not known char"<<endl;
        exit(-1);
    }
};

#endif
