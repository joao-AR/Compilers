#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "../h/Automaton.h"
#include "../h/Parsing.h"

const bool printDebug = false;
int err = 0;
int posiAll;
void parsing(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine,int &linePosi,int &columnPosi){
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
    std::cout << " \n expetedToken = " << expetedToken << " inputToken = " <<  inputToken << "\n";

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
    eat(IDENTIFICADOR,token,lineTokens, posi); 
    eat(PV,token,lineTokens, posi); // ; 
    BlocoVariaveis(token,lineTokens, posi);
    //ProcedimentoFuncao(token,lineTokens, posi);
    // BlocoComandos();
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
    if(token == INTEIRO || token == REAL ||  token == CARACTERE ||token ==  LOGICO || token == IDENTIFICADOR){
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
    eat(IDENTIFICADOR,token,lineTokens, posi);
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

    if(token == INTEIRO || token == REAL ||  token == CARACTERE ||token ==  LOGICO || token == IDENTIFICADOR){
        TipoBasico(token,lineTokens, posi);
        eat(DP,token,lineTokens, posi);//:
        DeclaraIdentificador(token,lineTokens, posi);
        eat(PV,token,lineTokens, posi);//;
    }else{
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

    switch (token){
    case IDENTIFICADOR:
        eat(IDENTIFICADOR,token,lineTokens, posi);// DeclaraIdentificador → identificador
        
        if(token == VIRGULA){
            eat(VIRGULA,token,lineTokens, posi);
            DeclaraIdentificador(token,lineTokens, posi);// DeclaraIdentificador → identificador , DeclaraIdentificador
        }
        break;
    default:
        std::string LineErr = std::to_string(allLines[posiAll]);
        std::string ColumnErr = std::to_string(allColumns[posiAll]);
        std::string errMsg = "ERRO DE SINTAXE. Linha:" + LineErr + " Coluna: " + ColumnErr + " -> " + "'" + allwords[posiAll] + "'";
        error(errMsg);
        exit(1); 
        break;
    }
    if(printDebug){ std::cout <<  "===============FIM-DeclaraIdentificador=============== \n";}

    posiAll++;
}
// ProcedimentoFuncao → DeclaraProcedimento ProcedimentoFuncao
// ProcedimentoFuncao → DeclaraFuncao ProcedimentoFuncao
// ProcedimentoFuncao →
void ProcedimentoFuncao(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============ProcedimentoFuncao=============== \n";}
    
    
    
    posiAll++;
    if(printDebug){ std::cout <<  "==============FIM-ProcedimentoFuncao===============\n";}

}

// Parametros → ( DeclaraIdentificador )
// Parametros →
void Parametros(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============Parametros=============== \n";}


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

    switch(token) {
        case INTEIRO: 
            eat(INTEIRO,token,lineTokens, posi);
        break;
        case REAL: 
            eat(REAL,token,lineTokens, posi);
        break;
        case CARACTERE: 
            eat(CARACTERE,token,lineTokens, posi);
        break;
        case LOGICO: 
            eat(LOGICO,token,lineTokens, posi);
        break;
        case IDENTIFICADOR: 
            eat(IDENTIFICADOR,token,lineTokens, posi);
        break;
        default: 
            std::string recived = getTokenName(token);
            std::string errMsg = "ERRO SINTATICO EM: " + recived + "ERRO PADRAO";
            error(errMsg); 
        break;
    }
    posiAll++;
    if(printDebug){ std::cout <<  "===============FIM-TipoBasico=============== \n";}
}