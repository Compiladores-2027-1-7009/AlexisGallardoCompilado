
Siento que es importante mencionar como es la interacción y la prueba de los programas, ya que depende de cada uno el cómo funcionan según su diseño:

### lineas.l, wc.l y gato.l
*   **`lineas.l`**, **`wc.l`** y **`gato.l`**: Solo requieren ejecutar el programa y escribir directamente.
    *   **`lineas.l`**: Numera al dar `Enter`.
    *   **`wc.l`**: Requiere presionar `Ctrl + D` al final para que el flujo termine y muestre el conteo de líneas, palabras y bytes en la consola.
    *   **`gato.l`**: Procesa un bloque de 3 líneas con 3 caracteres (`X`, `O`, `_`) por línea antes de lanzar el veredicto.

### sumaBinaria.l y filtroLin.l
*   **`sumaBinaria.l`** y **`filtroLin.l`**: Son más estrictos con el formato de entrada.
    *   **`sumaBinaria.l`**: El sumador binario ignora cualquier entrada a menos que empiece con el prefijo `0b` seguido de bits (ej. `0b10 0b11`), mostrando el total acumulado en decimal al cerrar con `Ctrl + D`.
    *   **`filtroLin.l`**: Evalúa líneas completas de números:
        *   Si la línea termina con la letra **A** (ej. `10 20A`), procesa los tokens, extrae los enteros y muestra su suma al dar `Enter`.
        *   Si termina con **B** (ej. `50 60B`), imprime la línea tal cual.
        *   Cualquier otra combinación es ignorada.

### mayus.l y analizadlex.l
*   **`mayus.l`** y **`analizadlex.l`**: No son interactivos en consola; requieren que creemos archivos de prueba y pasemos sus rutas como argumentos al ejecutable.
    *   **`mayus.l`**: La estructura de ejecución requiere pasar el archivo de origen y el de destino:
        ```bash
        ./ejecutable entrada.txt salida.txt
        ```
    *   **`analizadlex.l`**: Exige un archivo con extensión `.art` (ej. `codigo.art`) que contenga el código a evaluar con palabras reservadas, números o identificadores. Al ejecutarlo como:
        ```bash
        ./analizador codigo.art
        ```
        El programa valida la extensión, mapea los tokens y genera de forma automática un archivo de salida con el mismo nombre pero extensión `.tokens` (ej. `codigo.tokens`) estructurado con las etiquetas `<CLASE, valor>`.
