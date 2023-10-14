#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
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
        std::cout << "ERRO -1\n";
        return 0;
    }else{
        newState = automaton[stateLine][inputColumn];
    }
    return newState;
}

int getInputColumn(char c){
    if(c == '+'){
        return 0;
    }else if(c == '-'){
        return 1;
    }
    else if(isNum(c)){
        return 3;
    }else if(c == '='){
        return 13;
    }else if(c == ';'){
        return 14;
    }else if(c == 'd'){
        return 15;
    }else if( c == 'e'){
        return 16;
    }else if( c == 'f'){
    return 17;
    }else if( c == 'g'){
    return 18;
    }else if( c == 'h'){
    return 19;
    }else if( c == 'i'){
    return 20;
    }else if( c == 't'){
    return 21 ;
    }else if( c == 'n'){
    return 22;
    }else if( c == 'l'){
    return 23;
    }else if( c == 's'){
    return 24;
    }else if( c == 'b'){
    return 25;
    }else if( c == 'p'){
    return 26;
    }else if( c == 'r'){
    return 27 ;
    } 
    return 29;
}

void lexAnalyser(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine){
    int posiString = 0;
    size_t inputStrSize = inputString.size();
    char ultimoChar;
    std::string word = "";

    while(posiString <= inputStrSize){
        ultimoChar = inputString[posiString];
        word = getWord(inputString,posiString,inputStrSize);
        checkWordAccepted(word,automaton);
        posiString++;
    }
    
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

void printToken (int lastFinal){

    if(lastFinal ==  19){
    std::cout << "IF ";
    }else if(lastFinal == 20 ){
        std::cout << "THEN";
    }else if(lastFinal == 21 ){
        std::cout << "ELSE";
    }else if( lastFinal == 22){
        std::cout << "END";
    }else if( lastFinal == 23){
        std::cout << "BEGIN";
    }else if( lastFinal == 24){
        std::cout << "PRINT";
    }else if( lastFinal == 25){
        std::cout << "SEMICOL";
    }else if( lastFinal == 26){
        std::cout << "EQ";
    }else if( lastFinal == 27){
        std::cout << "NUM";
    }
}

void printOutput(std::string output,int lastFinal){
    printToken(lastFinal);
    std::cout << "\n";
}   

