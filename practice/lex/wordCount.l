%{
	/*
	print the count of chars, words and lines in a input file
	*/
	int chars = 0;
	int words = 0;
	int lines = 0;
%}

%%

[a-zA-Z]+	{ words ++; chars += strlen(yytext); }
\n	{ chars ++; lines ++;}
.	{ chars ++;}

%%

int main(int argc, char* argv[]){
	yyin = fopen(argv[1], "r");
	yylex();
	printf("Lines:%8d\nWords:%8d\nChars:%8d\n", lines, words, chars);
}
