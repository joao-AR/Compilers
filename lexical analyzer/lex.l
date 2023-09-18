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
%%

"void" { printf("VOID \n"); incColumn(yytext);}

"if" { printf("IF\n"); incColumn(yytext);}

"(" { printf("L_PAREN\n"); incColumn(yytext);}
")" {printf("R_PAREN\n");incColumn(yytext);}

"{" {printf("L_CURLY_BRACKET\n");incColumn(yytext);}
"}" {printf("R_CURLY_BRACKET\n");incColumn(yytext);}

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

.   { printf("error:lexical:%d:%d: %s\n",line,column,yytext); incColumn(yytext);}

%%

int main() {
    yylex();
    if(comment_begin_line != 0){
		printf("error:lexical:%d:%d: unterminated comment\n", comment_begin_line, comment_begin_colon);
	}
    return 0;
}
