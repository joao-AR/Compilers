%{
#include <stdio.h>
%}

%option noyywrap

%{
// Função para imprimir o nome do token
void printToken(const char* token) {
    printf("Token: %s\n", token);
}
%}

DIGIT [0-9]
LETTER [a-zA-Z]

%%

"+" {
    printf("%s\n",yytext);
}

"-" {
    printf("%s\n",yytext);
}

{LETTER}+ {
    printf("%s\n",yytext);
}

{DIGIT}* {
    printf("%s\n",yytext);
}

{DIGIT}+ {
    printf("%s\n",yytext);
}

{DIGIT}+e{DIGIT}+ {
    printf("%s\n",yytext);
}

{DIGIT}+e"+"{DIGIT}+ {
    printf("%s\n",yytext);
}

{DIGIT}+e"-"{DIGIT}+ {
    printf("%s\n",yytext);
}
[ \t\n]   ; 

. {
    printf("ERRO\n");
}

%%

int main() {
    yylex();
    return 0;
}
