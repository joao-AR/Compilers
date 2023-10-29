#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include <unordered_map>

#include "./h/Verification.h"
#include "./h/Automaton.h"

void ignoreSpaces(std::string inputStr,int &posiString, int inputSize){
    if(inputStr[posiString] == ' '){
        while (inputStr[posiString] == ' '){
            //std::cout << "CHAR -> " << inputStr[posiString] << "<- \n";
            posiString++;
        }
    }
}
std::string getWord(std::string inputStr,int &posiString, int inputSize){
    char c;
    std::string word;
    ignoreSpaces(inputStr,posiString,inputSize); 
    
    while (inputStr[posiString] != ' ' && posiString < inputSize){
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
        {'+',0},
        {'-',1},
        {'*',2},
        {'/',3},
        {'0',4},
        {'1',5},
        {'2',6},
        {'3',7},
        {'4',8},
        {'5',9},
        {'6',10},
        {'7',11},
        {'8',12},
        {'9',13},
        {'a',14},
        {'b',15},
        {'c',16},
        {'d',17},
        {'e',18},
        {'f',19},
        {'g',20},
        {'h',21},
        {'i',22},
        {'j',23},
        {'k',24},
        {'l',25},
        {'m',26},
        {'n',27},
        {'o',28},
        {'p',29},
        {'q',30},
        {'r',31},
        {'s',32},
        {'t',33},
        {'u',34},
        {'v',35},
        {'w',36},
        {'x',37},
        {'y',38},
        {'z',39},
        {'A',14},
        {'B',15},
        {'C',16},
        {'D',17},
        {'E',18},
        {'F',19},
        {'G',20},
        {'H',21},
        {'I',22},
        {'J',23},
        {'K',24},
        {'L',25},
        {'M',26},
        {'N',27},
        {'O',28},
        {'P',29},
        {'Q',30},
        {'R',31},
        {'S',32},
        {'T',33},
        {'U',34},
        {'V',35},
        {'W',36},
        {'X',37},
        {'Y',38},
        {'Z',39},
        {';',40},
        {',',41},
        {':',42},
        {'.',43},
        {'[',44},   
        {']',45},
        {'(',46}, 
        {')',47},
        {'=',48},
        {'<',49},
        {'>',50}
    };

    if (charInputColumn.find(c) != charInputColumn.end()) {
        return charInputColumn[c];
    }
    
    return 51; // Valor padrão se o caractere não for encontrado no mapa.
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
        {6,"E"},
        {18,"IDENTIFICADOR"},
        {26,"ALGORITIMO"},
        {28,"ATE"},
        {43,"CARACTERE"},
        {44,"DE"},
        {46,"DIV"},  
    };
    return lastFinalToken[lastFinal];
}

void printOutput(std::string output,int lastFinal){
    std::string str = getToken(lastFinal);
    std::cout << str; 
    // std::cout << "\n";
}   

