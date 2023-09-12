#include <iostream>

#ifndef Auto
#define Auto
    void analisadorLexico(std::string stingEntrada,int automato [][41], bool haveNextLine);

    int getNovoEstadoAtual(int linhaEstado,int colunaEntrada,int automato [][41]);
    std::string getPalavra(std::string stingEntrada,int &posiString, int tamanhoEntrada);
    int getColunaEntrada(char c);
    
    void resetEstados(std::string &auxSaida,std::string &saida,int &currentState,int &lastFinal,bool &novaLetra,char c ,int tipoReset);
    void imprimeSaida(std::string saida,int lastFinal);
    void imprimeToken (int lastFinal);

#endif