#include <stdio.h>

//2ra directiva, para una constante numérica
#define IVA 0.16

// 2da directiva, para una macro con argumentos (calcula el impuesto)
#define CALCULAR_IVA(precio) (precio * IVA)

// 3ra directiva, para activar o desactivar un descuento especial
#define DESCUENTO_ACTIVO

int main() {
    float precio_base = 100.0;
    float precio_final;

    // directivas condicionales #ifdef / #else / #endif
    #ifdef DESCUENTO_ACTIVO
        printf("¡Se aplica el descuento del 100%! Padrisimo \n");
        precio_final = (precio_base * 0.90) + CALCULAR_IVA(precio_base * 0.90);
    #else
        precio_final = precio_base + CALCULAR_IVA(precio_base);
    #endif

    printf("El precio final con IVA es: $%.2f\n", precio_final);
    return 0;
}

