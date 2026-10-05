%option noyywrap

%{
#include <stdio.h>

/* matriz para evitar errores de formateo */
char tablero[9]; 
int fila_actual = 0;
int col_actual = 0;

void verificar_ganador() {
    int gana_X = 0;
    int gana_O = 0;
    int vacios = 0;

    // cuenta casillas vacías en el tablero
    for (int i = 0; i < 9; i++) {
        if (tablero[i] == '_') {
            vacios++;
        }
    }

    // verifica las  filas
    for (int i = 0; i < 3; i++) {
        int idx0 = i * 3 + 0;
        int idx1 = i * 3 + 1;
        int idx2 = i * 3 + 2;
        if (tablero[idx0] != '_' && tablero[idx0] == tablero[idx1] && tablero[idx0] == tablero[idx2]) {
            if (tablero[idx0] == 'X') gana_X = 1;
            if (tablero[idx0] == 'O') gana_O = 1;
        }
    }

    // verifica las columnas
    for (int j = 0; j < 3; j++) {
        int idx0 = 0 * 3 + j;
        int idx1 = 1 * 3 + j;
        int idx2 = 2 * 3 + j;
        if (tablero[idx0] != '_' && tablero[idx0] == tablero[idx1] && tablero[idx0] == tablero[idx2]) {
            if (tablero[idx0] == 'X') gana_X = 1;
            if (tablero[idx0] == 'O') gana_O = 1;
        }
    }

    // verifica diagonales
    if (tablero[0] != '_' && tablero[0] == tablero[4] && tablero[0] == tablero[8]) {
        if (tablero[0] == 'X') gana_X = 1;
        if (tablero[0] == 'O') gana_O = 1;
    }
    if (tablero[2] != '_' && tablero[2] == tablero[4] && tablero[2] == tablero[6]) {
        if (tablero[2] == 'X') gana_X = 1;
        if (tablero[2] == 'O') gana_O = 1;
    }

    // imprime el veredicto  
    if (gana_X && gana_O) {
        printf(" -> empate\n");
    } else if (gana_X) {
        printf(" -> gana X\n");
    } else if (gana_O) {
        printf(" -> gana O\n");
    } else if (vacios == 0) {
        printf(" -> Nadie gana\n");
    } else {
        printf(" -> sin ganador\n");
    }
}
%}

%%
[XO_]   {
            /* guarda el caracter convirtiendo fila y columna a un indice plano  */
            tablero[fila_actual * 3 + col_actual] = yytext[0];
            col_actual++;
        }

\n      {
            if (col_actual > 0) {
                fila_actual++;
                col_actual = 0;
            }
            if (fila_actual == 3) {
                verificar_ganador();
                fila_actual = 0;
            }
        }

[ \t]   ;
.       ;
%%

int main() {
    yylex();
    return 0;
}

