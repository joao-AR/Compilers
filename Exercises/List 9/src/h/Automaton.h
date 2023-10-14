#include <iostream>


#ifndef Auto
#define Auto

    #define INITIAL_STATE = 1
    #define ALPHABET_LENGTH 29
    void lexAnalyser(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine);
    std::string getWord(std::string inputStr,int &posiString, int inputSize);
    int getInputColumn(char c);
    int getNewCurrentState(int stateLine,int inputColumn,int automaton [][ALPHABET_LENGTH]);
    void resetStates(std::string &auxOut,std::string &output,int &currentState,int &lastFinal,bool &newWord,char c ,int resetType);
    void printToken (int lastFinal);
    void printOutput(std::string output,int lastFinal);
    
#endif