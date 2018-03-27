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
%token <ch> NET_TOKEN
%token <num> NET_NUM_TOKEN
%token <num> NET_ZERO
%token <num> ELEM_VALUE_TOKEN
%token <ch> ELEM_UNIT_TOKEN
%token <num> RESISTOR_VALUE
%token <dec> DC_OFFSET_TOK
%token <dec> AMP_TOKEN
%token <dec> FREQ_TOKEN
%token <dec> DELAY_TOK
%token <dec> DAMPING_TOK

%%

circuit:
            connection circuit
            | connection
connection:
            element elementNet elementValue
            | source sourceNet sourceValue

element:
        ELEMENT_TOKEN ELEMENT_NUM_TOKEN { tempE.elementName = $1; tempE.elementNum = $2; }

source:
        SOURCE_TOKEN SOURCE_NUM_TOKEN { tempS.sourceName = $1; tempS.sourceNum = $2; }

elementNet:
        elementNetStart elementNetEnd

elementNetStart:
        NET_TOKEN NET_NUM_TOKEN { tempE.netStart = $2; }
        | NET_ZERO  { tempE.netStart = 0; }

elementNetEnd:
        NET_TOKEN NET_NUM_TOKEN { tempE.netEnd = $2; }
        | NET_ZERO  { tempE.netEnd = 0; }

sourceNet:
        sourceNetStart sourceNetEnd

sourceNetStart:
        NET_TOKEN NET_NUM_TOKEN { tempS.netStart = $2; }
        | NET_ZERO  { tempS.netStart = 0; }
sourceNetEnd:
        NET_TOKEN NET_NUM_TOKEN { tempS.netEnd = $2; }
        | NET_ZERO  { tempS.netEnd = 0; }

elementValue:
        RESISTOR_VALUE  { if(tempE.elementName[0] == 'R'){ tempE.value = $1; tempE.unit = strdup("1"); } else { yyerror("No unit is specified, only possible for resistor.\n"); } }
        | ELEM_VALUE_TOKEN ELEM_UNIT_TOKEN    { tempE.value = $1;  tempE.unit = $2; if(tempE.elementName[0] == 'R'){ if($2[1] || ($2[0]!='K' && $2[0]!= 'N' && $2[0]!='M')) yyerror("Incorrect unit.\n"); } else if(tempE.elementName[0] == 'L') { if( ($2[1] && $2[1]!='H' && ($2[0]!='K' && $2[0]!='N' && $2[0]!='M') ) || (!$2[1] && $2[0]!='H') ) yyerror("Incorrect unit.\n"); } else if(tempE.elementName[0] == 'C'){ if( ($2[1] && $2[1]!='F' && ($2[0]!='K' && $2[0]!='N' && $2[0]!='M') ) || (!$2[1] && $2[0]!='F') ) yyerror("Incorrect unit.\n"); } }

sourceValue:
        DC_OFFSET_TOK AMP_TOKEN FREQ_TOKEN DELAY_TOK    { tempS.dcOffset = $1, tempS.amplitude = $2, tempS.freq = $3, tempS.delay = $4, tempS.dampingFactor = 0.0; }
        | DC_OFFSET_TOK AMP_TOKEN FREQ_TOKEN DELAY_TOK DAMPING_TOK  { tempS.dcOffset = $1, tempS.amplitude = $2, tempS.freq = $3, tempS.delay = $4, tempS.dampingFactor = $5; }

%%
void yyerror(char *s){
    extern int yylineno;
    fprintf(stderr, "Line Number %d: %s\n",yylineno, s);
}

int main(int argc, char** argv){
    yyin = fopen(argv[1], "r");
    yyparse();
    printf("%s->%d->NetStart:%d->NetEnd:%d->Value:%d->Unit:%s\n",tempE.elementName, tempE.elementNum, tempE.netStart, tempE.netEnd, tempE.value, tempE.unit);

    printf("%s->%d->NetStart:%d->NetEnd:%d->dcOffset:%f->Amp:%f->Freq:%f->Delay:%f->Damping:%f\n",tempS.sourceName, tempS.sourceNum, tempS.netStart, tempS.netEnd, tempS.dcOffset, tempS.amplitude, tempS.freq, tempS.delay, tempS.dampingFactor);
    fclose(yyin);
}
