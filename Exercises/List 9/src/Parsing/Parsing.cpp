#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "../h/Automaton.h"
#include "../h/Parsing.h"


int err = 0;
const int IF = 19;
const int THEN = 20;
const int ELSE = 21;
const int END = 22;
const int BEGIN = 23;
const int PRINT = 24;
const int SEMI = 25;
const int EQ = 26;
const int NUM = 27;

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
    if(err == 0 ){
        //std::cout << inputString << "\n";
        std::cout << "CADEITA ACEITA\n";
    }
    err = 0; // reset no erro para proxima linha
    // std::cout << "\n";
    // for (int i = 0; i < lineTokens.size(); i++) {
    //     std::cout << lineTokens[i] << " ";
    // }
    // std::cout << "\n";
}

std::string getTokenName(int token){
    std::unordered_map<int, std::string> numTokenName = {
        {19, "if"},
        {20, "then"},
        {21, "else"},
        {22, "end"},
        {23,"begin"},
        {24,"print"},
        {25,";"},
        {26,"="},
        {27,"num"}
    };
    return numTokenName[token];
}

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

    while(posi <= wordSize){        
        inputColumn = getInputColumn(word[posi]);
        currentState = getNewCurrentState(currentState,inputColumn,automaton);
        
        isFinalState = std::find(std::begin(finalStates), std::end(finalStates), currentState) != std::end(finalStates);
        lastFinal = isFinalState ? currentState : lastFinal;
        
        auxOutput = newWord ? auxOutput + word[posi] : auxOutput;

        if(currentState == 0 && lastFinal != 0){
            lineTokens.push_back(lastFinal);
            resetStates(auxOutput,output,currentState,lastFinal,newWord,word[posi],0);
        }else{
            output = auxOutput;
            newWord = true;
            posi++;
        }
    }

}

void error(std::string errMsg){
    if(err == 0){
        std::cout << errMsg <<"\n";
        err = 1;
    }
}

// Pega o proximo token no vetor
int getToken(std::vector<int> lineTokens,int &posi){
    posi++; // vai para a proxima posi do vetor
    return lineTokens[posi];
}

// Vai retornar o Proximo Token do vetor de tokens 
int advance(std::vector<int>  lineTokens,int &posiLineTokens) {
    int token = getToken(lineTokens,posiLineTokens);
    return token;
}

void eat(int expetedToken , int &inputToken,std::vector<int> lineTokens,int &posiLineTokens) {

    //std::cout << "\n==============EAT==============\n";
    //std::cout << " \n expetedToken = " << expetedToken << " inputToken = " <<  inputToken << "\n";

    // Se o token for o token que o programa estava esperando 
    if (expetedToken == inputToken){
        inputToken = advance(lineTokens,posiLineTokens);
    }else{ // Caso não for o token esperado vai se impressa uma msg de erro
        std::string recived = getTokenName(inputToken);
        std::string expected = getTokenName(expetedToken);
        std::string errMsg = "ERRO SINTATICO EM: " + recived + " ESPERADO: "+ expected;
        error(errMsg);
        return;
    }
    //std::cout << "\n==============FIM==============\n";

}


// S é o inicial
// S → if E then S else S
// S → begin S L
// S → print E
void S(int &token, std::vector<int> lineTokens,int &posi){
    //std::cout <<  "===============S=============== \n";
    switch(token) {
        case IF: 
            eat(IF,token,lineTokens, posi); 
            E(token,lineTokens, posi);
            eat(THEN,token,lineTokens, posi); 
            S(token,lineTokens, posi); 
            eat(ELSE,token,lineTokens, posi);
            S(token,lineTokens, posi);
        break;
        case BEGIN: 
            eat(BEGIN,token,lineTokens, posi); 
            S(token,lineTokens, posi);
            L(token,lineTokens, posi); 
            break;
        case PRINT: 
        eat(PRINT,token,lineTokens, posi); 
        E(token,lineTokens, posi); 
        break;
        default: 
            std::string recived = getTokenName(token);
            std::string errMsg = "ERRO SINTATICO EM: " + recived + " ESPERADO: if, begin, print";
            error(errMsg);         
    }
    //std::cout <<  "==============FS===============\n";
}

// L → end
// L → ; S L
void L(int &token, std::vector<int> lineTokens,int &posi){
    //std::cout <<  "===============L=============== \n";
    switch(token) {
        case END: 
            eat(END,token,lineTokens, posi); 
            break;
    
        case SEMI: 
            eat(SEMI,token,lineTokens, posi); 
            S(token,lineTokens, posi); 
            L(token,lineTokens, posi); 
            break;
        default: 
            std::string recived = getTokenName(token);
            std::string errMsg = "ERRO SINTATICO EM: " + recived + " ESPERADO: end, ;";
            error(errMsg); 
    }
    //std::cout <<  "===============FL=============== \n";

}

// E → num = num
void E(int &inputToken, std::vector<int> lineTokens,int &posi){ 
    //std::cout <<  "===============E=============== \n";
    eat(NUM,inputToken,lineTokens,posi);
    eat(EQ,inputToken,lineTokens,posi);
    eat(NUM,inputToken,lineTokens,posi);
    //std::cout <<  "==============FE===============\n";
}