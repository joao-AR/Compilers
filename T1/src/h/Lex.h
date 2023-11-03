#include "./Automaton.h"

#ifndef Lex
#define Lex

    bool lexAnalyser(std::string inputString, bool haveNextLine,bool &commentSearch,bool &lineComment,int &linePosi,int &columnPosi);

#endif