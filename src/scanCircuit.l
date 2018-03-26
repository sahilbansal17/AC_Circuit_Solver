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
%s ELEM_VALUE_UNIT
%s SOURCE_VALUE
%s SV_DC_OFFSET
%s SV_AMP
%s SV_FREQ
%s SV_DELAY
%s SV_DAMPING

element [RLC]
source [VI]
num [0-9]+
unit K|N|M|(NF)|(NH)|(MF)|(MH)
spaces [ \t]+
net (Net)|(NET)
decimal ([0-9]+)|([0-9]*\.[0-9]+)

%%
<INITIAL>{spaces}/{element}   { BEGIN ELEMENT; }
<INITIAL>{spaces}/{source}   { BEGIN SOURCE; }
<INITIAL>{element}/{num} { yylval.ch = strdup(yytext); BEGIN ELEMENT_NUM; return ELEMENT_TOKEN; }
<INITIAL>{source}/{num}  { yylval.ch = strdup(yytext); BEGIN SOURCE_NUM; return SOURCE_TOKEN; }
{spaces}  { printf(" "); };

<ELEMENT>{element}/{num}    { yylval.ch = strdup(yytext); BEGIN ELEMENT_NUM; return ELEMENT_TOKEN; }
<ELEMENT_NUM>{num}/{spaces} { yylval.num = atoi(yytext); BEGIN NET_START; return ELEMENT_NUM_TOKEN; }
<SOURCE>{source}/{num}    { yylval.ch = strdup(yytext); BEGIN SOURCE_NUM; return SOURCE_TOKEN; }
<SOURCE_NUM>{num}/{spaces} { yylval.num = atoi(yytext); BEGIN NET_START; return SOURCE_NUM_TOKEN; }

<NET_START>0/{spaces}    { yylval.num = 0; BEGIN NET_END; return NET_START_NUM_TOKEN; }
<NET_START>{net}/{num}  { yylval.ch = strdup(yytext); BEGIN NET_START_NUM; return NET_START_TOKEN; }
<NET_START_NUM>{num}/{spaces}   { ECHO; BEGIN NET_END; }

<NET_END>0/{spaces}SINE  { ECHO; BEGIN SOURCE_VALUE; }
<NET_END>{net}/{num}    { ECHO; BEGIN NET_END_NUM; }
<NET_END_NUM>{num}/{spaces}SINE { ECHO; BEGIN SOURCE_VALUE; }
<NET_END>0/{spaces}  { ECHO; BEGIN ELEM_VALUE; }
<NET_END_NUM>{num}/{spaces} { ECHO; BEGIN ELEM_VALUE; }

<ELEM_VALUE>{num}/{spaces}   { ECHO; BEGIN INITIAL; } // for the case that resistor will have no unit mentioned
<ELEM_VALUE>{num}/{unit}   { ECHO; BEGIN ELEM_VALUE_UNIT; }
<ELEM_VALUE_UNIT>{unit}/{spaces}    { ECHO; BEGIN INITIAL; }

<SOURCE_VALUE>"("   { ; BEGIN SV_DC_OFFSET; }
<SV_DC_OFFSET>{decimal}/{spaces}    { ECHO; BEGIN SV_AMP; }
<SV_AMP>{decimal}/{spaces}    { ECHO; BEGIN SV_FREQ; }
<SV_FREQ>{decimal}(Khz)    { ECHO; BEGIN SV_DELAY; }
<SV_DELAY>{decimal}S/(")"|{spaces}")")    { ECHO; BEGIN INITIAL; }
<SV_DELAY>{decimal}S    { ECHO; BEGIN SV_DAMPING; }
<SV_DAMPING>{decimal}/(")"|{spaces}")") { ECHO; BEGIN INITIAL; }

.   { ; }

%%

int yywrap(void) {
    return 1;
}
