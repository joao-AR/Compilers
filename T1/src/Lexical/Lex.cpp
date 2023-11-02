#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "../h/Verification.h"
#include "../h/Automaton.h"

bool lexAnalyser(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine,bool &commentSearch,bool &lineComment,int &linePosi,int &columnPosi){
    size_t inputStrSize = inputString.size();
    std::string word = "";
    int posiString = 0;
    bool wordAccepted = false;
    int whiteSapces = 0;
    while(posiString <= inputStrSize){
        word = getWord(inputString,posiString,inputStrSize,columnPosi,whiteSapces);
        if(word != ""){
            //std::cout << "\n WORD ->" << word << "<-\n";
            wordAccepted = checkWordAccepted(word,automaton,commentSearch,lineComment,linePosi,columnPosi,whiteSapces);
            if(!wordAccepted){return false;}
        }
        posiString++;// pular o espaço entre as palavras
    }
    return true;
}