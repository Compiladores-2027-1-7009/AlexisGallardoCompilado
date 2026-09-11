<p  align="center">
  <img  width="200"  src="https://www.fciencias.unam.mx/sites/default/files/logoFC_2.png"  alt="">  <br>Compiladores  2027-1 <br>
  Práctica 0: Sistema de procesamiento de Lenguaje <br> Profesora: Ariel Adara Mercado Martínez
</p>

### Sistema de procesamiento de Lenguaje
### Objetivo:
Comprender y analizar el funcionamiento de los diferentes programas que intervienen en el proceso de traducción de un programa fuente a un programa ejecutable.

### Introducción
Un compilador es un programa que traduce un programa fuente escrito en un lenguaje de alto nivel a un
programa en lenguaje objeto, usualmente de bajo nivel. Este proceso no se realiza de manera aislada; el
compilador colabora con otros programas como el preprocesador, ensamblador y enlazador.
El preprocesador recopila y expande macros y otros fragmentos de código abreviado en el programa
fuente. Luego, el compilador transforma el código preprocesado en un programa objeto en lenguaje ensamblador, que es posteriormente convertido en código máquina por el ensamblador. Finalmente, el enlazador combina los archivos de código máquina y bibliotecas necesarias para producir un programa ejecutable. El cargador lleva este programa ejecutable a la memoria para su ejecución.

```mermaid
flowchart TD
subgraph 1
id1([Programa fuente]) --> Preprocesador  -- Programa Fuente modificado -->  Compilador  -- Programa objeto en lenguaje ensamblador -->  Ensamblador  -- Código máquina relocalizable --> Enlazador/Cargador --> id2([Código máquina destino])
end
subgraph  2  
id3[/Archivos de biblioteca y archivos objeto/] --> Enlazador/Cargador  
end  
 ```

### Desarrollo:

1. Deberá tener instalado el compilador _gcc_ y trabajar en un ámbiente _Linux_.
2. Escriba el siguiente programa en lenguaje **_C_** (sin copiar y pegar) y nómbrelo *programa.c*
```c
#include <stdio .h>
#include <stdlib.h>
//# define PI 3.1415926535897

# ifdef PI
# define area (r) (PI * r * r)
# else
# define area (r) (3.1416 * r * r)
# endif


/**
* Compiladores 2025-2
*
*/
int main ( void ) {
printf ("Hola Mundo !\n"); //Función para imprimir hola mundo
float mi_area = area (3) ; //soy un comentario... hasta donde llegaré ?
printf ("Resultado : %f\n", mi_area);
return 0;
}
```
3. Use el siguiente comando: `cpp programa.c programa.i`
Revise el contenido de _programa.i_ y conteste lo siguiente:
<ol type="a">
  <li>¿Qué ocurre cuando se invoca el comando <i>cpp</i> con esos argumentos?</li>
  Cuando se hace eso con esos argumentos, basicamente es pedirle al cpp (al preprocesador c) que tome como argumento el programa.c y que
  genere el programa.i. El cual al verlo se pueden ver cosas bastante familiares (como int, return 0, char, etc.), tambien que es demasiado
  extenso, mucho mas que el programa.c. Con lo que hemos visto en clase, sabemos que el preprocesador solo prepara el texto para dejarselo
  listo al compilador. 
  <li>¿Qué similitudes encuentra entre los archivos <i>programa.c</i> y <i>programa.i</i>?</li>
  Hay varias similitudes que se pueden notar, en 1ra (Y la mas evidente), ambos son archivos de texto plano legibles por humanos, al final de
  programa.i se ve que la estructura básica de la función int main ( void ) se ve semejante a la de programa.c (aunque los comentarios no 
  aparecen)
  <li>¿Qué pasa con las macros y los comentarios del código fuente original en <i>programa.i</i>?</li>
  Como mencione anteriormente, los comentarios parecen desaparecer, en cuanto a los macros, como se menciona arriba en el documento, las macros
  son expandidas, aunque tambien parecen ser resueltas, por ejemplo: #define PI estaba comentado en programa.c, el preprocesador evaluo el #else y
  sustituyo la palabra area(3) directamente por la formula matematica: (r) (3.1416 * r * r) (3).
  <li>Compare el contenido de <i>programa.i</i> con el de <i>stdio.h</i> e indique de forma general las similitudes entre ambos
  archivos.</li>
  La similitud es que las miles de líneas que aparecen al principio de programa.i son una copia de lo que hay dentro de stdio.h. Si los
  comparamos, vemos que comparten las mismas estructuras y declaraciones de funciones de la biblioteca estándar (como por ejemplo extern int
  printf y otras cosas del sistema). Básicamente, lo que hizo el preprocesador fue pegar todo el contenido de stdio.h arriba del codigo para
  dejarlo unificado en un solo archivo
  <li>¿A qué etapa corresponde este proceso?</li>
  A la etapa de preprocesamiento
</ol>

---

4. Ejecute la siguiente instrucción: ``gcc -Wall -S programa.i``
<ol type="a">
  <li>¿Para qué sirve la opción <i>-Wall</i>?</li>
  Para decirle a gcc que debe activar todos los avisos o advertencias posibles sobre nuestro codigo. Lo que nos debe ayudar a detectar malas
  practicas o posibles errores logicos que aunque dejen compilar el programa podrian causar problemas al ejecutarse.
  <li>¿Qué le indica a gcc la opción <i>-S</i>?</li>
  Le indica al compilador que se detenga justo después de la etapa de compilación. Lo que evita que pase a las fases de ensamblado
  y enlazado
  <li>¿Qué contiene el archivo de salida y cuál es su extensión?</li>
  Contiene nuestras intrucciones de codigo traducidas a ensamblador. Su extension es .s
  <li>¿A qué etapa corresponde este comando?</li>
  Etapa de compilacion
</ol>

---

5. Ejecute la siguiente instrucción: `as programa.s -o programa.o`
<ol type="a">
  <li> Antes de revisarlo, indique cuál es su hipótesis sobre lo que debe contener el archivo con extensión  <i>.o</i>. </li>
  Por la o, me imagino que es el codigo en codigo objeto, por lo tanto debe de haber una cochinada de simbolos inentendibles jajaja
  <li> Diga de forma general qué contiene el archivo <i>programa.o</i> y por qué se visualiza de esa manera. </li>
  No lo podia abrir hasta usar emacs, pero en efecto, contiene codigo maquina binario e instrucciones que el procesador puede entender
  directamente. Y se ve asi porque no está hecho para ser leído por humanos, si no, por las computadoras, aunque los editores intentan interpretar
  los bytes binarios como si fueran texto normal y por eso da esos simbolos
  <li> ¿Qué programa se invoca con  <i>as</i>? </li>
  Al assembler (Ensamblador) del sistema
  <li> ¿A qué etapa corresponde la llamada a este programa? </li>
  A la etapa de ensamblado
</ol>

---

6. Encuentre la ruta de los siguientes archivos en el equipo de trabajo:
* ld-linux-x86-64.so.2
  `/lib64/ld-linux-aarch64.so.1`
* Scrt1.o (o bien, crt1.o)
  `/usr/lib64/Scrt1.o`
* crti.o
  `/usr/lib64/crti.o`
* crtbeginS.o
  *No requerida*
* crtendS.o
  *No requerida*
* crtn.o
  `/usr/lib64/crtn.o`

---

7. Ejecute el siguiente comando, sustituyendo las rutas que encontró en el paso anterior:
```bash
ld -o ejecutable -dynamic-linker /lib/ld-linux-x86-64.so.2 /usr/lib/Scrt1.o /usr/lib/crti.o programa.o -lc /usr/lib/crtn.o
```

<ol type="a">
  <li> En caso de que el comando ld mande errores, investigue como enlazar un programa utilizando el comando <i>ld</i>. Y proponga una posible solución para llevar a cabo este proceso con éxito. </li>
  Al principio, el comando ld manual generó un ejecutable que al correrlo lanzaba el error cannot execute: required file not found. Ocurrió porque el enlazador apuntaba a una ruta incorrecta del sistema. Investigando descubri que en mi arquitectura ARM of 64 bits, la ruta real es /usr/lib/ld-linux-aarch64.so.1. Mi solución fue corregir la ruta exacta en el comando ld o, de forma más eficiente, utilizar gcc programa.o -o executable

  <li> Describa el resultado obtenido al ejecutar el comando anterior. </li>
  Tras corregir la ruta del enlazador el proceso fue etzitoso. Se generó un archivo binario ejecutable capaz de interactuar con el sistema operativo de forma correcta.
</ol>

---

8. Una vez que se enlazó el código máquina relocalizable, podemos ejecutar el programa con la siguiente instrucción en la terminal: ```./ejecutable``` <p>
Regresa Hola mundo ! y el Resultado : 28.274401

---

9. Quite el comentario de la macro _#define PI_ en el código fuente original y conteste lo siguiente:
<ol type="a">
  <li> Genere nuevamente el archivo.i. De preferencia asigne un nuevo nombre.</li>
  *(Paso realizado en la terminal ejecutando cpp)*
  <li> ¿Cambia en algo la ejecución final? </li>
  En el primer programa el preprocesador usaba el valor del #else (3.1416), por lo que el cálculo daba exactamente 28.274401. Al usar ahora el
  valor real y más preciso de la macro PI, el resultado de la multiplicación cambia a nivel de decimales, dándonos un resultado final en la pantalla mucho más exacto (28.274334).
</ol>

---

10. Escribe un segundo programa en lenguaje **_C_** en el que agregue 4 directivas del preprocesador de _**C**_ (_cpp_)[^1]. Las directivas elegidas deben jugar algún papel en el significado del programa, ser distintas entre sí y diferentes de las utilizadas en el primer programa (aunque no están prohibidas si las requieren). 
<ol type="a">
    <li>Explique su utilidad general y su función en particular para su programa. (Cree el programa IVA.c)</li>
</ol>
Las directivas funcionaron de la siguiente manera:
<ul>
  <li><b>#define IVA 0.16:</b> Su utilidad es guardar un valor constante. En el programa sirvio para establecer el porcentaje de impuesto en un solo lugar; así si el IVA cambia en el futuro solo modificamos esta línea y se actualiza en todo el código.</li>
  <li><b>#define CALCULAR_IVA(precio):</b> Su utilidad es crear macros con argumentos para realizar sustituciones de fórmulas rápidas. En el programa sirvió para automatizar la operacion matematica del impuesto sin la necesidad de crear una funcion completa en C.</li>
  <li><b>#define DESCUENTO_ACTIVO:</b> Su utilidad es servir como una bandera o interruptor de configuración. En el programa, sirvió para avisarle al preprocesador que queríamos activar una oferta especial en la tienda.</li>
  <li><b>#ifdef / #else / #endif:</b> Su utilidad es la compilación condicional, o sea, decidir que partes del codigo se quedan y cuales se borran segun las banderas activadas. En el programa, sirvió para evaluar si existía la bandera del descuento; como si estaba activa, el preprocesador metio al archivo final la formula con la rebaja del 10% y borro por completo el codigo del #else.</li>
</ul>

---

11. Redacte un informe detallado con sus resultados y conclusiones.

Con esta práctica me quedo mas claro como funciona de verdad el procesamiento de un codigo en C. Estamos tan acostumbrados a compilar que uno puede pensar que compilar es solo presionar un boton o meter un comando rapido y ya, ten tu resultado, pero con todo lo que hice en esta practica, pude ver que el codigo pasa por una linea de produccion de cuatro etapas:

<ul>
  <li><b>Preprocesamiento:</b> Como vimos en el primer punto, aquí el preprocesador hace la limpieza. Borra por completo los comentarios (porque a la máquina no le sirven (tambien lo menciono la profa en la clase)) y expande las macros. También copia y pega al instante las miles de líneas de stdio.h al principio de nuestro código, por lo que el archivo programa.i se vuelve muy grande, en comparacion con el programa.c.</li>
  
  <li><b>Compilación :</b> En esta parte el compilador traduce todo ese texto humano a lenguaje ensamblador. Estuvo interesante porque 1ro pase por el error de la variable 'r' no declarada, un simple espacio que venia en la estructura original del codigo que nos pediste reescribir rompio la macro y causo que el compilador marcara problemas, lo que me hizo ver lo estricta que es esta etapa con la sintaxis.</li>
  
  <li><b>Ensamblado:</b> Aqui el ensamblador traduce el archivo .s a codigo objeto. Cuando intente abrirlo con Emacs confirme mi hipotesis: ya no es texto que cualquier persona pueda leer, sino que resulto ser binario, y por eso se veian puros símbolos extraños y raros.</li>
  
  <li><b>Enlazado :</b> Es el  paso final donde se une el codigo objeto con las bibliotecas de C y los archivos de arranque del sistema. Aqui aprendi que: como mi Fedora es de 64 bits y arquitectura aarch64, las rutas cambiaron a las del manual. Al principio me dio el error de "file not found" por apuntar a una ruta que no existia, pero lo solucione buscando la ruta real del sistema.</li>
</ul>

<b>En conclusión:</b>
aber jugado con la macro de PI en el punto 9 (la cual cambio los decimales del resultado final) y luego crear mi programa con las banderas de descuento, me enseno que las directivas del preprocesador son herramientas utiles para automatizar cosas y configurar el codigo antes de compilarlo. Fue una buena practica para entender que pasa detrás de escena en la terminal de Linux :p

[^1]: Pueden consultar la lista de directivas en su documentación en línea: [CPP - Index of directives](https://gcc.gnu.org/onlinedocs/cpp/Index-of-Directives.html##Index-of-Directives). O bien, revisar la entrada para este preprocesador en la herramienta man en Linux: `$ man cpp`
