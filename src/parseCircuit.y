%{
    #include <stdio.h>
    #include "src/parse.h"
    void yyerror(char *);

    extern "C" int yylex();
    extern "C" FILE *yyin;

    vector <element> circuitElements;
    vector <source> sourceElements;
    element tempE;
    source tempS;
%}

%union{
    int num;
    double dec;
    char* ch;
}
%token <ch> ELEMENT_TOKEN
%token <ch> SOURCE_TOKEN
%token <num> ELEMENT_NUM_TOKEN
%token <num> SOURCE_NUM_TOKEN
%token <ch> NET_START_TOKEN
%token <num> NET_START_NUM_TOKEN

%%

circuit:
            connection circuit
            | connection
connection:
            ELEMENT_TOKEN ELEMENT_NUM_TOKEN { tempE.elementName = $1; tempE.elementNum = $2; }
            | SOURCE_TOKEN SOURCE_NUM_TOKEN { tempS.sourceName = $1; tempS.sourceNum = $2; }
%%
void yyerror(char *s){
    extern int yylineno;
    fprintf(stderr, "Line Number %d: %s\n",yylineno, s);
}

int main(int argc, char** argv){
    yyin = fopen(argv[1], "r");
    yyparse();
    printf("%s->%d\n",tempE.elementName,tempE.elementNum);
    printf("%s->%d\n",tempS.sourceName,tempS.sourceNum);
    fclose(yyin);
}
