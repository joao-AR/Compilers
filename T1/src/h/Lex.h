#include "./Automaton.h"

#ifndef Lex
#define Lex
bool lexAnalyser(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine,bool &commentSearch,bool &lineComment,int &linePosi,int &columnPosi);
#endif