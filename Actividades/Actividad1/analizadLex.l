%option noyywrap
%option yylineno

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macro imprimir el formato de token
#define PRINT_TOKEN(clase, valor) fprintf(yyout, "<%s, %s>\n", clase, valor)
%}

%%
    /* palabras reservadas */
"if"|"then"|"else"|"while"|"do"|"case"|"is"|"void"|"true"|"false"|"begin"|"end"|"not" { PRINT_TOKEN("PALABRA_RESERVADA", yytext); }

    /* identificadores */
[a-zA-Z_][a-zA-Z0-9_]*                                { PRINT_TOKEN("IDENTIFICADOR", yytext); }

    /* num reales */
[0-9]+\.[0-9]+                                        { PRINT_TOKEN("NUMERO_REAL", yytext); }

    /* num enteros */
[0-9]+                                                { PRINT_TOKEN("NUMERO_ENTERO", yytext); }

    /* cadenas caracteres entre comillas */
\"[^\"\n]*\"                                          { PRINT_TOKEN("CADENA", yytext); }

    /* comentarios unica linea */
"--"[^\n]*                                            {  }

    /*  comentarios multilinea  */
"<*"([^*]|\*+[^>])*"\*>"                              {  }

    /*  operador asignacion */
":="                                                  { PRINT_TOKEN("OPERADOR_ASIGNACION", yytext); }

    /* op. relacionales */
">"|"<"|"<>"|"="                                      { PRINT_TOKEN("OPERADOR_RELACIONAL", yytext); }

    /* op. arit. */
"+"|"-"|"*"|"/"|"%"                                    { PRINT_TOKEN("OPERADOR_ARITMETICO", yytext); }

    /* símbolos especiales */
"("|")"|"{"|"}"|";"|","                                { PRINT_TOKEN("SIMBOLO_ESPECIAL", yytext); }

    /* espacios en blanco */
[ \t\r\n]+                                            { /*  */ }

    /* en caso de error */
.                                                     { fprintf(stderr, "Error lexico: Caracter '%s' inesperado en la línea %d\n", yytext, yylineno); }

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <archivo.art>\n", argv[0]);
        return 1;
    }

    // valida extension entrada
    char *ext_entrada = strrchr(argv[1], '.');
    if (!ext_entrada || strcmp(ext_entrada, ".art") != 0) {
        fprintf(stderr, "Error: El archivo de entrada debe tener extensión .art\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error al abrir el archivo de entrada.\n");
        return 1;
    }

    // construir nombre archivo salida 
    int longitud_nombre = ext_entrada - argv[1];
    char *nombre_salida = (char *) malloc(longitud_nombre + 8);
    strncpy(nombre_salida, argv[1], longitud_nombre);
    nombre_salida[longitud_nombre] = '\0';
    strcat(nombre_salida, ".tokens");

    yyout = fopen(nombre_salida, "w");
    if (!yyout) {
        fprintf(stderr, "Error al crear el archivo de salida.\n");
        fclose(yyin);
        free(nombre_salida);
        return 1;
    }

    yylex();

    fclose(yyin);
    fclose(yyout);
    free(nombre_salida);
    return 0;
}

