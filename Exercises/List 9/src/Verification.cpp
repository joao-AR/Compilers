#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "./h/Automaton.h"

bool isNum(char input){
    if(input == '0' || input == '1' || input == '2' ||  input == '3' ||input == '4'  || input == '5' || input == '6' ||  input == '7' || input == '8' || input == '9' ){
        return true;
    }    
    return false;
}

bool isLetterAccepted(char c){
    char acceptedLetters[] = {'d','e','f','g','h','i','t','n','l','s','b','p','r'}; 
    bool isAceita = std::find(std::begin(acceptedLetters), std::end(acceptedLetters), c) != std::end(acceptedLetters);
    return isAceita;
}

bool isCharAccepted(char c){
    if(c == '+'|| c == '-' || isNum(c)|| isLetterAccepted(c)){
        return true;
    }else{
        return false;
    }
}

void checkWordAccepted(std::string word,int automaton [][ALPHABET_LENGTH]){
    int finalStates[] = {18,19,20,21,22,23,24,25,26,27,28};

    int wordSize = word.size();
    int posi = 0;
    
    std::string auxOutput = "";
    std::string output = "";

    int inputColumn;
    int currentState = 1;
    int lastFinal = 0;

    bool isFinalState;
    bool newWord = true;
    
    while(posi <= wordSize){
        if(isCharAccepted(word[posi])){
            //std::cout << word[posi] << " << c \n";
            inputColumn = getInputColumn(word[posi]);
            currentState = getNewCurrentState(currentState,inputColumn,automaton);
            
            isFinalState = std::find(std::begin(finalStates), std::end(finalStates), currentState) != std::end(finalStates);
            lastFinal = isFinalState ? currentState : lastFinal;
            
            auxOutput = newWord ? auxOutput + word[posi] : auxOutput;

            if(currentState == 0 && lastFinal != 0){
                printOutput(output,lastFinal);
                resetStates(auxOutput,output,currentState,lastFinal,newWord,word[posi],0);
                
            }else if(currentState == 0 && lastFinal == 0){
                std::cout << "ERRO\n";
                resetStates(auxOutput,output,currentState,lastFinal,newWord,word[posi],1);
                
            }else{
                output = auxOutput;
                newWord = true;
                posi++;
            }
            
        }else{
            if(posi == wordSize){ 
                currentState = 0 ;
                if(currentState == 0 && lastFinal != 0){
                    printOutput(output,lastFinal);
                    break;
                }
                
            }else{
                std::cout << "ERRO\n";
                newWord = true;
                output = auxOutput;
                auxOutput = "";  
            }
            posi++;
        }
        
    }
}