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
    if(c == ' '|| c == '+' || c == '-' || c == '*' || c == '/' || c == ';' || c == ',' || c == ':' || c == '.' || c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}'|| c == '=' || c == '<' || c == '>' ||c == '"'||isNum(c)|| isLetterAccepted(c) ){
        return true;
    }else{
        //std::cout << "ERRO CHAR NAO ACEITO";
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

void checkSingleLineComment(std::string word,int &posi,bool &lineComment,std::string output){
    if(word[posi] == '/' && word[posi+1] == '/' ){// Verrifica se vai ser um comentario de linha
        lineComment = true;
        int currentState = 0;
        int lastFinal = 172;
        //printOutput(output,lastFinal);
        
    }
}
void blockCommentHandler(std::string word,int &posi,std::string output,bool &commentSearch){
    int wordSize = word.size();
    while(posi <= wordSize){
        if(word[posi] != '}'){// Procurando final do commentario
            posi++;
        }else if(word[posi] == '}'){
            commentSearch = false;
            int lastFinal = 170;
            //printOutput(output,lastFinal);
            break;
        }
    } 
}

bool blockStringHandler(std::string word,int &posi,std::string output,bool &stringSearch, int type){
    int wordSize = word.size();
    if(type == 1){
        while(posi <= wordSize){
            if(word[posi] == '"'){
                stringSearch = false;
                //printOutput(output,173);
                return true;
            }
            posi++;
        }
    }else if(type == 2 ){
        if(word[posi] == '"' && word[wordSize-1] == '"' && wordSize > 1 ){
            stringSearch = false;
            //printOutput(output,173);
        }else{
            stringSearch = true;
        }
        return true;
    }
    return false;
}
bool stringSearch = false;
bool checkWordAccepted(std::string word,int automaton [][ALPHABET_LENGTH],bool &commentSearch, bool &lineComment,int &linePosi,int &columnPosi, int whiteSpaces){
    //std::cout<< "Aword > " << word << "\n";
    bool wordAccepted = false;

    int wordSize = word.size();
    int posi = 0;
    
    std::string auxOutput = "";
    std::string output = "";

    int inputColumn;
    int currentState = 1;
    int lastFinal = 0;
    
    bool isFinalState;
    bool newWord = true;
 
    checkSingleLineComment(word,posi,lineComment,output);
    if(lineComment){return true;}
    
    if(commentSearch){ // Se estivermos procurando um comentario de bloco
        blockCommentHandler(word,posi,output,commentSearch);
    }else if(stringSearch){
        bool resp = blockStringHandler(word,posi,output,stringSearch,1);
        if(resp){return true;}
    }

    if(commentSearch || lineComment || stringSearch){// Se estiver procurando comentario ainda aceita qualquer palavra OU comentario de linha
        return true;
    }

    while(posi <= wordSize){
        columnPosi++;
        if(isCharAccepted(word[posi])){
            inputColumn = getInputColumn(word[posi]);
            currentState = getNewCurrentState(currentState,inputColumn,automaton);

            isFinalState = std::find(std::begin(finalStates), std::end(finalStates), currentState) != std::end(finalStates);
            lastFinal = isFinalState ? currentState : lastFinal;
            
            if(word[posi] == '"' && !stringSearch){
                blockStringHandler(word,posi,output,stringSearch,2);
                return true;
            }

            if(word[posi] == '{'){
                commentSearch = true;
                return true;
            }

            auxOutput = newWord ? auxOutput + word[posi] : auxOutput;
            //printAll(word[posi], inputColumn,currentState,lastFinal,output,isCharAccepted(word[posi]));
            
            if(currentState == 0 && lastFinal != 0){
                //std::cout << "Entrou currentState == 0 && lastFinal != 0\n";
                //printOutput(output,lastFinal);
                allTokens.push_back(lastFinal);
                allLines.push_back(linePosi);
                allwords.push_back(word);
                // allColumns.push_back(columnPosi - whiteSpaces);
                resetStates(auxOutput,output,currentState,lastFinal,newWord,word[posi],0);
                wordAccepted = true;
            }else if(currentState == 0 && lastFinal == 0){
                std::cout << "ERRO LEXICO. Linha: " << linePosi << " Coluna: " << columnPosi-1 << " -> " << "'" << word[posi]<<"'"; // ERRO não chegou a nenhum estado 
                return false;
            }else{
                output = auxOutput;
                newWord = true;
                posi++;
            }
            
        }else{
            if(posi == wordSize){ 
                currentState = 0 ;
                if(currentState == 0 && lastFinal != 0){
                    //printOutput(output,lastFinal);
                    wordAccepted = true;
                    break;
                }
                
            }else{
                std::cout << "ERRO LEXICO. Linha: " << linePosi << " Coluna: " << columnPosi-1 << " -> " << "'" << word[posi]<<"'"; // ERRO char não aceito 
                return false;
            }
            posi++;
        }
        //std::cout << output << "\n";
    }
    if(wordAccepted){
        allTokens.push_back(lastFinal);
        allLines.push_back(linePosi);
        allwords.push_back(word);
        // allColumns.push_back(columnPosi);
    }
    //std::cout <<"\n";
    return wordAccepted;
}

