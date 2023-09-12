#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "./h/Verification.h"


std::string getPalavra(std::string stingEntrada,int &posiString, int tamanhoEntrada){
    char c;
    std::string palavra;
    while (stingEntrada[posiString  ] != ' '){
        c = stingEntrada[posiString];
        palavra = palavra + c;
        posiString++;
        if(posiString == tamanhoEntrada){
            return palavra;
        }
    }
    return palavra;
}


int getNovoEstadoAtual(int linhaEstado,int colunaEntrada,int automato [][11]){
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
        if(c == 'a'){
            return 3;
        }else if(c == 'c'){
            return 4;
        }else if(c == 'e'){
            return 5;
        }else if(c == 'h'){
            return 6;
        }else if(c == 'i'){
            return 7;
        }else if(c == 'r'){
            return 8;
        }else if(c == 's'){
            return 9;
        }else if(c == 't'){
            return 10;
        }
    }
    return -1;
}

void analisadorLexico(std::string stingEntrada,int automato [][11], bool haveNextLine){
    int posiString = 0;
    size_t tamanhoEntrada = stingEntrada.size();
    char ultimoChar;
    std::string palavra = "";

    while(posiString <= tamanhoEntrada){
        ultimoChar = stingEntrada[posiString];
        palavra = getPalavra(stingEntrada,posiString,tamanhoEntrada);
        verificaPalavraAceita(palavra,automato);
        posiString++;
    }
    
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

void imprimeToken (int lastFinal){
    if(lastFinal == 3 ){
    std::cout << "ELE ";
    }else if(lastFinal == 6){
        std::cout << "ELA ";
    }else if(lastFinal == 8){
        std::cout << "DELE ";
    }else if(lastFinal == 10){
        std::cout << "DELA ";
    }else if(lastFinal == 13){
        std::cout << "GATO ";
    }else if(lastFinal == 14){
        std::cout << "CARRO ";
    }else if(lastFinal == 15){
        std::cout << "GATOS ";
    }else if(lastFinal == 16){
        std::cout << "CARROS ";
    }else if(lastFinal == 17){
        std::cout << "MAIS ";
    }else if(lastFinal == 18){
        std::cout << "MENOS ";
    }else if(lastFinal == 19){
        std::cout << "INTEIRO ";
    }else if(lastFinal == 22){
        std::cout << "REAL ";
    }
}

void imprimeSaida(std::string saida,int lastFinal){
    imprimeToken(lastFinal);
    if(lastFinal == 19 || lastFinal == 22){
        std::cout << saida << "\n";
    }else{
        std::cout << "\n";
    }
}   

