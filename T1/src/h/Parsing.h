#include "./Automaton.h"
#include <vector>
#include <unordered_map>
#ifndef Par
#define Par
    void parsing(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine,int &linePosi,int &columnPosi);
    void Programa(int &token, std::vector<int> lineTokens,int &posi);
    void BlocoVariaveis(int &token, std::vector<int> lineTokens,int &posi);
    void BlocoComandos(int &token, std::vector<int> lineTokens,int &posi);
    void ProcedimentoFuncao(int &token, std::vector<int> lineTokens,int &posi);
    void DeclaraProcedimento(int &token, std::vector<int> lineTokens,int &posi);
    void DeclaraFuncao(int &token, std::vector<int> lineTokens,int &posi);
    void TipoBasico(int &token, std::vector<int> lineTokens,int &posi);
    void DeclaraVariaveis(int &token, std::vector<int> lineTokens,int &posi);
    void DeclaraParametrosDeclaracoes(int &token, std::vector<int> lineTokens,int &posi);
    void Parametros (int &token, std::vector<int> lineTokens,int &posi);
    void DeclaraTipo(int &token, std::vector<int> lineTokens,int &posi);
    void VetorMatriz(int &token, std::vector<int> lineTokens,int &posi);
    void Dimensao(int &token, std::vector<int> lineTokens,int &posi);
    void DeclaraIdentificador(int &token, std::vector<int> lineTokens,int &posi);
    
    std::string getTokenName(int token);

    void getLineTokens(std::string word,int automaton [][ALPHABET_LENGTH],std::vector<int> &lineTokens);
    int getToken(std::vector<int> lineTokens,int &posi);

    int advance(std::vector<int>  lineTokens,int &posiLineTokens);
    void eat(int expetedToken , int &inputToken,std::vector<int> lineTokens,int &posiLineTokens);
    void error(std::string errMsg);

    const int NINTEIRO = 3;
    const int DP = 11;
    const int PONTO = 12;
    const int IGUAL = 13;
    const int IDENTIFICADOR = 18;
    const int ALGORITIMO = 26;
    const int PV = 35; // ;
    const int VIRGULA = 64;
    const int FUNCAO = 71;
    const int CARACTERE = 43;
    const int LOGICO = 95;
    const int REAL = 126;
    const int TIPO = 137;
    const int VETOR = 157;
    const int AC = 158;
    const int FC = 159;
    const int AP = 160;
    const int FP = 161;
    const int INTEIRO = 81;
    const int MATRIZ = 100;
    const int PROCEDIMENTO = 123;
#endif