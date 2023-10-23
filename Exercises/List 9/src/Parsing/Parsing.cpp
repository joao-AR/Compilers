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

// IF = 19
// THEN = 20
// ELSE = 21
// END = 22
// BEGIN = 23
// PRINT=24
// SEMI=25
// EQ=26
// NUM=27
// int getToken(){

// }

void error(){
    std::cout << "Error de parsing\n";
}
int getToken(std::vector<int> lineTokens,int &posi){
    posi++;
    return lineTokens[posi];
}
int advance(std::vector<int>  lineTokens,int &posiLineTokens) {
    int token = getToken(lineTokens,posiLineTokens);
    return token;
}

void eat(int expetedToken , int &inputToken,std::vector<int> lineTokens,int &posiLineTokens) {
    std::cout << "\n==============EAT==============\n";
    std::cout << " \n expetedToken = " << expetedToken << " inputToken = " <<  inputToken << "\n";

    if (expetedToken == inputToken){
        inputToken = advance(lineTokens,posiLineTokens);
    } else{
        error();
    }
    std::cout << "\n==============FIM==============\n";

}
void E(int &inputToken, std::vector<int> lineTokens,int &posi);

void S(int &token, std::vector<int> lineTokens,int &posi){
    std::cout <<  "===============S=============== \n";
    switch(token) {
        //case IF: eat(IF); E(); eat(THEN); S(); eat(ELSE); S(); break;
        case 19: 
            //eat(IF)
            eat(19,token,lineTokens, posi); 
            //E()
            //std::cout << "| posi> " << posi;
            E(token,lineTokens, posi);

            //eat(THEN)
            //std::cout << "| posi> " << posi;
            eat(20,token,lineTokens, posi); 
            //S()
            S(token,lineTokens, posi); 

            //eat(ELSE)
            eat(21,token,lineTokens, posi);
            std::cout << "token4: " << token << "\n";

            //S()
            S(token,lineTokens, posi);
            std::cout << "token5: " << token << "\n";
 
        break;
        //case BEGIN
        // case 23: eat(23); S(); L(); break;
        // // case PRINT 
        case 24: 
        eat(24,token,lineTokens, posi); 
        std::cout << "token6: " << token << "\n";
        E(token,lineTokens, posi); 
        std::cout << "token7: " << token << "\n";

        break;
        default: error();
        
    }
    std::cout <<  "==============FS===============\n";
}
// void L(int token){
//     switch(token) {
//         case END: eat(END); break;
//         case SEMI: eat(SEMI); S(); L(); break;
//         default: error(); 
//     }
// }
void E(int &inputToken, std::vector<int> lineTokens,int &posi){ 
    std::cout <<  "===============E=============== \n";
    //std::cout << "| posiE1> " << posi;
    // NUM=27
    eat(27,inputToken,lineTokens,posi);
    std::cout << "token8: " << inputToken << "\n";
    //std::cout << "| posiE2> " << posi;
    // EQ=26 
    eat(26,inputToken,lineTokens,posi);
    std::cout << "token9: " << inputToken << "\n";

    std::cout << "| posiE3> " << posi;
    // NUM=27 
    eat(27,inputToken,lineTokens,posi);
    std::cout << "token10: " << inputToken << "\n";
    std::cout <<  "==============FE===============\n";

    //std::cout << " posiE4> " << posi << "\n";
}

void parsing(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine){

    size_t inputStrSize = inputString.size();
    std::string word = "";
    bool wordAccepted = false;
    int posiString = 0;
    int posiLineTokens;
    std::vector<int> lineTokens;

    while(posiString <= inputStrSize){
        word = getWord(inputString,posiString,inputStrSize);
        getLineTokens(word,automaton,lineTokens);
        posiString++;
    }

    S(lineTokens[0],lineTokens,posiLineTokens);
    // std::cout << "\n";
    // for (int i = 0; i < lineTokens.size(); i++) {
    //     std::cout << lineTokens[i] << " ";
    // }
    // std::cout << "\n";
}



