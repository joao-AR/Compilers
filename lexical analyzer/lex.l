%{
#include <stdio.h>
#include <string.h>

int line = 1;
int column = 1;
int total_lines = 1;
int comment_begin_line = 0;
int comment_begin_colomn = 0;
int case_bar_n = 0;
void incColumn(char* str){
    size_t stringSize = strlen(str);
    column = column + stringSize;
}



%}
%option noyywrap
%x comment
%x string
%%

"void" { if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("VOID"); incColumn(yytext);}
"int" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("INT");incColumn(yytext);}
"char" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("CHAR");incColumn(yytext);}

"return" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("RETURN");incColumn(yytext);}
"break" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("BREAK");incColumn(yytext);}

"switch" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("SWITCH");incColumn(yytext);}
"case" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("CASE");incColumn(yytext);}
"default" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("DEFAULT");incColumn(yytext);}

"do" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("DO");incColumn(yytext);}
"while" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("WHILE");incColumn(yytext);}

"for" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("FOR");incColumn(yytext);}

"if" { if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("IF"); incColumn(yytext);}
"else" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("ELSE");incColumn(yytext);}

"typedef" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("TYPEDEF");incColumn(yytext);}
"struct" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("STRUCT");incColumn(yytext);}

"+" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("PLUS");incColumn(yytext);}
"-" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("MINUS");incColumn(yytext);}
"*" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("MULTIPLY");incColumn(yytext);}
"/" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("DIV");incColumn(yytext);}
"%" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("REMAINDER");incColumn(yytext);}
"++" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("INC");incColumn(yytext);}
"--" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("DEC");incColumn(yytext);}

"&" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("BITWISE_AND");incColumn(yytext);}
"|" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("BITWISE_OR");incColumn(yytext);}
"~" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("BITWISE_NOT");incColumn(yytext);}
"^" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("BITWISE_XOR");incColumn(yytext);}
"!" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("NOT");incColumn(yytext);}
"&&" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("LOGICAL_AND");incColumn(yytext);}
"||" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("LOGICAL_OR");incColumn(yytext);}
"==" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("EQUAL");incColumn(yytext);}
"!=" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("NOT_EQUAL");incColumn(yytext);}
"<" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("LESS_THAN");incColumn(yytext);}
">" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("GREATER_THAN");incColumn(yytext);}


"<=" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("LESS_EQUAL");incColumn(yytext);}
">=" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("GREATER_EQUAL");incColumn(yytext);}
">>" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("R_SHIFT");incColumn(yytext);}
"<<" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("L_SHIFT");incColumn(yytext);}
"=" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("ASSIGN");incColumn(yytext);}
"+=" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("ADD_ASSIGN");incColumn(yytext);}
"-=" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("MINUS_ASSIGN");incColumn(yytext);}
";" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("SEMICOLON");incColumn(yytext);}
"," {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("COMMA");incColumn(yytext);}
":" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("COLON");incColumn(yytext);}

"(" { if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("L_PAREN"); incColumn(yytext);}
")" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("R_PAREN");incColumn(yytext);}
"{" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("L_CURLY_BRACKET");incColumn(yytext);}
"}" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("R_CURLY_BRACKET");incColumn(yytext);}
"[" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("L_SQUARE_BRACKET");incColumn(yytext);}

"]" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("R_SQUARE_BRACKET");incColumn(yytext);}
"?" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("TERNARY_CONDITIONAL");incColumn(yytext);}
"#" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("NUMBER_SIGN");incColumn(yytext);}
"->" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("POINTER");incColumn(yytext);}

"printf" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; }; printf("PRINTF");incColumn(yytext);}
"scanf" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("SCANF");incColumn(yytext);}
"define" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("DEFINE");incColumn(yytext);}
"exit" {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("EXIT");incColumn(yytext);}

0[xX][0-9a-fA-F]+ {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("NUM_HEXA(%s)",yytext);incColumn(yytext); }
0[1-7][0-7]* {if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("NUM_OCTAL(%s)", yytext); incColumn(yytext);}  

" " {column++;}
(\')([^'\\]|\\.)*(\') 	{ 
    if(yyleng == 3){
        if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("CHARACTER(%c)", yytext[1]);
    }else{
        if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("CHARACTER(%c%c)", yytext[1],yytext[2]);
        }
} //Caractere

[0-9]+ { if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("NUM_INTEGER(%s)",yytext);  incColumn(yytext);}

[_a-zA-Z]+[_a-zA-Z0-9]* {
    if(strlen(yytext) <= 255){
        if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("IDENTIFIER(%s)",yytext);
    }else{
        if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };printf("error:lexical:%d:%d: identifier too long", line, column);
    }
    incColumn(yytext);
}

[\n] {line++; column = 1;}
[\t] {}// iguinorar tabulação

"//".* {
    if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; }
    line++; 
    column = 1;
}
"/*" {
    incColumn(yytext);
    comment_begin_line = line; 
    comment_begin_colomn = column - 2; 
    BEGIN(comment);
    }

<comment>"*"+"/" {
    incColumn(yytext);
    comment_begin_line = 0; 
    comment_begin_line = 0; 
    BEGIN(INITIAL);}
<comment>. {incColumn(yytext);}
<comment>\*[^*/] {
    if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };
    printf("warning:%d:%d: '/*' within block comment",line,column-1);
    incColumn(yytext);
}

<comment>"/*"[^*/]*"\n" {
    if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };
    printf("warning:%d:%d: '/*' within block comment",line,column);
    
    for(int i = 0; i < yyleng; i++){
        if(yytext[i] == '\n'){
            line++;
        }
    }
    column = 1;
}
<comment>\n { line++; column = 1;}


["] {
    if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; };
    BEGIN(string); 
    printf("STRING(");
}
<string>["] {
    incColumn(yytext); 
    printf(")");
    BEGIN(INITIAL);
}

<string>([^\\\"]|\\.)* { printf("%s", yytext); incColumn(yytext);}


. { if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; }; printf("error:lexical:%d:%d: %s",line,column +1 ,yytext); incColumn(yytext);}

%%

int main() {
    yylex();
    if(comment_begin_line != 0){
        if(case_bar_n == 1){ printf("\n"); }else{ case_bar_n = 1; }; 
		printf("error:lexical:%d:%d: unterminated comment", comment_begin_line, comment_begin_colomn);
	}
    return 0;
}
