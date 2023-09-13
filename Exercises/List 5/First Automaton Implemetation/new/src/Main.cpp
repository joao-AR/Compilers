#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "./h/Verification.h"
#include "./h/Automaton.h"


int main(){
    // entradasAceitas = {"+","-","a-z","0-9","e"};
    int automato [][5] = {
    /*estado 0*/ {0,0,0,0,0},
    /*estado 1*/ {3,4,2,5,0},
    /*estado 2*/ {0,0,2,2,0},
    /*estado 3*/ {0,0,0,0,0},
    /*estado 4*/ {0,0,0,0,0},
    /*estado 5*/ {0,0,0,5,6},
    /*estado 6*/ {7,7,0,8,0},
    /*estado 7*/ {0,0,0,8,0},
    /*estado 8*/ {0,0,0,8,0},
    };

    std::string linha;
    bool haveNextLine;
        while (true) {
            // Tenta ler uma linha da entrada padrão
            if (std::getline(std::cin, linha)) {
                // verificar se tem mais linhas 

                haveNextLine = std::cin.peek() != EOF ?  haveNextLine = true : haveNextLine = false;

                // chamar a funcão que vai andar pelo automato
                analisadorLexico(linha,automato,haveNextLine);
                // Verifica se há mais uma linha disponível
                
            } else {
                //std::cout << "Erro de leitura ou final do arquivo." << std::endl;
                break;
            }
    }


    return 0; 
}


