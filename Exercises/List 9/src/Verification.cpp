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
    if(c == '+'|| c == '-' ||c == '=' ||c == ';' || isNum(c)|| isLetterAccepted(c)){
        return true;
    }else{
        return false;
    }
}

void printAll(char word, int inputColumn,int currentState ,int lastFinal ,std::string output = "",bool char_acepted = false){
    std::cout << "=======Debug======= \n";
    std::cout << "word: " << word << "\n";
    //if(inputColumn >= 0){
        std::cout << "inputColumn: " << inputColumn << "\n";
   // }else if(currentState >= 0){
        std::cout << "currentState: " << currentState << "\n";
    //}else if(lastFinal >= 0){
        std::cout << "lastFinal: " << lastFinal << "\n";
    //}else if(output != ""){
        std::cout << "output: " << output << "\n";
    //}
    std::cout << "char_acepted: " << char_acepted << "\n";
    std::cout << "=======Fim======= \n\n";
}

bool checkWordAccepted(std::string word,int automaton [][ALPHABET_LENGTH]){
    bool wordAccepted = false;
    int finalStates[] = {19,20,21,22,23,24,25,26,27,28};

    int wordSize = word.size();
    int posi = 0;
    
    std::string auxOutput = "";
    std::string output = "";

    int inputColumn;
    int currentState = 1;
    int lastFinal = 0;
    
    bool isFinalState;
    bool newWord = true;
    //std::cout << "wordSize: " << wordSize << "\n"; 
    while(posi <= wordSize){
        //std::cout << "posi: " << posi << "\n";
        if(isCharAccepted(word[posi])){
            inputColumn = getInputColumn(word[posi]);
            currentState = getNewCurrentState(currentState,inputColumn,automaton);
            
            isFinalState = std::find(std::begin(finalStates), std::end(finalStates), currentState) != std::end(finalStates);
            lastFinal = isFinalState ? currentState : lastFinal;
            
            auxOutput = newWord ? auxOutput + word[posi] : auxOutput;
            //printAll(word[posi], inputColumn,currentState,lastFinal,output,isCharAccepted(word[posi]));

            if(currentState == 0 && lastFinal != 0){
                //std::cout << "Entrou currentState == 0 && lastFinal != 0\n";
                // printOutput(output,lastFinal);
                resetStates(auxOutput,output,currentState,lastFinal,newWord,word[posi],0);
                wordAccepted = true;
            }else if(currentState == 0 && lastFinal == 0){
                std::cout << "ERRO currentState == 0 && lastFinal == 0 \n";
                wordAccepted = false;
                resetStates(auxOutput,output,currentState,lastFinal,newWord,word[posi],1);
                
            }else{
                //std::cout << "Entrou Else \n";
                output = auxOutput;
                newWord = true;
                posi++;
            }
            
        }else{
            //std::cout << "char não aceito: " << word[posi] << "\n";
            if(posi == wordSize){ 
                currentState = 0 ;
                if(currentState == 0 && lastFinal != 0){
                    // printOutput(output,lastFinal);
                    wordAccepted = true;
                    break;
                }
                
            }else{
                //std::cout << "ERRO posi\n";
                newWord = true;
                output = auxOutput;
                auxOutput = "";  
                wordAccepted = false;
            }
            posi++;
        }
        //std::cout << output << "\n";
    }

    return wordAccepted;
}

