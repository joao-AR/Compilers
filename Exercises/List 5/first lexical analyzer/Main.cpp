#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include<string>
#include <algorithm>  // Para a função std::find

#include "verification.h"

int getColunaEntrada(char entrada, int currentState);
void printResultado(std::string saida, int lastFinal);
bool erro(int &lastFinal,std::string &saida, int &currentState, int &posiNaEntrada, std::string &auxSaida, char &ultimoCaractere, int tamanhoEntrada,std::string entrada);
void resetAutomato(int &lastFinal, int &currentState, std::string &auxSaida, char ultimoCaractere);

int main(){
    // entradasAceitas = "i","f","a-h",j-z","a-e","g-z",a-z","0-9",".","-","\n","Blank","qualqueroutro"
    // ID = 2,4
    // IF = 3 
    // whithe space = 12 
    // error = 5,9,13
    //real = 6,8
    //num = 7
    //comment = 11
    int automato [][13] = {
    /*estado 0*/ {0,0,0,0,0,0,0,0,0,0,0,0,0},
    /*estado 1*/ {2,0,4,4,0,0,0,7,5,9,0,12,13},
    /*estado 2*/ {0,3,0,0,4,4,0,4,0,0,0,0,0},
    /*estado 3*/ {0,0,0,0,0,0,4,4,0,0,0,0,0},
    /*estado 4*/ {0,0,0,0,0,0,4,4,0,0,0,0,0},
    /*estado 5*/ {0,0,0,0,0,0,0,6,0,0,0,0,0},
    /*estado 6*/ {0,0,0,0,0,0,0,6,0,0,0,0,0},
    /*estado 7*/ {0,0,0,0,0,0,0,7,8,0,0,0,0},
    /*estado 8*/ {0,0,0,0,0,0,0,8,0,0,0,0,0},
    /*estado 9*/ {0,0,0,0,0,0,0,0,0,10,0,0,0},
    /*estado 10*/{0,0,0,0,0,0,10,0,0,0,11,0,0},
    /*estado 11*/{0,0,0,0,0,0,0,0,0,0,0,0,0},
    /*estado 12*/{0,0,0,0,0,0,0,0,0,0,0,12,0},
    /*estado 13*/{0,0,0,0,0,0,0,0,0,0,0,0,0},
    };


    int estadosFinais[] = {2,3,4,5,6,7,8,9,11,12,13};
    std::string entrada;
    entrada = "chuchu teste ";
    
    // std::getline(std::cin,entrada);
    
    std::string saida;
    std::string auxSaida;
    // valores iniciais
    int  lastFinal  = 0; 
    int  currentState = 1;

    bool isAceito = false;
    bool isEstadoFinal;
    bool novaLetra = true;
    bool stop = false;
    size_t tamanhoEntrada = entrada.size();
    int posiNaEntrada = 0;
    
    char ultimoCaractere;
    while(posiNaEntrada <= tamanhoEntrada){
        auxSaida = novaLetra ? auxSaida + entrada[posiNaEntrada] : auxSaida;
        ultimoCaractere = auxSaida.back();
        // std::cout << auxSaida;
        isAceito = isEntradaAceita(ultimoCaractere);
        // while (isAceito != true){
        //     isAceito = isEntradaAceita(ultimoCaractere);
        //     if(!isAceito ){ 
        //     stop = erro(lastFinal,saida,currentState,posiNaEntrada,auxSaida,ultimoCaractere,tamanhoEntrada,entrada);  
        //     if(stop){break;}
        //     }
        // }

        int colunaEntrada = getColunaEntrada(ultimoCaractere,currentState);
        // std::cout << " colunaEntrada >> ";
        // std::cout << colunaEntrada;
        // std::cout << "\n";
        
        // std::cout << currentState;
        // std::cout << "\n";
        if(isAceito){    
            currentState = automato [currentState][colunaEntrada];
            // std::cout << " novo current state >> ";
            // std::cout << currentState;
            // std::cout << "\n";
        }
        isEstadoFinal = std::find(std::begin(estadosFinais), std::end(estadosFinais), currentState) != std::end(estadosFinais);
        lastFinal = isEstadoFinal ? currentState : lastFinal;
        
        if(isAceito && currentState == 0 && lastFinal != 0){
            printResultado(saida, lastFinal);
            auxSaida = ultimoCaractere;
            resetAutomato(lastFinal,currentState,auxSaida, ultimoCaractere);
            novaLetra = false;

        }else if( posiNaEntrada == tamanhoEntrada ){
            saida = auxSaida;
            printResultado(saida, lastFinal); // imprime a ultima entrada reconhecida
            break;
        
        }else if(lastFinal != 0 && currentState != 0 ){
            saida = auxSaida;
            novaLetra = true;
            posiNaEntrada++;
        }

     if(lastFinal == 0 && currentState == 0){ // verificação de erro caso a primeira entrada não seja aceita 
            stop = erro(lastFinal,saida,currentState,posiNaEntrada,auxSaida,ultimoCaractere,tamanhoEntrada,entrada);  
            if(stop){
                break;
            }
            novaLetra = false;
        }
    }


    return 0; 
}

void resetAutomato(int &lastFinal, int &currentState, std::string &auxSaida, char ultimoCaractere){
    lastFinal  = 0; 
    currentState = 1;
    auxSaida = ultimoCaractere;
}

int getColunaEntrada(char entrada, int currentState){

    if(isLetra(entrada)){
        if(entrada == 'i' && currentState == 1){
            return 0;
        }else if(entrada == 'f' && currentState == 2){
            return 1;
        }else if(currentState == 1 && isAh(entrada)){
            return 2;
        }else if(currentState == 1 && isJz(entrada)){
            return 3;
        }else if(currentState == 2 && isAe(entrada)){
            return 4;
        }else if(currentState == 2 && isGz(entrada)){
            return 5;
        }else{
            return 6;
        }
    }else if(isNumero(entrada)){
        return 7;
    }else if(entrada == '.'){
        return 8;
    }else if(entrada == '-'){
        return 9;
    }else if(entrada == '\n'){
        return 10;
    }else if(entrada == ' '){
        return 11;
    }else{
        return 12;
    }
    return 0;
}


void printResultado(std::string saida, int lastFinal){
        std::cout << "Entrada > "; 
        std::cout << saida;
        std::cout << " < Reconhecida no estado "; 
        std::cout << lastFinal; 
        std::cout << "\n";
}

bool erro(int &lastFinal,std::string &saida, int &currentState, int &posiNaEntrada, std::string &auxSaida, char &ultimoCaractere, int tamanhoEntrada,std::string entrada){
            if(lastFinal != 0){printResultado(saida, lastFinal);}
            // imprimir a string aceita anterior ao erro 
            if(posiNaEntrada >= tamanhoEntrada){ // erro imprimir erro  no fim ao final da string
                return true;
            }
            std::cout << "ERRO";
            std::cout << "\n";
            
            saida = "";
            lastFinal = 0; 
            currentState = 1;
            posiNaEntrada++;
            auxSaida = entrada[posiNaEntrada];
            ultimoCaractere = auxSaida.back();
            
            return false;
}
