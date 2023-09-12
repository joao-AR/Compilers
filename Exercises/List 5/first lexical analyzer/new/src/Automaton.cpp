#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "./h/Verification.h"

int getNovoEstadoAtual(int linhaEstado,int colunaEntrada,int automato [][41]){
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
    if( c == ' '){
        return 0;
    }else if(isNumero(c)){
        return 36;
    }else if(c == '.'){
        return 37;
    }else if(c == '-'){
        return 38;
    }else if(isletrasAceitas(c)){
        if(c == 'f'){
            return 6;
        }else if(c == 'i'){
            return 9;
        }else{
            return 1;
        }
    }
    return 40;
}

void analisadorLexico(std::string stingEntrada,int automato [][41], bool haveNextLine){
    int posiString = 0;
    size_t tamanhoEntrada = stingEntrada.size();
    char ultimoChar;
    std::string palavra = "";

    verificaPalavraAceita(stingEntrada,automato,haveNextLine);
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

    if(lastFinal == 2 ||  lastFinal == 4){
        std::cout << " ID\n";
    }else if(lastFinal == 3){
        std::cout << " IF\n";
    }else if(lastFinal == 5 || lastFinal == 9 || lastFinal == 13 ){
        std::cout << " error\n";
    }else if(lastFinal == 6 || lastFinal == 8 ){
        std::cout << " Real\n";
    }else if(lastFinal == 7){
        std::cout << " NUM\n";
    }else if(lastFinal == 11){
        std::cout << " comment\n";
    }else if(lastFinal == 12){
        std::cout << "white space\n";
    }
}

void imprimeSaida(std::string saida,int lastFinal){
    if(lastFinal != 12){
        std::cout << saida;
    }
    imprimeToken(lastFinal);
}   

