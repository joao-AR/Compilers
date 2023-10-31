#include "./Automaton.h"
#include <vector>
#include <unordered_map>
#ifndef Par
#define Par
    void parsing(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine,int &linePosi,int &columnPosi);
    std::string getTokenName(int token);

    void getLineTokens(std::string word,int automaton [][ALPHABET_LENGTH],std::vector<int> &lineTokens);
    int getToken(std::vector<int> lineTokens,int &posi);

    int advance(std::vector<int>  lineTokens,int &posiLineTokens);
    void eat(int expetedToken , int &inputToken,std::vector<int> lineTokens,int &posiLineTokens);
    void error(std::string errMsg);
#endif