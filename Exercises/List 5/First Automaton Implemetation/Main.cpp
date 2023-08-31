#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include<string>
#include <algorithm>  // Para a função std::find

bool verificaEstadoAceito(char caractere){
    return true;
    //todo verificação
}

bool verificaLetra(char caractere){
    if(
           caractere == 'a' || caractere == 'b' || caractere == 'c'||  caractere == 'd'
        || caractere == 'e' || caractere == 'f' || caractere == 'g'||  caractere == 'h'
        || caractere == 'i' || caractere == 'j' || caractere == 'k'||  caractere == 'l'
        || caractere == 'm' || caractere == 'n' || caractere == 'o'||  caractere == 'p'
        || caractere == 'q' || caractere == 'r' || caractere == 's'||  caractere == 't'
        || caractere == 'u' || caractere == 'v' || caractere == 'w'||  caractere == 'x' 
        || caractere == 'y' || caractere == 'z'){
        return true;
    }
    return false;
}

int getColunaEntrada(char entrada){
    if(entrada == '+'){
        return 0;
    }else if(entrada == '-'){
        return 1;
    }else if(verificaLetra(entrada)){
        return 2;
    }
}

bool verificaEntradaAceito(char entrada){
    if(entrada == '+'){
        return true;
    }else if(entrada == '-'){
        return true;
    }else if(verificaLetra(entrada)){
        return true;
    }
    return false;
}

void imprimeResultado(std::string saida, int lastFinal){
    if(saida != " "){
        std::cout << "Entrada > "; 
        std::cout << saida;
        std::cout << " < Reconhecida no estado "; 
        std::cout << lastFinal; 
        std::cout << "\n ";
    }
}

int main(){
    std::string entradasAceitas[] = {"+","-","a-z","0-9","e"};
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


    int estadosFinais[] = {2,3,4,5,8};
    std::string entrada = "+-abcabc@ abc fgh";
    std::string saida;
    std::string auxSaida;

    // valores iniciais
    int  lastFinal  = 0; 
    int  currentState = 1;

    bool isAceito;
    bool isEstadoFinal;
    bool novaLetra = true;
    size_t tamanhoEntrada = entrada.size();
    int posiNaEntrada = 0;
    
    while(posiNaEntrada <= tamanhoEntrada){
        auxSaida = novaLetra ? auxSaida + entrada[posiNaEntrada] : auxSaida;
        char ultimoCaractere = auxSaida.back();
        std::cout << "estado atual >>";
        std::cout << currentState;
        std::cout << "\n ";
        isAceito = verificaEntradaAceito(ultimoCaractere);
        
        if(!isAceito ){
            imprimeResultado(saida, lastFinal);
            // imprimir a string aceita anterior ao erro 
            if(posiNaEntrada >= tamanhoEntrada){ // erro imprimir erro  no fim ao final da string
                break;
            }
            std::cout << "ERRO";
            std::cout << "\n";
            saida = "";
            lastFinal = 0; 
            currentState = 1;
            posiNaEntrada++;
            std::cout << "estado atual213 >>";
            std::cout << currentState;
            std::cout << "\n ";
            auxSaida = entrada[posiNaEntrada];
            char ultimoCaractere = auxSaida.back();
        }
    
        int colunaEntrada = getColunaEntrada(ultimoCaractere);
        if(isAceito ){    
            currentState = automato [currentState][colunaEntrada];
        }
        isEstadoFinal = std::find(std::begin(estadosFinais), std::end(estadosFinais), currentState) != std::end(estadosFinais);
        lastFinal = isEstadoFinal ? currentState : lastFinal;

        if(currentState == 0 && isAceito){
                imprimeResultado(saida, lastFinal);
                auxSaida = ultimoCaractere;
                saida = "";
                lastFinal = 0; 
                currentState = 1;
                novaLetra = false;
            }else if( posiNaEntrada == tamanhoEntrada && isAceito){
                saida = auxSaida;
                imprimeResultado(saida, lastFinal); // imprime a ultima entrada reconhecido 
                break;
            }else{
                saida = auxSaida;
                novaLetra = true;
                posiNaEntrada++;
            }
    }

    
    return 0; 
}