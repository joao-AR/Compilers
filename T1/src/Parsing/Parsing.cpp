#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
#include "../h/Automaton.h"
#include "../h/Parsing.h"

const bool printDebug = true;
int err = 0;
const int INTEIRO = 81;
const int REAL = 126;
const int CARACTERE = 43;
const int LOGICO = 95;
const int PV =  35; // ;
const int PROCEDIMENTO = 123;
const int FUNCAO = 71;
const int ALGORITIMO = 26;
const int IDENTIFICADOR = 18;
const int DP = 11;
const int PONTO = 12;
const int AP = 160;
const int FP = 161 ;
void Programa(int &token, std::vector<int> lineTokens,int &posi);

void parsing(std::string inputString,int automaton [][ALPHABET_LENGTH], bool haveNextLine,int &linePosi,int &columnPosi){

    size_t inputStrSize = inputString.size();
    std::string word = "";
    bool wordAccepted = false;
    int posiString = 0;
    int posiLineTokens;
    std::vector<int> lineTokens;

    while(posiString <= inputStrSize){
        word = getWord(inputString,posiString,inputStrSize,columnPosi);
        getLineTokens(word,automaton,lineTokens);
        posiString++;
    }

    Programa(lineTokens[0],lineTokens,posiLineTokens);
    // if(err == 0 ){
    //     std::cout << "CADEITA ACEITA";
    // }
    // err = 0; // reset no erro para proxima linha
    std::cout << "\n";
    for (int i = 0; i < lineTokens.size(); i++) {
        std::cout << lineTokens[i] << " ";
    }
    std::cout << "\n";
}

std::string getTokenName(int token){
    std::unordered_map<int, std::string> numTokenName = {
        {2,"IDENTIFICADOR"},
        {4,"IDENTIFICADOR"},
        {3,"NINTEIRO"},
        {5,"IDENTIFICADOR"},
        {6,"E"},
        {7,"MAIS"},
        {8,"IDENTIFICADOR"},
        {9,"IDENTIFICADOR"},
        {10,"IDENTIFICADOR"},
        {11,"DP"},
        {12,"PONTO"},
        {13,"IGUAL"},
        {14,"IDENTIFICADOR"},
        {15,"IDENTIFICADOR"},
        {16,"IDENTIFICADOR"},
        {17,"IDENTIFICADOR"},
        {18,"IDENTIFICADOR"}, 
        {26,"ALGORITIMO"},
        {28,"ATE"}, 
        {31,"NREAL"},
        {32,"MENOS"},
        {33,"ASTERISCO"},
        {34,"BARRA"},
        {35,"PV"},
        {43,"CARACTERE"}, 
        {44,"DE"},
        {46,"DIV"}, 
        {53,"ENQUANTO"}, 
        {56,"ENTAO"},
        {57,"IDENTIFICADOR"},
        {60,"FACA"}, 
        {63,"FALSO"},
        {64,"VIRGULA"},
        {66,"FIM"},
        {71,"FUNCAO"} ,
        {76,"INICIO"},
        {81,"INTEIRO"},
        {87,"IMPRIMA"},
        {90,"LEIA"},
        {95,"LOGICO"}, 
        {100,"MATRIZ"},
        {101,"IDENTIFICADOR"},
        {103,"NAO"},
        {104,"IDENTIFICADOR"},
        {105,"OU"},
        {106,"IDENTIFICADOR"},
        {109,"PARA"},
        {112,"PASSO"},
        {123,"PROCEDIMENTO"},
        {126,"REAL"},
        {130,"REPITA"},   
        {131,"SE"},
        {134,"SENAO"},
        {137,"TIPO"},
        {146,"VERDADEIRO"},
        {154,"VARIAVEIS"}, 
        {157,"VETOR"}, 
        {158,"AC"},
        {159,"FC"}, 
        {160,"AP"},
        {161,"FP"},
        {162,"MENOR"},
        {163,"DIFERENTE"},  
        {164,"MENORIGUAL"},
        {165,"ATRIBUICAO"},
        {166,"MAIOR"},  
        {167,"MAIORIGUAL"},
        {173,"STRING"},
    };
    return numTokenName[token];
}

void getLineTokens(std::string word,int automaton [][ALPHABET_LENGTH],std::vector<int> &lineTokens){
    int finalStates[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,26,28,31,32,33,34,35,43,44,46,53,56,57,60,63,64,66,71,76,81,87,90,95,100,101,103,104,105,106,109,112,123,126,130,131,134,137,146,154,157,158,159,160,161,162,163,164,165,166,167,168,170,171,172,173};

    int wordSize = word.size();
    int posi = 0;
    std::string auxOutput = "";
    std::string output = "";

    int inputColumn;
    int currentState = 1;
    int lastFinal = 0;
    
    bool isFinalState;
    bool newWord = true;

    while(posi <= wordSize){        
        inputColumn = getInputColumn(word[posi]);
        currentState = getNewCurrentState(currentState,inputColumn,automaton);
        
        isFinalState = std::find(std::begin(finalStates), std::end(finalStates), currentState) != std::end(finalStates);
        lastFinal = isFinalState ? currentState : lastFinal;
        
        auxOutput = newWord ? auxOutput + word[posi] : auxOutput;
        // 170 e 172 são comentarios e serão ignorados
        if(currentState == 0 && lastFinal != 0 && lastFinal != 170 && lastFinal != 172 ){
            lineTokens.push_back(lastFinal);
            resetStates(auxOutput,output,currentState,lastFinal,newWord,word[posi],0);
        }else{
            output = auxOutput;
            newWord = true;
            posi++;
        }
    }

}

void error(std::string errMsg){
    if(err == 0){
        std::cout << errMsg <<"\n";
        err = 1;
    }
}

// Pega o proximo token no vetor
int getToken(std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============GETTOKEN=============== \n";}
    posi++; // vai para a proxima posi do vetor
    std::cout << "lineTokens[posi] ->" << posi <<"\n";
    if(printDebug){ std::cout <<  "===============FIM-GETTOKEN=============== \n";}
    return lineTokens[posi];
}

// Vai retornar o Proximo Token do vetor de tokens 
int advance(std::vector<int>  lineTokens,int &posiLineTokens) {
    if(printDebug){ std::cout <<  "===============ADVANCE=============== \n";}
    int token = getToken(lineTokens,posiLineTokens);
    if(printDebug){ std::cout <<  "===============FIM_ADVANCE=============== \n";}
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
        std::string errMsg = "ERRO SINTATICO EM: " + recived + " ESPERADO: "+ expected;
        error(errMsg);
        return;
    }

    if(printDebug){ std::cout <<  "===============FIM-EAT=============== \n";}

}


//Programa → algoritmo identificador ; BlocoVariaveis ProcedimentoFuncao BlocoComandos .
void BlocoVariaveis(int &token, std::vector<int> lineTokens,int &posi){}
void BlocoComandos(int &token, std::vector<int> lineTokens,int &posi){}

void ProcedimentoFuncao(int &token, std::vector<int> lineTokens,int &posi);

void DeclaraProcedimento(int &token, std::vector<int> lineTokens,int &posi);
void DeclaraFuncao(int &token, std::vector<int> lineTokens,int &posi);
void TipoBasico(int &token, std::vector<int> lineTokens,int &posi);
void DeclaraVariaveis(int &token, std::vector<int> lineTokens,int &posi);
void DeclaraParametrosDeclaracoes(int &token, std::vector<int> lineTokens,int &posi);
void Parametros (int &token, std::vector<int> lineTokens,int &posi);

void Programa(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "\n===============PROGRAMA=============== \n";}
    
    eat(ALGORITIMO,token,lineTokens, posi);
    // eat(IDENTIFICADOR,token,lineTokens, posi); 
    // eat(PV,token,lineTokens, posi); // ;
    // // BlocoVariaveis();
    // ProcedimentoFuncao(token,lineTokens, posi);
    // // BlocoComandos();
    // eat(PONTO,token,lineTokens, posi); 

    if(printDebug){ std::cout <<  "==============FIM-PROGRAMA===============\n";}
}

// ProcedimentoFuncao → DeclaraProcedimento ProcedimentoFuncao
// ProcedimentoFuncao → DeclaraFuncao ProcedimentoFuncao
// ProcedimentoFuncao →
void ProcedimentoFuncao(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============ProcedimentoFuncao=============== \n";}
    
    switch(token) {
        case PROCEDIMENTO: 
            // DeclaraProcedimento(token,lineTokens, posi);
            // ProcedimentoFuncao(token,lineTokens, posi);
        break;
    
        // case FUNCAO: 
        //     DeclaraFuncao(token,lineTokens, posi);
        //     ProcedimentoFuncao(token,lineTokens, posi);
        //     break;
        default: // vazio
            // std::string recived = getTokenName(token);
            // std::string errMsg = "ERRO SINTATICO EM: " + recived + "ERRO PADRAO";
            // error(errMsg); 
            break;
    }

    if(printDebug){ std::cout <<  "==============FIM-ProcedimentoFuncao===============\n";}

}
// DeclaraProcedimento → procedimento identificador Parametros ; DeclaraParametros BlocoVariaveis BlocoComandos ;
void DeclaraProcedimento(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============DeclaraProcedimento=============== \n";}
    eat(PROCEDIMENTO,token,lineTokens, posi);
    eat(IDENTIFICADOR,token,lineTokens, posi);
    Parametros(token,lineTokens, posi);
    eat(PV,token,lineTokens, posi);
    DeclaraParametrosDeclaracoes(token,lineTokens, posi);
    BlocoVariaveis(token,lineTokens, posi);
    BlocoComandos(token,lineTokens, posi);
    eat(PV,token,lineTokens, posi);
    if(printDebug){ std::cout <<  "===============FIM-DeclaraProcedimento=============== \n";}
}

// Parametros → ( DeclaraIdentificador )
// Parametros →
void Parametros(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============Parametros=============== \n";}

    switch(token) {
        case AP: 
            eat(AP,token,lineTokens, posi);// (
            // DeclaraIdentificador(token,lineTokens, posi);
            eat(FP,token,lineTokens, posi);// )
        break;
        default: // vazio
            // std::string recived = getTokenName(token);
            // std::string errMsg = "ERRO SINTATICO EM: " + recived + "ERRO PADRAO";
            // error(errMsg); 
        break;
    }

    if(printDebug){ std::cout <<  "===============FIM-Parametros=============== \n";}
}

// DeclaraParametros → Declaracoes
// DeclaraParametros →
// Declaracoes → DeclaraVariaveis
// Declaracoes → DeclaraTipo
// Declaracoes → DeclaraVariaveis Declaracoes
// Declaracoes → DeclaraTipo Declaracoes
void DeclaraParametrosDeclaracoes(int &token, std::vector<int> lineTokens,int &posi){ // junção dos dois
    if(printDebug){ std::cout <<  "===============DeclaraParametrosDeclaracoes=============== \n";}

    if(token == INTEIRO || token == REAL ||  token == CARACTERE ||token ==  LOGICO || token == IDENTIFICADOR){
            DeclaraVariaveis(token,lineTokens, posi);
    }else{
        // std::string recived = getTokenName(token);
        // std::string errMsg = "ERRO SINTATICO EM: " + recived + "ERRO PADRAO";
        // error(errMsg); 
    }
    if(printDebug){ std::cout <<  "===============FIM-DeclaraParametrosDeclaracoes=============== \n";}
}

//DeclaraVariaveis → TipoBasico : DeclaraIdentif icador ;
void DeclaraVariaveis(int &token, std::vector<int> lineTokens,int &posi){
    if(printDebug){ std::cout <<  "===============DeclaraVariaveis=============== \n";}

    if(token == INTEIRO || token == REAL ||  token == CARACTERE ||token ==  LOGICO || token == IDENTIFICADOR){
        TipoBasico(token,lineTokens, posi);
        eat(DP,token,lineTokens, posi);//:
        eat(PV,token,lineTokens, posi);//;
    }else{
        // std::string recived = getTokenName(token);
        // std::string errMsg = "ERRO SINTATICO EM: " + recived + "ERRO PADRAO";
        // error(errMsg);
        // exit(1); 
    }
    if(printDebug){ std::cout <<  "===============FIM-DeclaraVariaveis=============== \n";}
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
    if(printDebug){ std::cout <<  "===============FIM-TipoBasico=============== \n";}
}