#include <iostream>


#ifndef Auto
#define Auto

    #define INITIAL_STATE = 1
    #define ALPHABET_LENGTH 53

    std::string getWord(std::string inputStr,int &posiString, int inputSize);
    int getInputColumn(char c);
    int getNewCurrentState(int stateLine,int inputColumn,int automaton [][ALPHABET_LENGTH]);
    void resetStates(std::string &auxOut,std::string &output,int &currentState,int &lastFinal,bool &newWord,char c ,int resetType);
    std::string getToken (int lastFinal);
    void printOutput(std::string output,int lastFinal);
    
#endif