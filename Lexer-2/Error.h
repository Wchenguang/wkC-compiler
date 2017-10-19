#ifndef Error_h
#define Error_h

#include <iostream>
#include "CDEFINE.h"

using namespace std;

class Error{

public:
    static void strTooLong(int currentLine){
        cout<<"Error line "<<currentLine<<" : ";
        cout<<"string too long max: "<<MAXSTRLENGTH<<endl;
        exit(-1);
    }
    
    static void charNoContent(int currentLine){
        cout<<"Error line "<<currentLine<<" : ";
        cout<<"expected statement"<<endl;
        exit(-1);
    }
    
    static void charNotMatch(int currentLine){
        cout<<"Error line "<<currentLine<<" : ";
        cout<<"expected \'"<<endl;
        exit(-1);
    }
    
    static void strNotMatch(int currentLine){
        cout<<"Error line "<<currentLine<<" : ";
        cout<<"expected \""<<endl;
        exit(-1);
    }
    
    static void ErrNotEqual(int currentLine){
        cout<<"Error line "<<currentLine<<" : ";
        cout<<"expected = after !"<<endl;
        exit(-1);
    }
    
    static void notKnownChar(int currentLine, char ch){
        cout<<"Error line "<<currentLine<<" : ";
        cout<<"not known char "<<ch<<endl;
        exit(-1);
    }
};

#endif
