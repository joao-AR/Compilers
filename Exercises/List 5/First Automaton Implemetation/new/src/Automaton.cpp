#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "./h/Verification.h"




int getNovoEstadoAtual(int linhaEstado,int colunaEntrada,int automato [][5]){
    int NovoAtual;
    if(colunaEntrada == -1){
        std::cout << "ERRO -1\n";
        return 0;
    }else{
        NovoAtual = automato[linhaEstado][colunaEntrada];
    }
    return NovoAtual;
}

int getColunaEntrada(char c){
    if( c == '+'){
        return 0;
    }else if(c == '-'){
        return 1;
    }else if(isNumero(c)){
        return 2;
    }else if(isletrasAceitas(c)){
        if(c == 'e'){
            return 4;
        }
        return 3;
    }
    return -1;
}

void analisadorLexico(std::string stingEntrada,int automato [][5], bool haveNextLine){
    int posiString = 0;
    size_t tamanhoEntrada = stingEntrada.size();
    char ultimoChar;
    std::string palavra = "";
    verificaPalavraAceita(stingEntrada,automato);
}

void resetEstados(std::string &auxSaida,std::string &saida,int &currentState,int &lastFinal,bool &novaLetra,char c ,int tipoReset){
    if(tipoReset == 0){
        auxSaida = c ;
        saida = "";
        currentState = 1;
        lastFinal = 0;
        novaLetra = false;
    }else if(tipoReset == 1){
        auxSaida = c;
        saida = "";
        currentState = 1;
        lastFinal = 0;
        novaLetra = false;
    }
}

void imprimeSaida(std::string saida,int lastFinal){
    std::cout << saida << "\n";
}   

