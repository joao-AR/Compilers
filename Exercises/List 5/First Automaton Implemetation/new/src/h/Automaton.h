#include <iostream>

#ifndef Auto
#define Auto
    void analisadorLexico(std::string stingEntrada,int automato [][5], bool haveNextLine);

    int getNovoEstadoAtual(int linhaEstado,int colunaEntrada,int automato [][5]);
    int getColunaEntrada(char c);
    
    void resetEstados(std::string &auxSaida,std::string &saida,int &currentState,int &lastFinal,bool &novaLetra,char c ,int tipoReset);
    void imprimeSaida(std::string saida,int lastFinal);

#endif