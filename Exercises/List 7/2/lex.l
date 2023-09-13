%{
#include <stdio.h>
%}

%option noyywrap

DIGIT [0-9]
LETTER [a-zA-Z]
ID ({LETTER}({LETTER}|{DIGIT})*)
NUM {DIGIT}+
REAL ({NUM}"."{DIGIT}*|{DIGIT}*"."{DIGIT}+)
IF "if"
COMMENT "--"({LETTER})*"\n"

%%

{IF}   { printf("%s IF\n",yytext); }
{ID}   { printf("%s ID\n",yytext); }
{REAL} { printf("%s REAL\n",yytext); }
{NUM}  { printf("%s NUM\n",yytext); }
{COMMENT} { 
    yytext[yyleng-1] = '\0';
    printf("%s COMMENT\n",yytext); 
}
"." | "-" { printf("error\n",); }
[ \t]  { printf("white space\n"); }
[\n] { /* Ignorar espaços em branco e tabulações */ }

. { printf("%s error\n",yytext); }

%%

int main() {
    yylex();
    return 0;
}
