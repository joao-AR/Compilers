#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include<string>
#include <algorithm>  // Para a função std::find

bool verificaEstadoAceito(char caractere){
    return true;
    //todo verificação
}

bool verificaLetra(char caractere){
    if(caractere == 'a' || caractere == 'b' || caractere == 'c'||  caractere == 'd' ){
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
void imprimeResultado(std::string saida, int lastFinal){
    std::cout << "Entrada > "; 
    std::cout << saida;
    std::cout << " < Reconhecida no estado "; 
    std::cout << lastFinal; 
    std::cout << "\n ";
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
    std::string entrada = "+-dbdabc";
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
    
    while(posiNaEntrada < tamanhoEntrada){

        if(novaLetra){
            auxSaida = auxSaida + entrada[posiNaEntrada];
        }
    
        char ultimoCaractere = auxSaida.back();
        isAceito = verificaEstadoAceito(ultimoCaractere);
        
        if(isAceito){
            
            int colunaEntrada = getColunaEntrada(ultimoCaractere);
            currentState = automato [currentState][colunaEntrada];
            isEstadoFinal = std::find(std::begin(estadosFinais), std::end(estadosFinais), currentState) != std::end(estadosFinais);
            lastFinal = isEstadoFinal ? currentState : lastFinal;

            if(currentState == 0 ){
                    imprimeResultado(saida, lastFinal);
                    auxSaida = ultimoCaractere;
                    saida = "";
                    lastFinal  = 0; 
                    currentState = 1;
                    novaLetra = false;
                }else{
                    saida = auxSaida;
                    novaLetra = true;
                    posiNaEntrada++;
                }
        }   
    }

    saida = auxSaida;
    imprimeResultado(saida, lastFinal); // imprime a ultima entrada reconhecido 


    
    return 0; 
}