%{
#include <stdio.h>
%}
%option noyywrap
%%

"aba"+   { printf("%s (action 1)\n",yytext); }
(a(b)*a) { printf("%s (action 2)\n",yytext); }
(a|b)    { printf("%s (action 3)\n",yytext); }
.        { /* Ignorar outros caracteres */ }

%%

int main() {
    yylex();
    return 0;
}
