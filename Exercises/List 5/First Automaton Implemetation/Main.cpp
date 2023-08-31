#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include<string>
#include <algorithm>  // Para a função std::find

bool isLetra(char caractere);
bool isNumero(char entrada);
bool isEntradaAceita(char entrada);
int getColunaEntrada(char entrada);
void printResultado(std::string saida, int lastFinal);
bool erro(int &lastFinal,std::string &saida, int &currentState, int &posiNaEntrada, std::string &auxSaida, char &ultimoCaractere, int tamanhoEntrada,std::string entrada);
void resetAutomato(int &lastFinal, int &currentState, std::string &auxSaida, char ultimoCaractere){
    lastFinal  = 0; 
    currentState = 1;
    auxSaida = ultimoCaractere;
}
int main(){
    
    // std::string entradasAceitas[] = {"+","-","a-z","0-9","e"};
    
    int automato [][5] = {
    /*estado 0*/ {0,0,0,0,0},
    /*estado 1*/ {3,4,2,5,0},
    /*estado 2*/ {0,0,2,2,0},
    /*estado 3*/ {0,0,0,0,0},
    /*estado 4*/ {0,0,0,0,0},
    /*estado 5*/ {0,0,0,5,6},
    /*estado 6*/ {7,7,0,8,0},
    /*estado 7*/ {0,0,0,8,0},
    /*estado 8*/ {0,0,0,8,0},
    };


    int estadosFinais[] = {2,3,4,5,8};
    std::string entrada;
    entrada = "+-abcabc @abcfgh";
    
    // std::cout << "Digite a sua entrada >> ";
    // std::getline(std::cin,entrada);
    
    std::string saida;
    std::string auxSaida;
    // valores iniciais
    int  lastFinal  = 0; 
    int  currentState = 1;

    bool isAceito = false;
    bool isEstadoFinal;
    bool novaLetra = true;
    bool stop = false;
    size_t tamanhoEntrada = entrada.size();
    int posiNaEntrada = 0;
    

    while(posiNaEntrada <= tamanhoEntrada){
        auxSaida = novaLetra ? auxSaida + entrada[posiNaEntrada] : auxSaida;

        char ultimoCaractere = auxSaida.back();
        isAceito = isEntradaAceita(ultimoCaractere);
        
        while (isAceito != true){
            isAceito = isEntradaAceita(ultimoCaractere);
            if(!isAceito ){ 
            stop = erro(lastFinal,saida,currentState,posiNaEntrada,auxSaida,ultimoCaractere,tamanhoEntrada,entrada);  
            if(stop){break;}
            }
        }
    
        int colunaEntrada = getColunaEntrada(ultimoCaractere);
        
        if(isAceito ){    
            currentState = automato [currentState][colunaEntrada];
        }

        isEstadoFinal = std::find(std::begin(estadosFinais), std::end(estadosFinais), currentState) != std::end(estadosFinais);
        lastFinal = isEstadoFinal ? currentState : lastFinal;

        if(isAceito && currentState == 0 && lastFinal !=0){
                printResultado(saida, lastFinal);
                auxSaida = ultimoCaractere;
                resetAutomato(lastFinal,currentState,auxSaida, ultimoCaractere);
                novaLetra = false;
            }else if( posiNaEntrada == tamanhoEntrada && isAceito){
                saida = auxSaida;
                printResultado(saida, lastFinal); // imprime a ultima entrada reconhecido 
                break;
            }else if(lastFinal != 0 && currentState != 0 ){
                saida = auxSaida;
                novaLetra = true;
                posiNaEntrada++;
            }

        if(lastFinal == 0 && currentState == 0){ // verificação de erro caso a primeira entrada não seja aceita 
            stop = erro(lastFinal,saida,currentState,posiNaEntrada,auxSaida,ultimoCaractere,tamanhoEntrada,entrada);  
            if(stop){
                break;
            }
            novaLetra = false;
        }
    }

    return 0; 
}


bool isLetra(char caractere){
    if(
           caractere == 'a' || caractere == 'b' || caractere == 'c'||  caractere == 'd'
        || caractere == 'f' || caractere == 'g'||  caractere == 'h'
        || caractere == 'i' || caractere == 'j' || caractere == 'k'||  caractere == 'l'
        || caractere == 'm' || caractere == 'n' || caractere == 'o'||  caractere == 'p'
        || caractere == 'q' || caractere == 'r' || caractere == 's'||  caractere == 't'
        || caractere == 'u' || caractere == 'v' || caractere == 'w'||  caractere == 'x' 
        || caractere == 'y' || caractere == 'z'){
        return true;
    }
    return false;
}

bool isNumero(char entrada){
    if(entrada == '0' || entrada == '1' || entrada == '2' ||  entrada == '3' ||entrada == '4'  || entrada == '5' || entrada == '6' ||  entrada == '7' || entrada == '8' || entrada == '9' ){
    return true;
    }    
    return false;
}

int getColunaEntrada(char entrada){
    if(entrada == '+'){
        return 0;
    }else if(entrada == '-'){
        return 1;
    }else if(entrada == 'e'){
        return 4;
    }else if(isLetra(entrada)){
        return 2;
    }else if(isNumero(entrada)){
        return 3;
    }
}

bool isEntradaAceita(char entrada){
    if(entrada == '+'){
        return true;
    }else if(entrada == '-'){
        return true;
    }else if(entrada == 'e'){
        return true;
    } else if(isLetra(entrada)){
        return true;
    }else if(isNumero(entrada)){
        return true;
    }
    return false;
}

void printResultado(std::string saida, int lastFinal){
    if(saida != " "){
        std::cout << "Entrada > "; 
        std::cout << saida;
        std::cout << " < Reconhecida no estado "; 
        std::cout << lastFinal; 
        std::cout << "\n ";
    }
}

bool erro(int &lastFinal,std::string &saida, int &currentState, int &posiNaEntrada, std::string &auxSaida, char &ultimoCaractere, int tamanhoEntrada,std::string entrada){
            if(lastFinal != 0){printResultado(saida, lastFinal);}
            // imprimir a string aceita anterior ao erro 
            if(posiNaEntrada >= tamanhoEntrada){ // erro imprimir erro  no fim ao final da string
                return true;
            }
            std::cout << "ERRO";
            std::cout << "\n";
            
            saida = "";
            lastFinal = 0; 
            currentState = 1;
            posiNaEntrada++;
            auxSaida = entrada[posiNaEntrada];
            ultimoCaractere = auxSaida.back();
            
            return false;
}
