#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include <string>
#include <algorithm>  // Para a função std::find
int getNovoEstadoAtual(int linhaEstado,int colunaEntrada,int automato [][11]);

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


bool verificaAceito(char c){
    if(c == '+'|| c == '-' || isNumero(c)|| isletrasAceitas(c)){
        return true;
    }else{
        return false;
    }
}
void analisadorLexico(std::string stingEntrada,int automato [][11], bool haveNextLine){
    std::cout << "\n";
    int estadosFinais[] = {3,6,8,10,13,14,15,16,17,18,19,22};

    int posiString = 0;
    size_t tamanhoEntrada = stingEntrada.size();
    
    std::string auxSaida = "";
    std::string saidaFinal = "";
    
    int currentState = 1;
    int lastFinal = 0;
    char ultimoChar;
    bool isAceito;
    bool isEstadoFinal;
    bool novaLetra = true;
    int colunaEntrada;

    while(posiString <= tamanhoEntrada){
        ultimoChar = stingEntrada[posiString];
        isAceito = verificaAceito(ultimoChar);

        if(isAceito && ultimoChar != ' ' ){
            // std::cout << "curretState >> " << currentState << "\n";
            // std::cout << "ultimoChar >> " << ultimoChar << "\n";
            
            colunaEntrada = getColunaEntrada(ultimoChar);
            currentState = getNovoEstadoAtual(currentState,colunaEntrada,automato);
            
            isEstadoFinal = std::find(std::begin(estadosFinais), std::end(estadosFinais), currentState) != std::end(estadosFinais);
            lastFinal = isEstadoFinal ? currentState : lastFinal;
            
            auxSaida = novaLetra ? auxSaida + stingEntrada[posiString] : auxSaida;

            if(currentState == 0 && lastFinal != 0){
                std::cout << "saidaFinal " << saidaFinal << " lastFinal " << lastFinal << "\n";

                auxSaida = ultimoChar;
                saidaFinal = "";
                currentState = 1;
                lastFinal = 0;
                novaLetra = false;
            }else if(posiString+1 == tamanhoEntrada){
                if(lastFinal != 0 ){
                    saidaFinal = auxSaida;
                    std::cout << "saidaFinal " << saidaFinal << " lastFinal " << lastFinal << "\n";
                }else{
                    std::cout << "ERRO";
                }
                break;
            }else{
                saidaFinal = auxSaida;
                novaLetra = true;
                posiString++;
            }
            
        }else{
            novaLetra = true;
            saidaFinal = auxSaida;
            posiString++;
        }
    }
}


int main(){
    // entradasAceitas = "+","-","0-9","a","c","e","h","i","r","s","t" 
    
    // MAIS  = 17
    
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
                std::cout << "Erro de leitura ou final do arquivo." << std::endl;
                break;
            }
    }


    return 0; 
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
