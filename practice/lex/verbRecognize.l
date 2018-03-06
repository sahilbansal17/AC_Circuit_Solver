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

int main(){
    yylex();
}
