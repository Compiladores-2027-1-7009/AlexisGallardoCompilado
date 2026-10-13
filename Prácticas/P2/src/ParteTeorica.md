#### Ejercicios
Para la gramática G = ( N, Σ, P, S), descrita por las siguientes producciones: 
> P = {
>> programa → declaraciones sentencias <br>
>> declaraciones → declaraciones declaracion | declaracion <br>
>> declaracion → tipo lista-var **;** <br>
>> tipo → **int** | **float** <br>
>> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ <br>
>> sentencias → sentencias sentencia | sentencia <br>
>> sentencia → _**identificador**_ **=** expresion **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>> expresion → expresion **+** expresion | expresion **-** expresion | expresion __\*__ expresion | expresion **\/** expresión | _**identificador**_ | **_numero_** <br>
>> expresion → **(** expresion **)** <br>
}


1. Determinar en un archivo Readme, en formato Markdown (.md) o LaTeX (.tex) -- con su respectivo PDF, para este último -- , los conjuntos _N_, _Σ_ y el símbolo inicial _S_.  (0.5 pts.)
:   

* **$N$:**
```math
N = \{\text{programa, declaraciones, declaracion, tipo, lista\_var, sentencias, sentencia, expresion}\}
```

* **$\Sigma$:**
```math
\Sigma = \{\text{int, float, if, else, while, identificador, numero, };, \text{,}, =, +, -, *, /, (, )\}
```

* **$S$:**
```math
S = \text{programa}
```


2. Mostrar en el archivo el proceso de eliminación de ambigüedad o justificar, en caso de no ser necesario. (1 pts.).

La producción de **expresión** es ambigua, no define ni la precedencia ni la asociatividad de los operadores matemáticos, lo que nos permitiria construir muchos árboles sintácticos válidos para una misma cadena (como por ejemplo: `a + b * c`).   

Asi que toca jerarquizar las operaciones creando nuevos **N**:
* **$E$**: para suma/resta
* **$T$**: para multiplicación/división
* **$F$**: para paréntesis y valores crudos


```math
\begin{aligned} E &\rightarrow E + T \mid E - T \mid T \\ T &\rightarrow T * F \mid T / F \mid F \\ F &\rightarrow ( E ) \mid \text{identificador} \mid \text{numero} \end{aligned}
```

3. Mostrar en el archivo el proceso de eliminación de la recursividad izquierda o justificar, en caso de no ser necesario. (1 pts.)

El análisis sintáctico falla y entra en ciclos infinitos si existen reglas recursivas por la izquierda. Por lo que toca usar la regla de transformación para corregir las producciones.   

#### Para declaraciones ($\alpha = \text{declaracion}$, $\beta = \text{declaracion}$):
$$\begin{aligned}
\text{declaraciones} &\rightarrow \text{declaracion \ \ declaraciones'} \\
\text{declaraciones'} &\rightarrow \text{declaracion \ \ declaraciones'} \mid \epsilon
\end{aligned}$$

#### lista_var ($\alpha = \text{, identificador}$, $\beta = \text{identificador}$):
```math
\begin{aligned}
\text{lista\_var} &\rightarrow \text{identificador \ \ lista\_var'} \\
\text{lista\_var'} &\rightarrow \text{, identificador \ \ lista\_var'} \mid \epsilon
\end{aligned}
```

#### sentencias ($\alpha = \text{sentencia}$, $\beta = \text{sentencia}$):
$$\begin{aligned}
\text{sentencias} &\rightarrow \text{sentencia \ \ sentencias'} \\
\text{sentencias'} &\rightarrow \text{sentencia \ \ sentencias'} \mid \epsilon
\end{aligned}$$

#### expresiones aritméticas ($E$ y $T$):
$$\begin{aligned}
E &\rightarrow T E' \\
E' &\rightarrow + \ T E' \mid - \ T E' \mid \epsilon \\
T &\rightarrow F T' \\
T' &\rightarrow * \ F T' \mid / \ F T' \mid \epsilon
\end{aligned}$$


4. Mostrar en el archivo el proceso de factorización izquierda o justificar, en caso de no ser necesario. (1 pts.)

Aqui si no es necesario. Tras eliminar la ambigüedad y la recursión por la izquierda, y ver los 1ros símbolos (conjuntos $\text{FIRST}$) de cada regla de la gramática: 

En ningún **N** hay dos reglas que comiencen con el mismo símbolo terminal. Como en:
$$E' \rightarrow +TE' \mid -TE' \mid \epsilon$$

Cada alternativa empieza con un token distinto ($+$, $-$ o vacío). Asi que no hay porque hacerla.


5. Mostrar en el archivo los nuevos conjuntos _N_ y _P_. (0.5 pts.)

```math
N = \{\text{programa, declaraciones, declaraciones', declaracion, tipo, lista\_var, lista\_var', sentencias, sentencias', sentencia, } E, E', T, T', F\}
```

#### ($P$):
```math
\begin{aligned}
\text{programa} &\rightarrow \text{declaraciones \ \ sentencias} \\
\text{declaraciones} &\rightarrow \text{declaracion \ \ declaraciones'} \\
\text{declaraciones'} &\rightarrow \text{declaracion \ \ declaraciones'} \mid \epsilon \\
\text{declaracion} &\rightarrow \text{tipo \ \ lista\_var} \ ; \\
\text{tipo} &\rightarrow \text{int} \mid \text{float} \\
\text{lista\_var} &\rightarrow \text{identificador \ \ lista\_var'} \\
\text{lista\_var'} &\rightarrow \text{, \ \ identificador \ \ lista\_var'} \mid \epsilon \\
\text{sentencias} &\rightarrow \text{sentencia \ \ sentencias'} \\
\text{sentencias'} &\rightarrow \text{sentencia \ \ sentencias'} \mid \epsilon \\
\text{sentencia} &\rightarrow \text{identificador} \ = \ E \ ; \\
\text{sentencia} &\rightarrow \text{if} \ ( \ E \ ) \ \text{sentencias \ \ else \ \ sentencias} \\
\text{sentencia} &\rightarrow \text{while} \ ( \ E \ ) \ \text{sentencias} \\
E &\rightarrow T E' \\
E' &\rightarrow + \ T E' \mid - \ T E' \mid \epsilon \\
T &\rightarrow F T' \\
T' &\rightarrow * \ F T' \mid / \ F T' \mid \epsilon \\
F &\rightarrow ( \ E \ ) \mid \text{identificador} \mid \text{numero}
\end{aligned}
```
