#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "../h/Verification.h"
#include "../h/Automaton.h"

bool lexAnalyser(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine){
    size_t inputStrSize = inputString.size();
    std::string word = "";
    int posiString = 0;
    bool wordAccepted = false;
    
    while(posiString <= inputStrSize){
        word = getWord(inputString,posiString,inputStrSize);
        if(word != ""){
            std::cout << "\nWORD ->" << word << "<-\n";
            wordAccepted = checkWordAccepted(word,automaton);
            if(!wordAccepted){return false;}
        }
        posiString++;
    }
    return true;
}