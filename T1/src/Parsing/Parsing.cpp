#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "../h/Automaton.h"
#include "../h/Parsing.h"

const bool printDebug = true;
int err = 0;
int posiAll;
bool isTermo(int token);
bool isFator(int token);
bool isExpressaoSimples(int token);
bool isIdentificador(int token);
bool isVariavel(int token);

bool isComandos (int token){
    if(  isIdentificador(token) || isVariavel(token) || token == SE || token == ENQUANTO || token == PARA || token == REPITA || token == LEIA || token == IMPRIMA){
        return true;
    }
    return false;


}
bool isExpressaoSimples(int token){
    if(isTermo(token) || token == MAIS || token == MENOS){
        return true;
    }
    return false;
}
bool isExpressao(int token){
    return isExpressaoSimples(token);
}
bool isIdentificador(int token){
    if(token == 2 || token == 4 || token == 5||token == 17  || token == 57 || token ==  101 ||   token ==  104|| token == 8  ||token == 9  ||token == 10 ||token == 14 ||token == 15 ||token == 16 ||token == 18 ||token ==  106 ){
        return true;
    }
    return false;
}

bool isVariavel(int token){return isIdentificador(token);}


bool isFator(int token){
    if(token == AP){return true;}
    if(token == NAO){return true;}
    if(token == NINTEIRO){return true;}
    if(token == NREAL){return true;}
    if(token == VERDADEIRO){return true;}
    if(token == FALSO){return true;}
    if(token == STRING){return true;}
    if(isIdentificador(token)){return true;}
    if(isVariavel(token)){return true;}
    
    return false;
}
bool isTermo(int token){ return isFator(token); }

void parsing(std::string inputString, bool haveNextLine,int &linePosi,int &columnPosi){
    posiAll = 0;
    std::cout << "\n -------------------\n";
    for (size_t i = 0; i < allTokens.size(); i++) {
            std::cout << allTokens[i] << " ";
    }
    
    // std::cout <<  "\n";
    
    // for (size_t i = 0; i < allLines.size(); i++) {
    //         std::cout << allLines[i] << " ";
    // }
    // std::cout <<  "\n";
    // for (size_t i = 0; i < allColumns.size(); i++) {
    //         std::cout << allColumns[i] << " ";
    // }
    // std::cout <<  "\n";
    // for (size_t i = 0; i < allwords.size(); i++) {
    //         std::cout << allwords[i] << " ";
    // }
    
    int posiTokens = 0;
    // DeclaraVariaveis(allTokens[0],allTokens,posiTokens);
    Programa(allTokens[0],allTokens,posiTokens);

    if(err == 0 ){
        std::cout << "CADEITA ACEITA";
    }
    err = 0; // reset no erro para proxima linha
}

void error(std::string errMsg){
    if(err == 0){
        std::cout << errMsg <<"\n";
        err = 1;
    }
}

// Pega o proximo token no vetor
int getToken(std::vector<int> lineTokens,int &posi){
    //if(printDebug){ std::cout <<  "===============GETTOKEN=============== \n";}
    posi++; // vai para a proxima posi do vetor
    //if(printDebug){ std::cout <<  "===============FIM-GETTOKEN=============== \n";}
    std::cout << "POSI >" << posi << '\n';
    return lineTokens[posi];
}

// Vai retornar o Proximo Token do vetor de tokens 
int advance(std::vector<int>  lineTokens,int &posiLineTokens) {
    //if(printDebug){ std::cout <<  "===============ADVANCE=============== \n";}
    int token = getToken(lineTokens,posiLineTokens);
    //if(printDebug){ std::cout <<  "===============FIM_ADVANCE=============== \n";}
    return token;
}

void eat(int expetedToken , int &inputToken,std::vector<int> lineTokens,int &posiLineTokens) {

    if(printDebug){ std::cout <<  "===============EAT=============== \n";}
    if(isIdentificador(inputToken)){
        inputToken = 18;
    }
    std::cout << " \n expetedToken = " << expetedToken << " inputToken = " <<  inputToken << " posiLineTokens = " << posiLineTokens << "\n";

    // Se o token for o token que o programa estava esperando 
    if (expetedToken == inputToken){
        inputToken = advance(lineTokens,posiLineTokens);
    }else{ // Caso não for o token esperado vai se impressa uma msg de erro
        std::string recived = getTokenName(inputToken);
        std::string expected = getTokenName(expetedToken);
        std::string LineErr = std::to_string(allLines[posiAll]);
        std::string ColumnErr = std::to_string(allColumns[posiAll]);
        std::string errMsg = "ERRO DE SINTAXE. Linha:" + LineErr + " Coluna: " + ColumnErr + " -> " + "'" + allwords[posiAll] + "'";
        error(errMsg);
        exit(1);
    }
    posiAll++;
    if(printDebug){ std::cout <<  "===============FIM-EAT=============== \n";}
}


//Programa → algoritmo identificador ; BlocoVariaveis ProcedimentoFuncao BlocoComandos .
void Programa(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "\n===============PROGRAMA=============== \n";}
    
    eat(ALGORITIMO,token,lineTokens, posi);
    if(isIdentificador(token)){
        token=18;
        eat(IDENTIFICADOR,token,lineTokens, posi); 
    }else{
        std::cout << "ERRO Programa\n";
    }
    eat(PV,token,lineTokens, posi); // ; 
    BlocoVariaveis(token,lineTokens, posi);
    ProcedimentoFuncao(token,lineTokens, posi);
    BlocoComandos(token,lineTokens, posi);
    eat(PONTO,token,lineTokens, posi); 
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-PROGRAMA===============\n";}
}

//BlocoVariaveis → variaveis Declaracoes
//BlocoVariaveis →
void BlocoVariaveis(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============BlocoVariaveis=============== \n";}
    switch (token){
    case VARIAVEIS:
            eat(VARIAVEIS,token,lineTokens, posi);
            Declaracoes(token,lineTokens, posi);
    break;
    default:
        //BlocoVariaveis →
        break;
    }
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-BlocoVariaveis===============\n";}

}

bool checkTipoBasico(int token){
    if(token == INTEIRO || token == REAL ||  token == CARACTERE ||token ==  LOGICO || isIdentificador(token)){
        return true;
    }
    return false;
}

// Declaracoes → DeclaraVariaveis
// Declaracoes → DeclaraTipo
// Declaracoes → DeclaraVariaveis Declaracoes
// Declaracoes → DeclaraTipo Declaracoes
void Declaracoes(int &token, std::vector<int> lineTokens,int &posi){
    if(checkTipoBasico(token)){
        DeclaraVariaveis(token,lineTokens, posi);// Declaracoes → DeclaraVariaveis
        if(checkTipoBasico(token) || token == TIPO){
            Declaracoes(token,lineTokens, posi); // Declaracoes → DeclaraVariaveis Declaracoes
        }    
    }else if(token == TIPO){ // Declaracoes → DeclaraTipo
        DeclaraTipo(token,lineTokens, posi);
        if(checkTipoBasico(token) || token == TIPO){
            Declaracoes(token,lineTokens, posi); // Declaracoes → DeclaraVariaveis Declaracoes
        } 
    }else{
        std::string LineErr = std::to_string(allLines[posiAll]);
        std::string ColumnErr = std::to_string(allColumns[posiAll]);
        std::string errMsg = "ERRO DE SINTAXE. Linha:" + LineErr + " Coluna: " + ColumnErr + " -> " + "'" + allwords[posiAll] + "'";
        error(errMsg);
        exit(1);
    }
    posiAll++;
}

// DeclaraTipo → tipo identificador = VetorMatriz [ Dimensao ] TipoBasico ;
void DeclaraTipo(int &token, std::vector<int> lineTokens,int &posi){
    eat(TIPO,token,lineTokens, posi);
    if(isIdentificador(token)){
        token=18;
        eat(IDENTIFICADOR,token,lineTokens, posi); 
    }else{
        std::cout << "ERRO DeclaraTipo\n";
        exit(1);
    }
    eat(IGUAL,token,lineTokens, posi);
    VetorMatriz(token,lineTokens, posi);
    eat(AC,token,lineTokens, posi);// [
    Dimensao(token,lineTokens, posi);
    eat(FC,token,lineTokens, posi);// ]
    TipoBasico(token,lineTokens, posi);
    eat(PV,token,lineTokens, posi);// ;
    posiAll++;
}

//VetorMatriz → vetor
//VetorMatriz → matriz
void VetorMatriz(int &token, std::vector<int> lineTokens,int &posi){
    if(token == VETOR){
        eat(VETOR,token,lineTokens, posi);
    }else if(token == MATRIZ){
        eat(MATRIZ,token,lineTokens, posi);
    }else{
        std::string LineErr = std::to_string(allLines[posiAll]);
        std::string ColumnErr = std::to_string(allColumns[posiAll]);
        std::string errMsg = "ERRO DE SINTAXE. Linha:" + LineErr + " Coluna: " + ColumnErr + " -> " + "'" + allwords[posiAll] + "'";
        error(errMsg);
        exit(1);
    }
    posiAll++;
}

//Dimensao → numero inteiro : numero inteiro
//Dimensao → numero inteiro : numero inteiro , Dimensao
void Dimensao(int &token, std::vector<int> lineTokens,int &posi){
    //Dimensao → numero inteiro : numero inteiro
    eat(NINTEIRO,token,lineTokens, posi);//numero_inteiro 
    eat(DP,token,lineTokens, posi);//:
    eat(NINTEIRO,token,lineTokens, posi);//numero_inteiro
    if(token == VIRGULA){ //Dimensao → numero inteiro : numero inteiro , Dimensao
        eat(VIRGULA,token,lineTokens, posi);
        Dimensao(token,lineTokens, posi);
    }
    posiAll++;
}

//DeclaraVariaveis → TipoBasico : DeclaraIdentificador ;
void DeclaraVariaveis(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============DeclaraVariaveis=============== \n";}

    if(token == INTEIRO || token == REAL ||  token == CARACTERE ||token ==  LOGICO || isIdentificador(token)){
        TipoBasico(token,lineTokens, posi);
        eat(DP,token,lineTokens, posi);//:
        DeclaraIdentificador(token,lineTokens, posi);
        std::cout << "-----PV\n";
        eat(PV,token,lineTokens, posi);//;
    }else{
        std::cout << "Erro DeclaraVariaveis\n";
        std::string LineErr = std::to_string(allLines[posiAll]);
        std::string ColumnErr = std::to_string(allColumns[posiAll]);
        std::string errMsg = "ERRO DE SINTAXE. Linha:" + LineErr + " Coluna: " + ColumnErr + " -> " + "'" + allwords[posiAll] + "'";
        error(errMsg);
        exit(1); 
    }
    posiAll++;
    if(printDebug){ std::cout <<  "===============FIM-DeclaraVariaveis=============== \n";}
}

// DeclaraIdentificador → identificador
// DeclaraIdentificador → identificador , DeclaraIdentificador
void DeclaraIdentificador(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============DeclaraIdentificador=============== \n";}

        std::cout << "VIRGULA " << VIRGULA << " token " << token << " \n";
    if(isIdentificador(token)){
        token = 18;
        eat(IDENTIFICADOR,token,lineTokens, posi);// DeclaraIdentificador → identificador
        if(token == VIRGULA){
            eat(VIRGULA,token,lineTokens, posi);
            DeclaraIdentificador(token,lineTokens, posi);// DeclaraIdentificador → identificador , DeclaraIdentificador
        }
    }else{
        std::cout << "Erro DeclaraIdentificador\n";
        std::string LineErr = std::to_string(allLines[posiAll]);
        std::string ColumnErr = std::to_string(allColumns[posiAll]);
        std::string errMsg = "ERRO DE SINTAXE. Linha:" + LineErr + " Coluna: " + ColumnErr + " -> " + "'" + allwords[posiAll] + "'";
        error(errMsg);
        exit(1); 
    }   

    if(printDebug){ std::cout <<  "===============FIM-DeclaraIdentificador=============== \n";}

    posiAll++;
}
// ProcedimentoFuncao → DeclaraProcedimento ProcedimentoFuncao
// ProcedimentoFuncao → DeclaraFuncao ProcedimentoFuncao
// ProcedimentoFuncao →
void ProcedimentoFuncao(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============ProcedimentoFuncao=============== \n";}
    
    if(token == PROCEDIMENTO){
        DeclaraProcedimento(token,lineTokens, posi);
        ProcedimentoFuncao(token,lineTokens, posi);
    }else if (token == FUNCAO){
        DeclaraFuncao(token,lineTokens, posi);
        ProcedimentoFuncao(token,lineTokens, posi);
    }
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-ProcedimentoFuncao===============\n";}

}


//DeclaraProcedimento → procedimento identificador Parametros ; DeclaraParametros BlocoVariaveis BlocoComandos ;
void DeclaraProcedimento(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============DeclaraProcedimento=============== \n";}
    eat(PROCEDIMENTO,token,lineTokens, posi);
    if(isIdentificador(token)){
        token = 18;
        eat(IDENTIFICADOR,token,lineTokens, posi);
    }else{
        std::cout << "Erro\n";
        exit(1);
    }
    Parametros(token,lineTokens, posi);
    eat(PV,token,lineTokens, posi); // ;
    TipoBasico(token,lineTokens, posi);
    eat(PV,token,lineTokens, posi); // ;
    DeclaraParametros(token,lineTokens, posi);
    BlocoVariaveis(token,lineTokens, posi);
    BlocoComandos(token,lineTokens, posi);
    eat(PV,token,lineTokens, posi);

    if(printDebug){ std::cout <<  "==============FIM-DeclaraProcedimento===============\n";}
}

//DeclaraFuncao → funcao identificador Parametros : TipoBasico ; DeclaraParametros BlocoVariaveis BlocoComandos ;
void DeclaraFuncao(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============DeclaraFuncao=============== \n";}
    eat(FUNCAO,token,lineTokens, posi);
    if(isIdentificador(token)){
        token = 18;
        eat(IDENTIFICADOR,token,lineTokens, posi);
    }else{
        std::cout << "Erro\n";
        exit(1);
    }
    Parametros(token,lineTokens, posi);
    eat(DP,token,lineTokens, posi); // :
    TipoBasico(token,lineTokens, posi);
    eat(PV,token,lineTokens, posi); // ;
    DeclaraParametros(token,lineTokens, posi);
    BlocoVariaveis(token,lineTokens, posi);
    BlocoComandos(token,lineTokens, posi);
    eat(PV,token,lineTokens, posi);
    
    if(printDebug){ std::cout <<  "==============FIM-DeclaraFuncao===============\n";}
}
//BlocoComandos → inicio ListaComandos fim
void BlocoComandos(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============BlocoComandos=============== \n";}
    eat(INICIO,token,lineTokens, posi);
    ListaComandos(token,lineTokens, posi);
    eat(FIM,token,lineTokens, posi);
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-BlocoComandos===============\n";}
}

// ListaComandos → Comandos ;
// ListaComandos → Comandos ; ListaComandos
void ListaComandos (int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============ListaComandos=============== \n";}
    Comandos(token,lineTokens, posi);
    eat(PV,token,lineTokens, posi);

    if(isComandos(token)){
        ListaComandos(token,lineTokens, posi);
    }

    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-ListaComandos===============\n";}
}
// Comandos → identificador
// Comandos → identificador ( ExprIter )
// Comandos → Variavel <- Expressao
// Comandos → se Expressao entao ListaComandos fim se
// Comandos → se Expressao entao ListaComandos senao ListaComandos fim se
// Comandos → enquanto Expressao faca ListaComandos fim enquanto
// Comandos → para identificador de Expressao ate Expressao faca ListaComandos fim para
// Comandos → para identificador de Expressao ate Expressao passo Expressao faca ListaComandos fim para
// Comandos → repita ListaComandos ate Expressao
// Comandos → leia ( V ariavel )
// Comandos → imprima ( ExprIter )
void Comandos (int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============Comandos=============== \n";}
    
    if(isIdentificador(token)){
        token = 18;
        eat(IDENTIFICADOR,token,lineTokens, posi);
        
        if(token == AP){
            eat(AP,token,lineTokens, posi);
            ExprIter(token,lineTokens, posi); 
            eat(FP,token,lineTokens, posi);
        }
    }else if(isVariavel(token)){
        Variavel(token,lineTokens, posi);
        eat(ATRIBUICAO,token,lineTokens, posi); // <-
        Expressao(token,lineTokens, posi);
    }else if(token == SE ){
        eat(SE,token,lineTokens, posi);
        Expressao(token,lineTokens, posi); 
        eat(ENTAO,token,lineTokens, posi);
        ListaComandos(token,lineTokens, posi);
        if(token == FIM){
            eat(FIM,token,lineTokens, posi);
            eat(SE,token,lineTokens, posi);
        }else if(token == SENAO){
            eat(SENAO,token,lineTokens, posi);
            ListaComandos(token,lineTokens, posi);
            eat(FIM,token,lineTokens, posi);
            eat(SE,token,lineTokens, posi);
        }else{
            //Todo Erro
        }

    }else if(token == ENQUANTO){
        eat(ENQUANTO,token,lineTokens, posi);
        Expressao(token,lineTokens, posi);
        eat(FACA,token,lineTokens, posi);
        ListaComandos(token,lineTokens, posi);
        eat(FIM,token,lineTokens, posi);
        eat(ENQUANTO,token,lineTokens, posi);
    }else if (token == PARA){
        eat(PARA,token,lineTokens, posi);
        if(isIdentificador(token)){
        token = 18;
        eat(IDENTIFICADOR,token,lineTokens, posi);
        }else{
            std::cout << "Erro\n";
            exit(1);
        }
        eat(DE,token,lineTokens, posi);
        Expressao(token,lineTokens, posi);
        eat(ATE,token,lineTokens, posi);
        Expressao(token,lineTokens, posi);
        if(token == PASSO){
            eat(PASSO,token,lineTokens, posi);
            Expressao(token,lineTokens, posi);
        }
        eat(FACA,token,lineTokens, posi);
        ListaComandos(token,lineTokens, posi);
        eat(FIM,token,lineTokens, posi);
        eat(PARA,token,lineTokens, posi);

    }else if(token == REPITA){
        eat(REPITA,token,lineTokens, posi);
        ListaComandos(token,lineTokens, posi);
        eat(ATE,token,lineTokens, posi);
        Expressao(token,lineTokens, posi);
    }else if(token == LEIA){
        eat(LEIA,token,lineTokens, posi);
        eat(AP,token,lineTokens, posi);
        Variavel(token,lineTokens, posi);
        eat(FP,token,lineTokens, posi);
    }else if (token == IMPRIMA){
        eat(IMPRIMA,token,lineTokens, posi);
        eat(AP,token,lineTokens, posi);
        ExprIter(token,lineTokens, posi);
        eat(FP,token,lineTokens, posi);
    }else{
        std::cout << "ERRO \n";
        exit(1);
    }

    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-ListaComandos===============\n";}

}
// Expressao → ExpressaoSimples
// Expressao → Expressao = ExpressaoSimples
// Expressao → Expressao <> ExpressaoSimples
// Expressao → Expressao < ExpressaoSimples
// Expressao → Expressao <= ExpressaoSimples
// Expressao → Expressao >= ExpressaoSimples
// Expressao → Expressao > ExpressaoSimples

void Expressao(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============Expressao=============== \n";}
    
    if(isExpressaoSimples(token)){
        ExpressaoSimples(token,lineTokens, posi);
        if(token == IGUAL){
            eat(IGUAL,token,lineTokens, posi);
            Expressao(token,lineTokens, posi);
        }else if( token == DIFERENTE ){
            eat(DIFERENTE,token,lineTokens, posi);
            Expressao(token,lineTokens, posi);
        }else if( token == MENOR){
            eat(MENOR,token,lineTokens, posi);
            Expressao(token,lineTokens, posi);
        }else if( token == MENORIGUAL){
            eat(MENORIGUAL,token,lineTokens, posi);
            Expressao(token,lineTokens, posi);
        }else if( token == MAIORIGUAL){
            eat(MAIORIGUAL,token,lineTokens, posi);
            Expressao(token,lineTokens, posi);
        }else if( token == MAIOR){
            eat(MAIOR,token,lineTokens, posi);
            Expressao(token,lineTokens, posi);
        }
    }else{
        //Todo ERRO
    }
    
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-Expressao===============\n";}

}

// ExpressaoSimples → Termo
// ExpressaoSimples → + Termo
// ExpressaoSimples → - Termo
// ExpressaoSimples → ExpressaoSimples + Termo
// ExpressaoSimples → ExpressaoSimples - Termo
// ExpressaoSimples → ExpressaoSimples OU Termo
void ExpressaoSimples(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============ExpressaoSimples=============== \n";}
    if(token == MAIS){ // ExpressaoSimples → + Termo
        eat(MAIS,token,lineTokens, posi);
        Termo(token,lineTokens, posi); 
        if(token == MAIS || token == MENOS || isTermo(token)){
            ExpressaoSimples(token,lineTokens, posi);
        }
        // }else if(token == OU){
        //     eat(OU,token,lineTokens, posi);
        //     ExpressaoSimples(token,lineTokens, posi);
        // }
    }else if(isTermo(token)){
        Termo(token,lineTokens, posi); // ExpressaoSimples → Termo
            if(token == OU){
                eat(OU,token,lineTokens, posi);
                if(token != MAIS && token != MENOS && isTermo(token)){
                    ExpressaoSimples(token,lineTokens, posi);// ExpressaoSimples → ExpressaoSimples OU Termo

                }
            }
    }else{
        //Todo ERRO
    }
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-ExpressaoSimples===============\n";}
}


// Termo → Fator
// F → Termo * Fator
// Termo → Termo / Fator
// Termo → Termo DIV Fator
// Termo → Termo E Fator
void Termo(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============Termo=============== \n";}
    if(isFator(token)){
        Fator(token,lineTokens, posi);
        if(token == ASTERISCO){
            eat(ASTERISCO, token,lineTokens, posi); // Termo → Termo * Fator
            Fator(token,lineTokens, posi);
        }else if(token == BARRA){
            eat(BARRA, token,lineTokens, posi); // Termo → Termo / Fator
            Fator(token,lineTokens, posi);
        }else if(token == DIV){
            eat(DIV, token,lineTokens, posi); // Termo → Termo DIV Fator
            Fator(token,lineTokens, posi);
        }else if(token == E ){ 
            eat(E, token,lineTokens, posi); // Termo → Termo E Fator
            Fator(token,lineTokens, posi);
        }
    }else{
        // Todo ERRO
    }
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-Termo===============\n";}
}

// Fator → ( Expressao )
// Fator → NAO Fator
// Fator → numero inteiro
// Fator → numero real
// Fator → verdadeiro
// Fator → falso
// Fator → string
// Fator → identificador ( ExprIter )
// Fator → Variavel
void Fator(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============Fator=============== \n";}

    if(isIdentificador(token)){
        token = 18; // IDENTIFICADOR
        eat(IDENTIFICADOR,token,lineTokens, posi);
        if(token == AP){ // Fator → ( Expressao )
            eat(AP,token,lineTokens, posi);
            ExprIter(token,lineTokens, posi);
            eat(FP,token,lineTokens, posi);
        }else{
            Variavel(token,lineTokens, posi);// Fator → Variavel
        }
        // std::cout << "AP Fator\n";
        // std::cout << "FP Fator == " << FP << " token == " << token << '\n';
        

    }else  if(token == NAO){// Fator → NAO Fator
        eat(NAO,token,lineTokens, posi);
        Fator(token,lineTokens, posi);
    }else if(token == NINTEIRO){// Fator → numero inteiro
        eat(NINTEIRO,token,lineTokens, posi);
    }else if(token == NREAL){// Fator → numero real
        eat(NREAL,token,lineTokens, posi);
    }else if(token == VERDADEIRO){// Fator → verdadeiro
        eat(VERDADEIRO,token,lineTokens, posi);
    }else if(token == FALSO){// Fator → falso
        eat(FALSO,token,lineTokens, posi);
    }else if(token == STRING){// Fator → string
        eat(STRING,token,lineTokens, posi);
    }else if(token == AP){// Fator → identificador ( ExprIter ) 
        eat(AP,token,lineTokens, posi);
        Expressao(token,lineTokens, posi);
        eat(FP,token,lineTokens, posi);
    }else if(isVariavel(token)){
        
    }else {
        std::cout << "Erro Fator\n";
        exit(1);
    }

    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-Fator===============\n";}
}
// Variavel → identificador
// Variavel → identificador [ ExprIter ]
void Variavel(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============Variavel=============== \n";}
    if(isIdentificador(token)){
        token = 18;
        eat(IDENTIFICADOR,token,lineTokens, posi); // Variavel → identificador
        if(token == AC){ // [
            eat(AC,token,lineTokens, posi); 
            ExprIter(token,lineTokens, posi);
            eat(FC,token,lineTokens, posi); // Variavel → identificador
        }
    }else{
        //todo ERRO
    }
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-Variavel===============\n";}
}

void ExprIter(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============ExprIter=============== \n";}
    if(isExpressao(token)){
        Expressao(token,lineTokens, posi);
        if(token == VIRGULA){
            eat(VIRGULA,token,lineTokens, posi);
            ExprIter(token,lineTokens, posi);
        }
    }else{
        std::cout << "Erro ExprIter\n";
    }
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-ExprIter===============\n";}
}

//DeclaraParametros → Declaracoes
//DeclaraParametros →
void DeclaraParametros(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============DeclaraParametros=============== \n";}
    if(checkTipoBasico(token) || token == TIPO){
        Declaracoes(token,lineTokens, posi);
    }
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-DeclaraParametros===============\n";}
}
// Parametros → ( DeclaraIdentificador )
// Parametros →
void Parametros(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============Parametros=============== \n";}
    if(token == AP){
        eat(AC,token,lineTokens, posi);// (
        DeclaraIdentificador(token,lineTokens, posi);
        eat(FC,token,lineTokens, posi);// )
    }

    posiAll++;
    if(printDebug){ std::cout <<  "===============FIM-Parametros=============== \n";}
}


// TipoBasico → inteiro
// TipoBasico → real
// TipoBasico → caractere
// TipoBasico → logico
// TipoBasico → identificador
void TipoBasico(int &token, std::vector<int> lineTokens,int &posi){ 
    if(printDebug){ std::cout <<  "===============TipoBasico=============== \n";}

    if( token == INTEIRO){
        eat(INTEIRO,token,lineTokens, posi);
    }else if( token == REAL){
        eat(REAL,token,lineTokens, posi);
    }else if( token == CARACTERE){
        eat(CARACTERE,token,lineTokens, posi);
    }else if(token == LOGICO){
        eat(LOGICO,token,lineTokens, posi);
    }else if( isIdentificador(token)){
        token = 18;
        eat(IDENTIFICADOR,token,lineTokens, posi);
    }else{
        std::cout << "ERRO" << '\n';
        exit(1);
    }

    posiAll++;
    if(printDebug){ std::cout <<  "===============FIM-TipoBasico=============== \n";}
}