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
    char acceptedLetters[] = {'A','a','B','b','C','c','D','d','E','e','F','f','G','g','H','h','I','i','J','j','K','k','L','l','M','m','N','n','O','o','P','p','Q','q','R','r','S','s','T','t','U','u','V','v','W','w','X','x','Y','y','Z','z'}; 
    bool isAceita = std::find(std::begin(acceptedLetters), std::end(acceptedLetters), c) != std::end(acceptedLetters);
    return isAceita;
}

bool isCharAccepted(char c){
    if(c== '+' || c== '-' || c== '*' || c== '/' || c== ';' || c== ',' || c== ':' || c== '.' || c== '[' || c== ']' || c== '(' || c== ')' || c== '=' || c== '<' || c== '>' ||isNum(c)|| isLetterAccepted(c) ){
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
    int finalStates[] = {6,18,26,28,43,44,46,53,56,60,63,66,71,76,81,87,90,95,100,103,105,109,112,123,126,130,131,134,137,146,154,157};

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
            inputColumn = getInputColumn(word[posi]);
            currentState = getNewCurrentState(currentState,inputColumn,automaton);

            isFinalState = std::find(std::begin(finalStates), std::end(finalStates), currentState) != std::end(finalStates);
            lastFinal = isFinalState ? currentState : lastFinal;
            
            auxOutput = newWord ? auxOutput + word[posi] : auxOutput;
            //printAll(word[posi], inputColumn,currentState,lastFinal,output,isCharAccepted(word[posi]));

            if(currentState == 0 && lastFinal != 0){
                //std::cout << "Entrou currentState == 0 && lastFinal != 0\n";
                printOutput(output,lastFinal);
                resetStates(auxOutput,output,currentState,lastFinal,newWord,word[posi],0);
                wordAccepted = true;
            }else if(currentState == 0 && lastFinal == 0){
                std::cout << "ERRO currentState == 0 && lastFinal == 0 \n";
                wordAccepted = false;
                exit(1);
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
                    printOutput(output,lastFinal);
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

