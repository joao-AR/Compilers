#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find

int getNovoEstadoAtual(int linhaEstado,int colunaEntrada,int automato [][11]);
std::string getPalavra(std::string stingEntrada,int &posiString, int tamanhoEntrada);
void verificaPalavraAceita(std::string palavra,int automato [][11]);

bool isNumero(char entrada);
bool isletrasAceitas(char c);
bool isCharAceita(char c);

int getColunaEntrada(char c);

void analisadorLexico(std::string stingEntrada,int automato [][11], bool haveNextLine);

void resetEstados(std::string &auxSaida,std::string &saida,int &currentState,int &lastFinal,bool &novaLetra,char c ,int tipoReset);

void imprimeSaida(std::string saida,int lastFinal);
void imprimeToken (int lastFinal);

int main(){
    // entradasAceitas = "+","-","0-9","a","c","e","h","i","r","s","t" 
    int automato [][11] = {
    /*estado 0*/ {0,0,0,0,0,0,0,0,0,0,0},
    /*estado 1*/ {17,18,19,0,11,0,2,0,0,4,0},
    /*estado 2*/ {0,0,0,0,0,3,0,7,0,0,0},
    /*estado 3*/ {0,0,0,0,0,0,0,0,9,0,0},
    /*estado 4*/ {0,0,0,0,0,0,5,0,0,0,0},
    /*estado 5*/ {0,0,0,0,0,6,0,0,0,0,0},
    /*estado 6*/ {0,0,0,0,0,0,0,0,0,0,0},
    /*estado 7*/ {0,0,0,0,0,0,0,0,0,8,0},
    /*estado 8*/ {0,0,0,0,0,0,0,0,0,0,0},
    /*estado 9*/ {0,0,0,0,0,0,0,0,0,10,0},
    /*estado 10*/{0,0,0,0,0,0,0,0,0,0,0},
    /*estado 11*/{0,0,0,12,0,0,0,0,0,0,0},
    /*estado 12*/{0,0,0,0,0,0,0,0,14,0,13},
    /*estado 13*/{0,0,0,0,0,0,0,0,0,15,0},
    /*estado 14*/{0,0,0,0,0,0,0,0,0,16,0},
    /*estado 15*/{0,0,0,0,0,0,0,0,0,0,0},
    /*estado 16*/{0,0,0,0,0,0,0,0,0,0,0},
    /*estado 17*/{0,0,0,0,0,0,0,0,0,0,0},
    /*estado 18*/{0,0,0,0,0,0,0,0,0,0,0},
    /*estado 19*/{0,0,19,0,0,20,0,0,0,0,0},
    /*estado 20*/{21,21,22,0,0,0,0,0,0,0,0},
    /*estado 21*/{0,0,22,0,0,0,0,0,0,0,0},
    /*estado 22*/{0,0,22,0,0,0,0,0,0,0,0},
    };

    std::string linha;
    bool haveNextLine;
        while (true) {
            // Tenta ler uma linha da entrada padrão
            if (std::getline(std::cin, linha)) {
                // verificar se tem mais linhas 

                haveNextLine = std::cin.peek() != EOF ?  haveNextLine = true : haveNextLine = false;

                // chamar a funcão que vai andar pelo automato
                analisadorLexico(linha,automato,haveNextLine);
                // Verifica se há mais uma linha disponível
                
            } else {
                //std::cout << "Erro de leitura ou final do arquivo." << std::endl;
                break;
            }
    }


    return 0; 
}

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

bool isNumero(char entrada){
    if(entrada == '0' || entrada == '1' || entrada == '2' ||  entrada == '3' ||entrada == '4'  || entrada == '5' || entrada == '6' ||  entrada == '7' || entrada == '8' || entrada == '9' ){
        return true;
    }    
    return false;
}

bool isletrasAceitas(char c){
    char letrasAceitas[] = {'a','c','e','h','i','r','s','t'}; 
    bool isAceita = std::find(std::begin(letrasAceitas), std::end(letrasAceitas), c) != std::end(letrasAceitas);
    return isAceita;
}

bool isCharAceita(char c){
    if(c == '+'|| c == '-' || isNumero(c)|| isletrasAceitas(c)){
        return true;
    }else{
        return false;
    }
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

void verificaPalavraAceita(std::string palavra,int automato [][11]){
    int estadosFinais[] = {3,6,8,10,13,14,15,16,17,18,19,22};

    int tamanhoPalavra = palavra.size();
    int posi = 0;
    
    std::string auxSaida = "";
    std::string saida = "";

    int colunaEntrada;
    int currentState = 1;
    int lastFinal = 0;

    bool isEstadoFinal;
    bool novaLetra = true;
    
    while(posi <= tamanhoPalavra){
        if(isCharAceita(palavra[posi])){
            //std::cout << palavra[posi] << " << c \n";
            colunaEntrada = getColunaEntrada(palavra[posi]);
            currentState = getNovoEstadoAtual(currentState,colunaEntrada,automato);
            
            isEstadoFinal = std::find(std::begin(estadosFinais), std::end(estadosFinais), currentState) != std::end(estadosFinais);
            lastFinal = isEstadoFinal ? currentState : lastFinal;
            
            auxSaida = novaLetra ? auxSaida + palavra[posi] : auxSaida;

            if(currentState == 0 && lastFinal != 0){
                imprimeSaida(saida,lastFinal);
                resetEstados(auxSaida,saida,currentState,lastFinal,novaLetra,palavra[posi],0);
                
            }else if(currentState == 0 && lastFinal == 0){
                std::cout << "ERRO\n";
                resetEstados(auxSaida,saida,currentState,lastFinal,novaLetra,palavra[posi],1);
                
            }else{
                saida = auxSaida;
                novaLetra = true;
                posi++;
            }
            
        }else{
            if(posi == tamanhoPalavra){ 
                currentState = 0 ;
                if(currentState == 0 && lastFinal != 0){
                    imprimeSaida(saida,lastFinal);
                    break;
                }
                
            }else{
                std::cout << "ERRO\n";
                novaLetra = true;
                saida = auxSaida;
                auxSaida = "";  
            }
            posi++;
        }
        
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

void imprimeSaida(std::string saida,int lastFinal){
    imprimeToken(lastFinal);
    if(lastFinal == 19 || lastFinal == 22){
        std::cout << saida << "\n";
    }else{
        std::cout << "\n";
    }
}   

void imprimeToken (int lastFinal){
        // int estadosFinais[] = {3,6,8,10,13,14,15,16,17,18,19,22};

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