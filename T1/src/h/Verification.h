#include <iostream>
#include "./Automaton.h"
#ifndef Veri
#define Veri

    bool isNum(char input);
    bool isWordAccepted(char c);
    bool isCharAccepted(char c);
    bool checkWordAccepted(std::string word,bool &commentSearch, bool &lineComment,int &linePosi,int &columnPosi, int whiteSpaces);
#endif