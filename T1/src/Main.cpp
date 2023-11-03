#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "./h/Automaton.h"
#include "./h/Verification.h"
#include "./h/Lex.h"
#include "./h/Parsing.h"

int main(){
    
    std::string line;
    bool lexicalError = false;
    bool haveNextLine;
    bool commentSearch = false;
    bool lineComment = false;
    bool stringSearch = false;

    int linePosi = 1;
    int columnPosi = 1;

    while (true) {
        // Tenta ler uma linha da entrada padrão
        if (std::getline(std::cin, line)) {

            // verificar se tem mais linhas 
            haveNextLine = std::cin.peek() != EOF ?  haveNextLine = true : haveNextLine = false;
            // chamar a funcão que vai andar pelo automato
            
            lexicalError = !lexAnalyser(line,haveNextLine,commentSearch,lineComment,linePosi,columnPosi); 
            if(lineComment){lineComment = false;}
            if(lexicalError){
                std::cout << "Lex error: line: " << line << "\n";
            }else{
                // if(haveNextLine == true){
                //     std::cout << "\n";
                // }
            }
            columnPosi = 1;
            linePosi++;
            // Verifica se há mais uma linha disponível 
        } else {
            //std::cout << "Erro de leitura ou final do arquivo." << std::endl;
            parsing(line,haveNextLine,linePosi,columnPosi);
            break;
        }
    }
}