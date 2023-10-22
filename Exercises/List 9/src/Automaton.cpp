#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include <unordered_map>

#include "./h/Verification.h"
#include "./h/Automaton.h"

std::string getWord(std::string inputStr,int &posiString, int inputSize){
    char c;
    std::string word;
    while (inputStr[posiString  ] != ' '){
        c = inputStr[posiString];
        word = word + c;
        posiString++;
        if(posiString == inputSize){
            return word;
        }
    }
    return word;
}

int getNewCurrentState(int stateLine,int inputColumn,int automaton [][ALPHABET_LENGTH]){
    int newState;
    if(inputColumn == -1){
        std::cout << "ERRO inputColumn\n";
        return 0;
    }else{
        newState = automaton[stateLine][inputColumn];
    }
    return newState;
}

int getInputColumn(char c){

    std::unordered_map<char, int> charInputColumn = {
        {'+', 0},
        {'-', 1},
        {'=', 12},
        {';', 13},
        {'d', 14},
        {'e', 15},
        {'f', 16},
        {'g', 17},
        {'h', 18},
        {'i', 19},
        {'t', 20},
        {'n', 21},
        {'l', 22},
        {'s', 23},
        {'b', 24},
        {'p', 25},
        {'r', 26}
    };

    if (charInputColumn.find(c) != charInputColumn.end()) {
        return charInputColumn[c];
    }else if(isNum(c)){
        return 3;
    }
    
    return 28; // Valor padrão se o caractere não for encontrado no mapa.
}

void resetStates(std::string &auxOut,std::string &output,int &currentState,int &lastFinal,bool &newWord,char c ,int resetType){
    if(resetType == 0){
        auxOut = c ;
        output = "";
        currentState = 1;
        lastFinal = 0;
        newWord = false;
    }else if(resetType == 1){
        auxOut = c;
        output = "";
        currentState = 1;
        lastFinal = 0;
        newWord = false;
    }
}

std::string getToken (int lastFinal){

    std::unordered_map<int, std::string> lastFinalToken = {
        {19, "IF"},
        {20, "THEN"},
        {21, "ELSE"},
        {22, "END"},
        {23,"BEGIN"},
        {24,"PRINT"},
        {25,"SEMICOL"},
        {26,"EQ"},
        {27,"NUM"}
    };
    return lastFinalToken[lastFinal];
}

void printOutput(std::string output,int lastFinal){
    std::string str = getToken(lastFinal);
    std::cout << str; 
    std::cout << "\n";
}   

