%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%%
^[0-9 \t]+A\n {
    int suma = 0;
    // busca y suma los números de la línea usando strtok
    char *token = strtok(yytext, " \tA\n");
    while (token != NULL) {
        suma += atoi(token);
        token = strtok(NULL, " \tA\n");
    }
    printf("%d\n", suma);
}

^[0-9 \t]+B\n {
    // si termina en B, se imprime la linea tal cual
    printf("%s", yytext);
}

.|\n ; // ignora cualquier otra linea que no cumpla el formato
%%

int main() {
    yylex();
    return 0;
}

