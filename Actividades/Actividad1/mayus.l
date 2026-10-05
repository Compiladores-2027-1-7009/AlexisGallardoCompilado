%option noyywrap

%{
#include <stdio.h>
#include <ctype.h>
%}

%%
[a-z]+  {
            /* recorre la palabra encontrada y convierte cada letra */
            for(int i = 0; i < yyleng; i++) {
                fprintf(yyout, "%c", toupper(yytext[i]));
            }
        }
.|\n    { 
            /* cualquier otro carácter (sean espacios, números, saltos) se copia igual a la salida */
            fprintf(yyout, "%s", yytext); 
        }
%%

int main(int argc, char **argv) {
    if (argc > 2) {
        yyin = fopen(argv[1], "r");
        yyout = fopen(argv[2], "w");
    }
    yylex();
    return 0;
}

