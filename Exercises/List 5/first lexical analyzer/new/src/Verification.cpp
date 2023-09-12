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
    char letrasAceitas[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; 
    bool isAceita = std::find(std::begin(letrasAceitas), std::end(letrasAceitas), c) != std::end(letrasAceitas);
    return isAceita;
}

bool isCharAceita(char c){
    return true;
}

void verificaPalavraAceita(std::string palavra,int automato [][41],bool haveNextLine){
    int estadosFinais[] = {2,3,4,5,6,7,8,9,11,12,13};

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
            
            if(currentState == 0 && lastFinal != 0 && lastFinal !=9){
                imprimeSaida(saida,lastFinal);
                resetEstados(auxSaida,saida,currentState,lastFinal,novaLetra,palavra[posi],0);
                
            }else if(currentState == 0 && lastFinal == 0){
                std::cout << "ERRO\n";
                resetEstados(auxSaida,saida,currentState,lastFinal,novaLetra,palavra[posi],1);
                
            }else if( ( posi == tamanhoPalavra) && (currentState == 0 && lastFinal == 9 )  && haveNextLine){ // verifica se é um comentario 
                    lastFinal = 11;
                    imprimeSaida(saida,lastFinal);
                    break;
            }else{
                saida = auxSaida;
                novaLetra = true;
                posi++;
            }
            
        }
        
    }
}