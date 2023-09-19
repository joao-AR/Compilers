%{
#include <stdio.h>
#include <string.h>

int line = 1;
int column = 1;
int total_lines = 1;
int comment_begin_line = 0;
int comment_begin_colon = 0;

void incColumn(char* str){
    size_t stringSize = strlen(str);
    column = column + stringSize;
}


%}
%option noyywrap
%x comment
%x string
%%

"void" { printf("VOID \n"); incColumn(yytext);}
"int" {printf("INT\n");incColumn(yytext);}
"char" {printf("CHAR\n");incColumn(yytext);}

"return" {printf("RETURN\n");incColumn(yytext);}
"break" {printf("BREAK\n");incColumn(yytext);}
"switch" {printf("SWITCH\n");incColumn(yytext);}
"case" {printf("CASE\n");incColumn(yytext);}
"default" {printf("DEFAULT\n");incColumn(yytext);}
"do" {printf("DO\n");incColumn(yytext);}
"while" {printf("WHILE\n");incColumn(yytext);}
"for" {printf("FOR\n");incColumn(yytext);}
"if" { printf("IF\n"); incColumn(yytext);}
"else" {printf("ELSE\n");incColumn(yytext);}
"typedef" {printf("TYPEDEF\n");incColumn(yytext);}
"struct" {printf("STRUCT\n");incColumn(yytext);}

"+" {printf("PLUS\n");incColumn(yytext);}
"-" {printf("MINUS\n");incColumn(yytext);}
"*" {printf("MULTIPLY\n");incColumn(yytext);}
"/" {printf("DIV\n");incColumn(yytext);}
"%" {printf("REMAINDER\n");incColumn(yytext);}
"++" {printf("INC\n");incColumn(yytext);}
"--" {printf("DEC\n");incColumn(yytext);}

"&" {printf("BITWISE_AND\n");incColumn(yytext);}
"|" {printf("BITWISE_OR\n");incColumn(yytext);}
"~" {printf("BITWISE_NOT\n");incColumn(yytext);}
"^" {printf("BITWISE_XOR\n");incColumn(yytext);}
"!" {printf("NOT\n");incColumn(yytext);}
"&&" {printf("LOGICAL_AND\n");incColumn(yytext);}
"||" {printf("LOGICAL_OR\n");incColumn(yytext);}
"==" {printf("EQUAL\n");incColumn(yytext);}
"!=" {printf("NOT_EQUAL\n");incColumn(yytext);}
"<" {printf("LESS_THAN\n");incColumn(yytext);}
">" {printf("\n");incColumn(yytext);}
"" {printf("GREATER_THAN\n");incColumn(yytext);}
"<=" {printf("LESS_EQUAL\n");incColumn(yytext);}
">=" {printf("GREATER_EQUAL\n");incColumn(yytext);}
">>" {printf("R_SHIFT\n");incColumn(yytext);}
"<<" {printf("L_SHIFT\n");incColumn(yytext);}
"=" {printf("ASSIGN\n");incColumn(yytext);}
"+=" {printf("ADD_ASSIGN\n");incColumn(yytext);}
"-=" {printf("MINUS_ASSIGN\n");incColumn(yytext);}
";" {printf("SEMICOLON\n");incColumn(yytext);}
"," {printf("COMMA\n");incColumn(yytext);}
":" {printf("COLON\n");incColumn(yytext);}

"(" { printf("L_PAREN\n"); incColumn(yytext);}
")" {printf("R_PAREN\n");incColumn(yytext);}
"{" {printf("L_CURLY_BRACKET\n");incColumn(yytext);}
"}" {printf("R_CURLY_BRACKET\n");incColumn(yytext);}
"[" {printf("L_SQUARE_BRACKET\n");incColumn(yytext);}

"]" {printf("R_SQUARE_BRACKET\n");incColumn(yytext);}
"?" {printf("TERNARY_CONDITIONAL\n");incColumn(yytext);}
"#" {printf("NUMBER_SIGN\n");incColumn(yytext);}
"->" {printf("POINTER\n");incColumn(yytext);}

"printf" {printf("PRINTF\n");incColumn(yytext);}
"scanf" {printf("SCANF\n");incColumn(yytext);}
"define" {printf("DEFINE\n");incColumn(yytext);}
"exit" {printf("EXIT\n");incColumn(yytext);}

0[xX][0-9a-fA-F]+ {printf("NUM_HEXA(%s)\n",yytext);incColumn(yytext); }
0[1-7][0-7]* {printf("NUM_OCTAL(%s)\n", yytext); incColumn(yytext);}  


[0-9]+ {printf("NUM_INTEGER(%s)\n",yytext);  incColumn(yytext);}
[_a-zA-Z]+[_a-zA-Z0-9]* {printf("IDENTIFIER(%s)\n",yytext);incColumn(yytext);}
[\n] {line++; column = 1;}
[\t] {/*iguinoara tabulação */}

"//".* {printf("comment\n"); line++;}
"/*" {
    incColumn(yytext);
    comment_begin_line = line; 
    comment_begin_colon = column - 2; 
    BEGIN(comment);
    }

<comment>"*"+"/" {
    incColumn(yytext);
    comment_begin_line = 0; 
    comment_begin_line = 0; 
    BEGIN(INITIAL);}
<comment>. {incColumn(yytext);}
<comment>\n {incColumn(yytext); line++; column = 1;}

["] {
    BEGIN(string); 
    printf("STRING(");
}
<string>["] {
    incColumn(yytext); 
    printf(")\n"); 
    BEGIN(INITIAL);
}
<string>([^\\\"]|\\.)* { incColumn(yytext); printf("%s", yytext);}


.   { printf("error:lexical:%d:%d: %s\n",line,column,yytext); incColumn(yytext);}

%%

int main() {
    yylex();
    if(comment_begin_line != 0){
		printf("error:lexical:%d:%d: unterminated comment\n", comment_begin_line, comment_begin_colon);
	}
    return 0;
}
