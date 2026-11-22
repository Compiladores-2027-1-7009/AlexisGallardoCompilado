1. Determinar en un archivo Readme, en formato Markdown (.md) o LaTeX (.tex) - con su respectivo PDF, para este último - , los conjuntos _N_, _Σ_ y el símbolo inicial _S_. (0.5 pts.)

- **$N$:**
```math
N = \{\text{programa, declaraciones, declaracion, tipo, lista\_var, sentencias, sentencia, expresion}\}
```

- **$\Sigma$:**
```math
\Sigma = \{\text{int, float, if, else, while, identificador, numero, };, \text{,}, =, +, -, *, /, (, )\}
```

- **$S$:**
```math
S = \text{programa}
```

#### a. Mostrar en el archivo el proceso de eliminación de ambigüedad o justificar, en caso de no ser necesario. (0.25 pts.)

La producción de **expresión** es ambigua, ya que no define ni la precedencia ni la asociatividad de los operadores matemáticos, lo que permitiría construir más de un árbol sintáctico válido para una misma cadena (por ejemplo: `a + b * c`).

Para resolverlo, jerarquizamos las operaciones de menor a mayor precedencia con asociatividad izquierda creando nuevos no terminales (**N**):
- **$E$**: para suma y resta (`+`, `-`)
- **$T$**: para multiplicación y división (`*`, `/`)
- **$F$**: para paréntesis y valores base (`( E )`, `identificador`, `numero`)

```math
\begin{aligned}
E &\rightarrow E + T \mid E - T \mid T \\
T &\rightarrow T * F \mid T / F \mid F \\
F &\rightarrow ( E ) \mid \text{identificador} \mid \text{numero}
\end{aligned}
```

#### b. Mostrar en el archivo el proceso de eliminación de la recursividad izquierda o justificar, en caso de no ser necesario. (0.25 pts.)

Un analizador sintáctico descendente entra en ciclos infinitos si existen reglas recursivas por la izquierda. Aplicamos la regla de transformación ($A \rightarrow A\alpha \mid \beta \implies A \rightarrow \beta A', \ A' \rightarrow \alpha A' \mid \epsilon$) en las producciones que la presentan:

- **Para `declaraciones`** ($\alpha = \text{declaracion}$, $\beta = \text{declaracion}$):
```math
\begin{aligned}
\text{declaraciones} &\rightarrow \text{declaracion \ \ declaraciones'} \\
\text{declaraciones'} &\rightarrow \text{declaracion \ \ declaraciones'} \mid \epsilon
\end{aligned}
```

- **Para `lista_var`** ($\alpha = \text{, identificador}$, $\beta = \text{identificador}$):
```math
\begin{aligned}
\text{lista\_var} &\rightarrow \text{identificador \ \ lista\_var'} \\
\text{lista\_var'} &\rightarrow \text{, \ \ identificador \ \ lista\_var'} \mid \epsilon
\end{aligned}
```

- **Para `sentencias`** ($\alpha = \text{sentencia}$, $\beta = \text{sentencia}$):
```math
\begin{aligned}
\text{sentencias} &\rightarrow \text{sentencia \ \ sentencias'} \\
\text{sentencias'} &\rightarrow \text{sentencia \ \ sentencias'} \mid \epsilon
\end{aligned}
```

- **Para expresiones aritméticas ($E$ y $T$):**
```math
\begin{aligned}
E &\rightarrow T E' \\
E' &\rightarrow + \ T E' \mid - \ T E' \mid \epsilon \\
T &\rightarrow F T' \\
T' &\rightarrow * \ F T' \mid / \ F T' \mid \epsilon
\end{aligned}
```

#### c. Mostrar en el archivo el proceso de factorización izquierda o justificar, en caso de no ser necesario. (0.25 pts.)

No es necesaria. Tras eliminar la ambigüedad y la recursividad izquierda, ningún no terminal tiene dos o más producciones que compartan un prefijo común. Por ejemplo, en $E' \rightarrow +TE' \mid -TE' \mid \epsilon$, en `sentencia` (`identificador`, `if`, `while`) o en $F$ (`(`, `identificador`, `numero`), cada alternativa comienza con un símbolo terminal distinto.

#### d. Mostrar en el archivo los nuevos conjuntos N' y P', que definen G'. (0.25 pts.)

- **$N'$:**
```math
N' = \{\text{programa, declaraciones, declaraciones', declaracion, tipo, lista\_var, lista\_var', sentencias, sentencias', sentencia, } E, E', T, T', F\}
```

- **$P'$:**
```math
\begin{aligned}
1. \quad \text{programa} &\rightarrow \text{declaraciones \ \ sentencias} \\
2. \quad \text{declaraciones} &\rightarrow \text{declaracion \ \ declaraciones'} \\
3. \quad \text{declaraciones'} &\rightarrow \text{declaracion \ \ declaraciones'} \\
4. \quad \text{declaraciones'} &\rightarrow \epsilon \\
5. \quad \text{declaracion} &\rightarrow \text{tipo \ \ lista\_var} \ ; \\
6. \quad \text{tipo} &\rightarrow \text{int} \\
7. \quad \text{tipo} &\rightarrow \text{float} \\
8. \quad \text{lista\_var} &\rightarrow \text{identificador \ \ lista\_var'} \\
9. \quad \text{lista\_var'} &\rightarrow \text{, \ \ identificador \ \ lista\_var'} \\
10. \quad \text{lista\_var'} &\rightarrow \epsilon \\
11. \quad \text{sentencias} &\rightarrow \text{sentencia \ \ sentencias'} \\
12. \quad \text{sentencias'} &\rightarrow \text{sentencia \ \ sentencias'} \\
13. \quad \text{sentencias'} &\rightarrow \epsilon \\
14. \quad \text{sentencia} &\rightarrow \text{identificador} \ = \ E \ ; \\
15. \quad \text{sentencia} &\rightarrow \text{if} \ ( \ E \ ) \ \text{sentencias \ \ else \ \ sentencias} \\
16. \quad \text{sentencia} &\rightarrow \text{while} \ ( \ E \ ) \ \text{sentencias} \\
17. \quad E &\rightarrow T E' \\
18. \quad E' &\rightarrow + \ T E' \\
19. \quad E' &\rightarrow - \ T E' \\
20. \quad E' &\rightarrow \epsilon \\
21. \quad T &\rightarrow F T' \\
22. \quad T' &\rightarrow * \ F T' \\
23. \quad T' &\rightarrow / \ F T' \\
24. \quad T' &\rightarrow \epsilon \\
25. \quad F &\rightarrow \text{identificador} \\
26. \quad F &\rightarrow \text{numero} \\
27. \quad F &\rightarrow ( \ E \ )
\end{aligned}
```

2. Mostrar en el archivo la construcción de los conjuntos FIRST de la gramática _G'_. (1 pt.)

Primero identificamos el conjunto de símbolos anulables ($A_n$), es decir, aquellos no terminales que pueden derivar en $\epsilon$:

```math
A_n = \{\text{declaraciones', lista\_var', sentencias', } E', T'\}
```

Aplicando el algoritmo para calcular **FIRST** por iteraciones (agregando primero los terminales directos y $\epsilon$, y propagando los conjuntos de los no terminales iniciales hasta que no haya cambios):

| Símbolo | $It_1$ | $It_2$ | $It_3$ | $It_4$ (Final) |
| :--- | :--- | :--- | :--- | :--- |
| **programa** | $\emptyset$ | $\emptyset$ | $\emptyset$ | `{ int, float }` |
| **declaraciones** | $\emptyset$ | $\emptyset$ | `{ int, float }` | `{ int, float }` |
| **declaraciones'** | `{ ε }` | `{ ε }` | `{ int, float, ε }` | `{ int, float, ε }` |
| **declaracion** | $\emptyset$ | `{ int, float }` | `{ int, float }` | `{ int, float }` |
| **tipo** | `{ int, float }` | `{ int, float }` | `{ int, float }` | `{ int, float }` |
| **lista_var** | `{ identificador }` | `{ identificador }` | `{ identificador }` | `{ identificador }` |
| **lista_var'** | `{ ,, ε }` | `{ ,, ε }` | `{ ,, ε }` | `{ ,, ε }` |
| **sentencias** | $\emptyset$ | `{ identificador, if, while }` | `{ identificador, if, while }` | `{ identificador, if, while }` |
| **sentencias'** | `{ ε }` | `{ identificador, if, while, ε }` | `{ identificador, if, while, ε }` | `{ identificador, if, while, ε }` |
| **sentencia** | `{ identificador, if, while }` | `{ identificador, if, while }` | `{ identificador, if, while }` | `{ identificador, if, while }` |
| **$E$** | $\emptyset$ | $\emptyset$ | `{ identificador, numero, ( }` | `{ identificador, numero, ( }` |
| **$E'$** | `{ +, -, ε }` | `{ +, -, ε }` | `{ +, -, ε }` | `{ +, -, ε }` |
| **$T$** | $\emptyset$ | `{ identificador, numero, ( }` | `{ identificador, numero, ( }` | `{ identificador, numero, ( }` |
| **$T'$** | `{ *, /, ε }` | `{ *, /, ε }` | `{ *, /, ε }` | `{ *, /, ε }` |
| **$F$** | `{ identificador, numero, ( }` | `{ identificador, numero, ( }` | `{ identificador, numero, ( }` | `{ identificador, numero, ( }` |

**Conjuntos FIRST de $G'$:**
```math
\begin{aligned}
\text{FIRST}(\text{programa}) &= \{\text{int, float}\} \\
\text{FIRST}(\text{declaraciones}) &= \{\text{int, float}\} \\
\text{FIRST}(\text{declaraciones'}) &= \{\text{int, float, } \epsilon\} \\
\text{FIRST}(\text{declaracion}) &= \{\text{int, float}\} \\
\text{FIRST}(\text{tipo}) &= \{\text{int, float}\} \\
\text{FIRST}(\text{lista\_var}) &= \{\text{identificador}\} \\
\text{FIRST}(\text{lista\_var'}) &= \{\text{, }, \epsilon\} \\
\text{FIRST}(\text{sentencias}) &= \{\text{identificador, if, while}\} \\
\text{FIRST}(\text{sentencias'}) &= \{\text{identificador, if, while, } \epsilon\} \\
\text{FIRST}(\text{sentencia}) &= \{\text{identificador, if, while}\} \\
\text{FIRST}(E) &= \{\text{identificador, numero, } (\} \\
\text{FIRST}(E') &= \{+, -, \epsilon\} \\
\text{FIRST}(T) &= \{\text{identificador, numero, } (\} \\
\text{FIRST}(T') &= \{*, /, \epsilon\} \\
\text{FIRST}(F) &= \{\text{identificador, numero, } (\}
\end{aligned}
```

3. Mostrar en el archivo la construcción de los conjuntos FOLLOW de la gramática _G'_. (1 pt.)

Aplicando el algoritmo para calcular **FOLLOW** por iteraciones (colocando `$` en el símbolo inicial, agregando los conjuntos `FIRST` de los símbolos que siguen a cada no terminal y propagando el `FOLLOW` del encabezado cuando el símbolo queda al final o lo que le sigue es anulable):

| Símbolo | $It_1$ | $It_2$ | $It_3$ (Final) |
| :--- | :--- | :--- | :--- |
| **programa** | `{ $ }` | `{ $ }` | `{ $ }` |
| **declaraciones** | `{ identificador, if, while }` | `{ identificador, if, while }` | `{ identificador, if, while }` |
| **declaraciones'** | $\emptyset$ | `{ identificador, if, while }` | `{ identificador, if, while }` |
| **declaracion** | `{ int, float }` | `{ int, float, identificador, if, while }` | `{ int, float, identificador, if, while }` |
| **tipo** | `{ identificador }` | `{ identificador }` | `{ identificador }` |
| **lista_var** | `{ ; }` | `{ ; }` | `{ ; }` |
| **lista_var'** | $\emptyset$ | `{ ; }` | `{ ; }` |
| **sentencias** | `{ else }` | `{ $, else, identificador, if, while }` | `{ $, else, identificador, if, while }` |
| **sentencias'** | $\emptyset$ | `{ else }` | `{ $, else, identificador, if, while }` |
| **sentencia** | `{ identificador, if, while }` | `{ else, identificador, if, while }` | `{ $, else, identificador, if, while }` |
| **$E$** | `{ ;, ) }` | `{ ;, ) }` | `{ ;, ) }` |
| **$E'$** | $\emptyset$ | `{ ;, ) }` | `{ ;, ) }` |
| **$T$** | `{ +, - }` | `{ +, -, ;, ) }` | `{ +, -, ;, ) }` |
| **$T'$** | $\emptyset$ | `{ +, - }` | `{ +, -, ;, ) }` |
| **$F$** | `{ *, / }` | `{ *, /, +, - }` | `{ *, /, +, -, ;, ) }` |

**Conjuntos FOLLOW de $G'$:**
```math
\begin{aligned}
\text{FOLLOW}(\text{programa}) &= \{\$\} \\
\text{FOLLOW}(\text{declaraciones}) &= \{\text{identificador, if, while}\} \\
\text{FOLLOW}(\text{declaraciones'}) &= \{\text{identificador, if, while}\} \\
\text{FOLLOW}(\text{declaracion}) &= \{\text{int, float, identificador, if, while}\} \\
\text{FOLLOW}(\text{tipo}) &= \{\text{identificador}\} \\
\text{FOLLOW}(\text{lista\_var}) &= \{;\} \\
\text{FOLLOW}(\text{lista\_var'}) &= \{;\} \\
\text{FOLLOW}(\text{sentencias}) &= \{\$, \text{else, identificador, if, while}\} \\
\text{FOLLOW}(\text{sentencias'}) &= \{\$, \text{else, identificador, if, while}\} \\
\text{FOLLOW}(\text{sentencia}) &= \{\$, \text{else, identificador, if, while}\} \\
\text{FOLLOW}(E) &= \{;, )\} \\
\text{FOLLOW}(E') &= \{;, )\} \\
\text{FOLLOW}(T) &= \{+, -, ;, )\} \\
\text{FOLLOW}(T') &= \{+, -, ;, )\} \\
\text{FOLLOW}(F) &= \{*, /, +, -, ;, )\}
\end{aligned}
```

4. Mostrar en el archivo la construcción de la tabla de análisis sintáctico predictivo para _G'_. (1 pt.)

Para construir la tabla $M[A, a]$ aplicamos el algoritmo de construcción $LL(1)$:
1. Para cada producción $A \rightarrow \alpha$, se coloca en $M[A, a]$ para todo terminal $a \in \text{FIRST}(\alpha)$.
2. Si $\epsilon \in \text{FIRST}(\alpha)$ (la producción es anulable), se coloca también en $M[A, b]$ para todo terminal $b \in \text{FOLLOW}(A)$.

#### Análisis por producción

| # | Producción ($A \rightarrow \alpha$) | $\text{FIRST}(\alpha)$ | ¿Anulable? | $\text{FOLLOW}(A)$ (si aplica) |
| :-: | :--- | :--- | :-: | :--- |
| 1 | $\text{programa} \rightarrow \text{declaraciones \ sentencias}$ | `{ int, float }` | No | — |
| 2 | $\text{declaraciones} \rightarrow \text{declaracion \ declaraciones'}$ | `{ int, float }` | No | — |
| 3 | $\text{declaraciones'} \rightarrow \text{declaracion \ declaraciones'}$ | `{ int, float }` | No | — |
| 4 | $\text{declaraciones'} \rightarrow \epsilon$ | `{ ε }` | Sí | `{ identificador, if, while }` |
| 5 | $\text{declaracion} \rightarrow \text{tipo \ lista\_var} \ ;$ | `{ int, float }` | No | — |
| 6 | $\text{tipo} \rightarrow \text{int}$ | `{ int }` | No | — |
| 7 | $\text{tipo} \rightarrow \text{float}$ | `{ float }` | No | — |
| 8 | $\text{lista\_var} \rightarrow \text{identificador \ lista\_var'}$ | `{ identificador }` | No | — |
| 9 | $\text{lista\_var'} \rightarrow , \ \text{identificador \ lista\_var'}$ | `{ , }` | No | — |
| 10 | $\text{lista\_var'} \rightarrow \epsilon$ | `{ ε }` | Sí | `{ ; }` |
| 11 | $\text{sentencias} \rightarrow \text{sentencia \ sentencias'}$ | `{ identificador, if, while }` | No | — |
| 12 | $\text{sentencias'} \rightarrow \text{sentencia \ sentencias'}$ | `{ identificador, if, while }` | No | — |
| 13 | $\text{sentencias'} \rightarrow \epsilon$ | `{ ε }` | Sí | `{ $, else, identificador, if, while }` |
| 14 | $\text{sentencia} \rightarrow \text{identificador} = E \ ;$ | `{ identificador }` | No | — |
| 15 | $\text{sentencia} \rightarrow \text{if} \ ( E ) \ \text{sentencias \ else \ sentencias}$ | `{ if }` | No | — |
| 16 | $\text{sentencia} \rightarrow \text{while} \ ( E ) \ \text{sentencias}$ | `{ while }` | No | — |
| 17 | $E \rightarrow T E'$ | `{ identificador, numero, ( }` | No | — |
| 18 | $E' \rightarrow + \ T E'$ | `{ + }` | No | — |
| 19 | $E' \rightarrow - \ T E'$ | `{ - }` | No | — |
| 20 | $E' \rightarrow \epsilon$ | `{ ε }` | Sí | `{ ;, ) }` |
| 21 | $T \rightarrow F T'$ | `{ identificador, numero, ( }` | No | — |
| 22 | $T' \rightarrow * \ F T'$ | `{ * }` | No | — |
| 23 | $T' \rightarrow / \ F T'$ | `{ / }` | No | — |
| 24 | $T' \rightarrow \epsilon$ | `{ ε }` | Sí | `{ +, -, ;, ) }` |
| 25 | $F \rightarrow \text{identificador}$ | `{ identificador }` | No | — |
| 26 | $F \rightarrow \text{numero}$ | `{ numero }` | No | — |
| 27 | $F \rightarrow ( E )$ | `{ ( }` | No | — |

> **Nota sobre `sentencias'`:** Al no existir delimitadores de bloque (`{ }`) en las reglas de `if` y `while`, se presenta un conflicto `FIRST/FOLLOW` en `sentencias'` con los terminales `{ identificador, if, while }` entre las producciones **12** y **13**. Para que el analizador sea determinista y consuma todas las sentencias consecutivas, se prioriza la producción **12** (`sentencias' → sentencia sentencias'`) para `{ identificador, if, while }` y se deja la producción **13** (`ε`) exclusivamente para `{ else, EOF }`.

#### Tabla de Análisis Sintáctico Predictivo LL(1)
*(Los números corresponden al índice de cada producción en $P'$)*

| No Terminal | `int` | `float` | `id` | `num` | `if` | `else` | `while` | `;` | `,` | `=` | `+` | `-` | `*` | `/` | `(` | `)` | `EOF` |
| :--- | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| **programa** | 1 | 1 | | | | | | | | | | | | | | | |
| **declaraciones** | 2 | 2 | | | | | | | | | | | | | | | |
| **declaraciones'** | 3 | 3 | 4 | | 4 | | 4 | | | | | | | | | | |
| **declaracion** | 5 | 5 | | | | | | | | | | | | | | | |
| **tipo** | 6 | 7 | | | | | | | | | | | | | | | |
| **lista_var** | | | 8 | | | | | | | | | | | | | | |
| **lista_var'** | | | | | | | | 10 | 9 | | | | | | | | |
| **sentencias** | | | 11 | | 11 | | 11 | | | | | | | | | | |
| **sentencias'** | | | 12 | | 12 | 13 | 12 | | | | | | | | | | 13 |
| **sentencia** | | | 14 | | 15 | | 16 | | | | | | | | | | |
| **$E$** | | | 17 | 17 | | | | | | | | | | | 17 | | |
| **$E'$** | | | | | | | | 20 | | | 18 | 19 | | | | 20 | |
| **$T$** | | | 21 | 21 | | | | | | | | | | | 21 | | |
| **$T'$** | | | | | | | | 24 | | | 24 | 24 | 22 | 23 | | 24 | |
| **$F$** | | | 25 | 26 | | | | | | | | | | | 27 | | |
