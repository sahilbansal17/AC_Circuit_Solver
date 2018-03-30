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
    bool error;
    int numErrors = 0;
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
%token <dec> ELEM_VALUE_TOKEN
%token <ch> ELEM_UNIT_TOKEN
%token <dec> RESISTOR_VALUE
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
        ELEMENT_TOKEN ELEMENT_NUM_TOKEN { error = 0; tempE.elementName = $1; tempE.elementNum = $2; }

source:
        SOURCE_TOKEN SOURCE_NUM_TOKEN { error = 0; tempS.sourceName = $1; tempS.sourceNum = $2; }

elementNet:
        elementNetStart elementNetEnd

elementNetStart:
        NET_TOKEN NET_NUM_TOKEN { tempE.netStart = $2; }
        | NET_ZERO  { tempE.netStart = 0; }

elementNetEnd:
        NET_TOKEN NET_NUM_TOKEN { tempE.netEnd = $2; if(tempE.netEnd == tempE.netStart) yyerror("starting and ending net can't be same."); }
        | NET_ZERO  { tempE.netEnd = 0; if(tempE.netEnd == tempE.netStart) yyerror("starting and ending net can't be same."); }

sourceNet:
        sourceNetStart sourceNetEnd

sourceNetStart:
        NET_TOKEN NET_NUM_TOKEN { tempS.netStart = $2; }
        | NET_ZERO  { tempS.netStart = 0; }
sourceNetEnd:
        NET_TOKEN NET_NUM_TOKEN { tempS.netEnd = $2; if(tempS.netEnd == tempS.netStart) yyerror("starting and ending net can't be same."); }
        | NET_ZERO  { tempS.netEnd = 0; if(tempS.netEnd == tempS.netStart) yyerror("starting and ending net can't be same."); }

elementValue:
        RESISTOR_VALUE  { if(tempE.elementName[0] == 'R'){ tempE.value = $1; tempE.unit = strdup("1"); } else { yyerror("No unit is specified, only possible for resistor.\n"); } if(!error) circuitElements.push_back(tempE); }
        | ELEM_VALUE_TOKEN ELEM_UNIT_TOKEN    { tempE.value = $1;  tempE.unit = $2; if(tempE.elementName[0] == 'R'){ if($2[1] || ($2[0]!='K' && $2[0]!= 'N' && $2[0]!='M')) yyerror("Incorrect unit.\n"); } else if(tempE.elementName[0] == 'L') { if( ($2[1] && $2[1]!='H' && ($2[0]!='K' && $2[0]!='N' && $2[0]!='M') ) || (!$2[1] && $2[0]!='H') ) yyerror("Incorrect unit.\n"); } else if(tempE.elementName[0] == 'C'){ if( ($2[1] && $2[1]!='F' && ($2[0]!='K' && $2[0]!='N' && $2[0]!='M') ) || (!$2[1] && $2[0]!='F') ) yyerror("Incorrect unit.\n"); } if(!error) circuitElements.push_back(tempE); }

sourceValue:
        DC_OFFSET_TOK AMP_TOKEN FREQ_TOKEN DELAY_TOK    { tempS.dcOffset = $1, tempS.amplitude = $2, tempS.freq = $3, tempS.delay = $4, tempS.dampingFactor = 0.0; if(!error) sourceElements.push_back(tempS); }
        | DC_OFFSET_TOK AMP_TOKEN FREQ_TOKEN DELAY_TOK DAMPING_TOK  { tempS.dcOffset = $1, tempS.amplitude = $2, tempS.freq = $3, tempS.delay = $4, tempS.dampingFactor = $5; if(!error) sourceElements.push_back(tempS); }

%%
void yyerror(char *s){
    error = 1;
    numErrors ++;
    extern int yylineno;
    fprintf(stderr, "Line Number %d: %s\n",yylineno, s);
}

int parse(char* fileName){
    yyin = fopen(fileName, "r");
    if(!yyin){
        fprintf(stderr, "No such input file exists!\n");
        return -1;
    }
    yyparse();
    if(numErrors > 0) return -1;
    return 1; // success
}

/* int main(int argc, char** argv){
    yyin = fopen(argv[1], "r");
    yyparse();
    if(numErrors == 0){
        printf("\nElements:\n");
        for(int i = 0 ; i < circuitElements.size(); i ++){
            element tempE = circuitElements[i];
            printf("%s->%d->NetStart:%d->NetEnd:%d->Value:%d->Unit:%s\n",tempE.elementName, tempE.elementNum, tempE.netStart, tempE.netEnd, tempE.value, tempE.unit);
        }
        printf("\nSource:\n");
        for(int i = 0 ; i < sourceElements.size(); i ++){
            source tempS = sourceElements[i];
            printf("%s->%d->NetStart:%d->NetEnd:%d->dcOffset:%f->Amp:%f->Freq:%f->Delay:%f->Damping:%f\n",tempS.sourceName, tempS.sourceNum, tempS.netStart, tempS.netEnd, tempS.dcOffset, tempS.amplitude, tempS.freq, tempS.delay, tempS.dampingFactor);
        }
        printf("\n\n");
    }
    fclose(yyin);
} */
