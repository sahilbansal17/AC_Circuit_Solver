## PRACTICE FOR YACC

Yacc reads the grammar and generates C code for a syntax analyzer or parser. It uses grammar rules that allow it to analyze tokens and create a syntax tree.

A simple calculator is made, *calculator.l* file returns token and *calculator.y* parses them to give the appropriate output.

To run :
1. `yacc -d calculator.y` # creates y.tab.h, y.tab.c
2. `lex calculator.l` # creates lex.yy.c
3. `cc lex.yy.c y.tab.c -o calculator` # compile/link
4. `./calculator`
