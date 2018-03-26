%{
    #include <stdio.h>
    void yyerror(char *);
%}
%option yylineno
%%
[ \t]+ ;

R[0-9]+ { printf("%s",yytext); }
C[0-9]+ { printf("%s",yytext); }
L[0-9]+ { printf("%s",yytext); }
V[0-9]+ { printf("%s",yytext); }
I[0-9]+ { printf("%s",yytext); }

.   { ; }

%%

int yywrap(void) {
    return 1;
}

int main(int argc, char* argv[]){
    yyin = fopen(argv[1], "r"); // input file for lex is yyin and is stdin by default
    yylex();
    fclose(yyin);
}
