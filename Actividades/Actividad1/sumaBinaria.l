%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>

long suma_total = 0;
%}

%%
0b[01]+ {
    suma_total += strtol(yytext + 2, NULL, 2);
}
(.|\n)    { /* Si lees esto ola */ }
%%

int main() {
    yylex();
    printf("%ld\n", suma_total);
    return 0;
}

