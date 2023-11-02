#include "./Automaton.h"
#include <vector>
#include <unordered_map>
#ifndef Par
#define Par
    extern int posiAll;
    void parsing(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine,int &linePosi,int &columnPosi);
    void Programa(int &token, std::vector<int> lineTokens,int &posi);
    void BlocoVariaveis(int &token, std::vector<int> lineTokens,int &posi);
    void BlocoComandos(int &token, std::vector<int> lineTokens,int &posi);
    void ProcedimentoFuncao(int &token, std::vector<int> lineTokens,int &posi);
    void DeclaraProcedimento(int &token, std::vector<int> lineTokens,int &posi);
    void DeclaraFuncao(int &token, std::vector<int> lineTokens,int &posi);
    void Declaracoes(int &token, std::vector<int> lineTokens,int &posi);
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

    const int IDENTIFICADOR1 = 2  ; 
    const int IDENTIFICADOR2 = 4  ; 
    const int NINTEIRO = 3  ; 
    const int IDENTIFICADOR3 = 5  ; 
    const int E = 6  ; 
    const int MAIS = 7  ; 
    const int IDENTIFICADOR4 = 8  ; 
    const int IDENTIFICADOR5 = 9  ; 
    const int IDENTIFICADOR6 = 10 ; 
    const int DP = 11 ; 
    const int PONTO = 12 ; 
    const int IGUAL = 13 ; 
    const int IDENTIFICADOR7 = 14 ; 
    const int IDENTIFICADOR8 = 15 ; 
    const int IDENTIFICADOR9 = 16 ; 
    const int IDENTIFICADOR10 = 17 ; 
    const int IDENTIFICADOR  = 18 ; 
    const int ALGORITIMO = 26 ; 
    const int ATE  = 28 ; 
    const int NREAL = 31 ; 
    const int MENOS = 32 ; 
    const int ASTERISCO = 33 ; 
    const int BARRA = 34 ; 
    const int PV = 35 ; 
    const int CARACTERE  = 43 ; 
    const int DE = 44 ; 
    const int DIV  = 46 ; 
    const int ENQUANTO  = 53 ; 
    const int ENTAO = 56 ; 
    const int IDENTIFICADOR15 = 57 ; 
    const int FACA  = 60 ; 
    const int FALSO = 63 ; 
    const int VIRGULA = 64 ; 
    const int FIM = 66 ; 
    const int FUNCAO = 71 ; 
    const int INICIO = 76 ; 
    const int INTEIRO = 81 ; 
    const int IMPRIMA = 87 ; 
    const int LEIA = 90 ; 
    const int LOGICO  = 95 ; 
    const int MATRIZ = 100; 
    const int IDENTIFICADOR12 = 101; 
    const int NAO = 103; 
    const int IDENTIFICADOR13 = 104; 
    const int OU = 105; 
    const int IDENTIFICADOR14 = 106; 
    const int PARA = 109; 
    const int PASSO = 112; 
    const int PROCEDIMENTO = 123; 
    const int REAL = 126; 
    const int REPITA    = 130; 
    const int SE = 131; 
    const int SENAO = 134; 
    const int TIPO = 137; 
    const int VERDADEIRO = 146; 
    const int VARIAVEIS  = 154; 
    const int VETOR  = 157; 
    const int AC = 158; 
    const int FC  = 159; 
    const int AP = 160; 
    const int FP = 161; 
    const int MENOR = 162; 
    const int DIFERENTE   = 163; 
    const int MENORIGUAL = 164; 
    const int ATRIBUICAO = 165; 
    const int MAIOR   = 166; 
    const int MAIORIGUAL = 167; 
    const int COMENTARIOBLOCO = 170; 
    const int COMENTARIOLINHA = 172; 
    const int STRING = 173; 
#endif