#include <iostream>
#include <vector>

#ifndef Auto
#define Auto
    const int finalStates[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,26,28,31,32,33,34,35,43,44,46,53,56,57,60,63,64,66,71,76,81,87,90,95,100,101,103,104,105,106,109,112,123,126,130,131,134,137,146,154,157,158,159,160,161,162,163,164,165,166,167,170,171,172,173};
    extern std::vector<int> allTokens;
    extern std::vector<int> allLines;
    extern std::vector<int> allColumns;
    extern std::vector<std::string> allwords;

    #define INITIAL_STATE = 1
    #define ALPHABET_LENGTH 54

    std::string getWord(std::string inputStr,int &posiString, int inputSize,int &columnPosi,int &whiteSpaces);
    int getInputColumn(char c);
    int getNewCurrentState(int stateLine,int inputColumn,int automaton [][ALPHABET_LENGTH]);
    void resetStates(std::string &auxOut,std::string &output,int &currentState,int &lastFinal,bool &newWord,char c ,int resetType);
    std::string getTokenName (int lastFinal);
    void printOutput(std::string output,int lastFinal);
    
#endif