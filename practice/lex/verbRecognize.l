%{
    /*
    recognize whether a word is verb or not
    */
%}
%%
[\t ]+ /* ignores whitespaces */ ;
is |
am |
are |
were |
was |
be |
being |
been |
do |
does |
did |
will |
would |
should |
can |
could |
has |
have |
had |
go          { printf("%s: is a verb\n", yytext) ; }
[a-zA-Z]+   { printf("%s: is not a verb\n", yytext) ; }

.|\n        { ECHO; /* normal default */}

%%

int main(int argc, char* argv[]){
    yyin = fopen(argv[1], "r"); // input file for lex is yyin and is stdin by default
    yylex();
    fclose(yyin);
}
