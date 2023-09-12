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

    while(posiString <= tamanhoEntrada){
        ultimoChar = stingEntrada[posiString];
        palavra = getPalavra(stingEntrada,posiString,tamanhoEntrada);
        verificaPalavraAceita(palavra,automato,haveNextLine);
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

    if(lastFinal == 2 ||  lastFinal == 4){
        std::cout << "ID ";
    }else if(lastFinal == 3){
        std::cout << "IF ";
    }else if(lastFinal == 5 || lastFinal == 9 || lastFinal == 13 ){
        std::cout << "error ";
    }else if(lastFinal == 6 || lastFinal == 8 ){
        std::cout << "Real ";
    }else if(lastFinal == 7){
        std::cout << "NUM ";
    }else if(lastFinal == 11){
        std::cout << "comment ";
    }else if(lastFinal == 12){
        std::cout << "white space ";
    }
}

void imprimeSaida(std::string saida,int lastFinal){
    imprimeToken(lastFinal);
    std::cout << saida << "\n";
}   

