#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "./h/Automaton.h"

bool isNumero(char entrada){
    if(entrada == '0' || entrada == '1' || entrada == '2' ||  entrada == '3' ||entrada == '4'  || entrada == '5' || entrada == '6' ||  entrada == '7' || entrada == '8' || entrada == '9' ){
        return true;
    }    
    return false;
}

bool isletrasAceitas(char c){
    char letrasAceitas[] = {'a','c','e','h','i','r','s','t'}; 
    bool isAceita = std::find(std::begin(letrasAceitas), std::end(letrasAceitas), c) != std::end(letrasAceitas);
    return isAceita;
}

bool isCharAceita(char c){
    if(c == '+'|| c == '-' || isNumero(c)|| isletrasAceitas(c)){
        return true;
    }else{
        return false;
    }
}

void verificaPalavraAceita(std::string palavra,int automato [][11]){
    int estadosFinais[] = {3,6,8,10,13,14,15,16,17,18,19,22};

    int tamanhoPalavra = palavra.size();
    int posi = 0;
    
    std::string auxSaida = "";
    std::string saida = "";

    int colunaEntrada;
    int currentState = 1;
    int lastFinal = 0;

    bool isEstadoFinal;
    bool novaLetra = true;
    
    while(posi <= tamanhoPalavra){
        if(isCharAceita(palavra[posi])){
            //std::cout << palavra[posi] << " << c \n";
            colunaEntrada = getColunaEntrada(palavra[posi]);
            currentState = getNovoEstadoAtual(currentState,colunaEntrada,automato);
            
            isEstadoFinal = std::find(std::begin(estadosFinais), std::end(estadosFinais), currentState) != std::end(estadosFinais);
            lastFinal = isEstadoFinal ? currentState : lastFinal;
            
            auxSaida = novaLetra ? auxSaida + palavra[posi] : auxSaida;

            if(currentState == 0 && lastFinal != 0){
                imprimeSaida(saida,lastFinal);
                resetEstados(auxSaida,saida,currentState,lastFinal,novaLetra,palavra[posi],0);
                
            }else if(currentState == 0 && lastFinal == 0){
                std::cout << "ERRO\n";
                resetEstados(auxSaida,saida,currentState,lastFinal,novaLetra,palavra[posi],1);
                
            }else{
                saida = auxSaida;
                novaLetra = true;
                posi++;
            }
            
        }else{
            if(posi == tamanhoPalavra){ 
                currentState = 0 ;
                if(currentState == 0 && lastFinal != 0){
                    imprimeSaida(saida,lastFinal);
                    break;
                }
                
            }else{
                std::cout << "ERRO\n";
                novaLetra = true;
                saida = auxSaida;
                auxSaida = "";  
            }
            posi++;
        }
        
    }
}