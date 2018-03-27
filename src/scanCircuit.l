%{
    #include <stdio.h>
    #include "y.tab.h"
    #define YY_DECL extern "C" int yylex()
    void yyerror(char *);
%}
%option yylineno

%s ELEMENT
%s ELEMENT_NUM
%s SOURCE
%s SOURCE_NUM
%s NET_START
%s NET_START_NUM
%s NET_END
%s NET_END_NUM
%s ELEM_VALUE
%s ELEM_UNIT
%s SOURCE_VALUE
%s SV_DC_OFFSET
%s SV_AMP
%s SV_FREQ
%s SV_DELAY
%s SV_DAMPING

element [RLC]
source [VI]
num [0-9]+
unit K|N|M
spaces [ \t]+
net (Net)|(NET)
decimal ([0-9]+)|([0-9]*\.[0-9]+)

%%
<INITIAL>{spaces}/{element}   { BEGIN ELEMENT; }
<INITIAL>{spaces}/{source}   { BEGIN SOURCE; }
<INITIAL>{element}/{num} { yylval.ch = strdup(yytext); BEGIN ELEMENT_NUM; return ELEMENT_TOKEN; }
<INITIAL>{source}/{num}  { yylval.ch = strdup(yytext); BEGIN SOURCE_NUM; return SOURCE_TOKEN; }
{spaces}  ;

<ELEMENT>{element}/{num}    { yylval.ch = strdup(yytext); BEGIN ELEMENT_NUM; return ELEMENT_TOKEN; }
<ELEMENT_NUM>{num}/{spaces} { yylval.num = atoi(yytext); BEGIN NET_START; return ELEMENT_NUM_TOKEN; }
<SOURCE>{source}/{num}    { yylval.ch = strdup(yytext); BEGIN SOURCE_NUM; return SOURCE_TOKEN; }
<SOURCE_NUM>{num}/{spaces} { yylval.num = atoi(yytext); BEGIN NET_START; return SOURCE_NUM_TOKEN; }

<NET_START>0/{spaces}    { yylval.num = 0; BEGIN NET_END; return NET_ZERO; }
<NET_START>{net}/{num}  { yylval.ch = strdup(yytext); BEGIN NET_START_NUM; return NET_TOKEN; }
<NET_START_NUM>{num}/{spaces}   { yylval.num = atoi(yytext); BEGIN NET_END; return NET_NUM_TOKEN; }

<NET_END>0/{spaces}SINE  { yylval.num = 0; BEGIN SOURCE_VALUE; return NET_ZERO; }
<NET_END>{net}/{num}    { yylval.ch = strdup(yytext); BEGIN NET_END_NUM; return NET_TOKEN; }
<NET_END_NUM>{num}/{spaces}SINE { yylval.num = atoi(yytext); BEGIN SOURCE_VALUE; return NET_NUM_TOKEN; }
<NET_END>0/{spaces}  { yylval.num = 0; BEGIN ELEM_VALUE; return NET_ZERO; }
<NET_END_NUM>{num}/{spaces} { yylval.num = atoi(yytext); BEGIN ELEM_VALUE; return NET_NUM_TOKEN; }

<ELEM_VALUE>{num}   { yylval.num = atoi(yytext); BEGIN INITIAL; return RESISTOR_VALUE; } // for the case that resistor will have no unit mentioned  
<ELEM_VALUE>{num}/{unit}?[FH]?   { yylval.num = atoi(yytext); BEGIN ELEM_UNIT; return ELEM_VALUE_TOKEN; } // for ease of error reporting  
<ELEM_UNIT>{unit}?[FH]?    { yylval.ch = strdup(yytext); BEGIN INITIAL; return ELEM_UNIT_TOKEN; }  // since spaces will note necessarily follow the unit, it could lead to many bugs 

<SOURCE_VALUE>"("   { ; BEGIN SV_DC_OFFSET; }
<SV_DC_OFFSET>{decimal}/{spaces}    { yylval.dec = atof(yytext); BEGIN SV_AMP; return DC_OFFSET_TOK; }
<SV_AMP>{decimal}/{spaces}    { yylval.dec = atof(yytext); BEGIN SV_FREQ; return AMP_TOKEN; }
<SV_FREQ>{decimal}((Khz)|(KHz))    { yylval.dec = atof(yytext); BEGIN SV_DELAY; return FREQ_TOKEN; }
<SV_DELAY>{decimal}S/(")"|{spaces}")")    { yylval.dec = atof(yytext); BEGIN INITIAL; return DELAY_TOK; }
<SV_DELAY>{decimal}S    { yylval.dec = atof(yytext); BEGIN SV_DAMPING; return DELAY_TOK; }
<SV_DAMPING>{decimal}/(")"|{spaces}")") { yylval.dec = atof(yytext); BEGIN INITIAL; return DAMPING_TOK; }

<INITIAL>")"   { ; } // consume ")" 
<SOURCE_VALUE>SINE { ; } // consume "SINE" 

\n { ; } // so that yylineno increments after each line 
.   { char msg[25]; sprintf(msg, "%s, <%s>", "invalid character", yytext); yyerror(msg); }

%%

int yywrap(void) {
    return 1;
}
