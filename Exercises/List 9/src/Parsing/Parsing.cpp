#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include <vector>
#include "../h/Automaton.h"

void getLineTokens(std::string word,int automaton [][ALPHABET_LENGTH],std::vector<int> &lineTokens){
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
        
        inputColumn = getInputColumn(word[posi]);
        currentState = getNewCurrentState(currentState,inputColumn,automaton);
        
        isFinalState = std::find(std::begin(finalStates), std::end(finalStates), currentState) != std::end(finalStates);
        lastFinal = isFinalState ? currentState : lastFinal;
        
        auxOutput = newWord ? auxOutput + word[posi] : auxOutput;
        //printAll(word[posi], inputColumn,currentState,lastFinal,output,isCharAccepted(word[posi]));

        if(currentState == 0 && lastFinal != 0){
            //std::cout << "Entrou currentState == 0 && lastFinal != 0\n";
            lineTokens.push_back(lastFinal);
            resetStates(auxOutput,output,currentState,lastFinal,newWord,word[posi],0);
        }else{
            //std::cout << "Entrou Else \n";
            output = auxOutput;
            newWord = true;
            posi++;
        }
    }

}



// S → if E then S else S
// S → begin S L
// S → print E
// L → end
// L → ; S L
// E → num = num

// int getToken(){

// }
// int token = getToken();

// void advance() {token=getToken();}

// void eat(int t) {
//     if (token==t){
//         advance(); 
//     } else{
//         error();
//     }
// }

// void S(){
// switch(token) {
//     case IF: eat(IF); E(); eat(THEN); S(); eat(ELSE); S(); break;
//     case BEGIN: eat(BEGIN); S(); L(); break;
//     case PRINT: eat(PRINT); E(); break;
//     default: error(); 
//     }
// }
// void L(){
//     switch(token) {
//         case END: eat(END); break;
//         case SEMI: eat(SEMI); S(); L(); break;
//         default: error(); 
//     }
// }
// void E(){ 
//     eat(NUM); 
//     eat(EQ); 
//     eat(NUM); 
// }

void parsing(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine){

    size_t inputStrSize = inputString.size();
    std::string word = "";
    bool wordAccepted = false;
    int posiString = 0;
    std::vector<int> lineTokens;

    int IF=19, THEN=20, ELSE=21,END=22, BEGIN=23,  PRINT=24, SEMI=25,EQ=26, NUM=27 ;

    while(posiString <= inputStrSize){
        word = getWord(inputString,posiString,inputStrSize);
        getLineTokens(word,automaton,lineTokens);
        posiString++;
    }

    for (int i = 0; i < lineTokens.size(); i++) {
            std::cout << lineTokens[i] << " ";
        }
    std::cout << "\n";
}



