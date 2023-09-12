#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "./h/Verification.h"
#include "./h/Automaton.h"


int main(){
    // entradasAceitas = "+","-","0-9","a","c","e","h","i","r","s","t" 
    int automato [][11] = {
    /*estado 0*/ {0,0,0,0,0,0,0,0,0,0,0},
    /*estado 1*/ {17,18,19,0,11,0,2,0,0,4,0},
    /*estado 2*/ {0,0,0,0,0,3,0,7,0,0,0},
    /*estado 3*/ {0,0,0,0,0,0,0,0,9,0,0},
    /*estado 4*/ {0,0,0,0,0,0,5,0,0,0,0},
    /*estado 5*/ {0,0,0,0,0,6,0,0,0,0,0},
    /*estado 6*/ {0,0,0,0,0,0,0,0,0,0,0},
    /*estado 7*/ {0,0,0,0,0,0,0,0,0,8,0},
    /*estado 8*/ {0,0,0,0,0,0,0,0,0,0,0},
    /*estado 9*/ {0,0,0,0,0,0,0,0,0,10,0},
    /*estado 10*/{0,0,0,0,0,0,0,0,0,0,0},
    /*estado 11*/{0,0,0,12,0,0,0,0,0,0,0},
    /*estado 12*/{0,0,0,0,0,0,0,0,14,0,13},
    /*estado 13*/{0,0,0,0,0,0,0,0,0,15,0},
    /*estado 14*/{0,0,0,0,0,0,0,0,0,16,0},
    /*estado 15*/{0,0,0,0,0,0,0,0,0,0,0},
    /*estado 16*/{0,0,0,0,0,0,0,0,0,0,0},
    /*estado 17*/{0,0,0,0,0,0,0,0,0,0,0},
    /*estado 18*/{0,0,0,0,0,0,0,0,0,0,0},
    /*estado 19*/{0,0,19,0,0,20,0,0,0,0,0},
    /*estado 20*/{21,21,22,0,0,0,0,0,0,0,0},
    /*estado 21*/{0,0,22,0,0,0,0,0,0,0,0},
    /*estado 22*/{0,0,22,0,0,0,0,0,0,0,0},
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


