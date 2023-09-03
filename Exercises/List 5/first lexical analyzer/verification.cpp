#include <iostream>
#include <cctype>  // Biblioteca para funções de caracteres
#include<string>
#include <algorithm>  // Para a função std::find

bool isLetra(char caractere){
    if(
           caractere == 'a' || caractere == 'b' || caractere == 'c'||  caractere == 'd'
        || caractere == 'e' || caractere == 'f' || caractere == 'g'||  caractere == 'h'
        || caractere == 'i' || caractere == 'j' || caractere == 'k'||  caractere == 'l'
        || caractere == 'm' || caractere == 'n' || caractere == 'o'||  caractere == 'p'
        || caractere == 'q' || caractere == 'r' || caractere == 's'||  caractere == 't'
        || caractere == 'u' || caractere == 'v' || caractere == 'w'||  caractere == 'x' 
        || caractere == 'y' || caractere == 'z'){
        return true;
    }
    return false;
}
bool isAh(char caractere){
    if( caractere == 'a' || caractere == 'b' || caractere == 'c'||  caractere == 'd'
        || caractere == 'e' || caractere == 'f' || caractere == 'g'||  caractere == 'h'){
        return true;
    }
    return false;
}

bool isJz(char caractere){
    if(
        caractere == 'j' || caractere == 'k'||  caractere == 'l'
        || caractere == 'm' || caractere == 'n' || caractere == 'o'||  caractere == 'p'
        || caractere == 'q' || caractere == 'r' || caractere == 's'||  caractere == 't'
        || caractere == 'u' || caractere == 'v' || caractere == 'w'||  caractere == 'x' 
        || caractere == 'y' || caractere == 'z'){
        return true;
    }
    return false;
}

bool isAe(char caractere){
    if( caractere == 'a' || caractere == 'b' || caractere == 'c'||  caractere == 'd'|| caractere == 'e'){
        return true;
    }
    return false;
}

bool isGz(char caractere){
    if(  caractere == 'g'||  caractere == 'h'
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

bool isEntradaAceita(char entrada){
    if(isLetra(entrada) || isNumero(entrada) || entrada == ' '){
        return true;
    }
    return false;
}