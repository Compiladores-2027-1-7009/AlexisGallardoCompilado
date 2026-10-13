#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/**
 * 1. Definir en un comentario la gramÃ¡tica G(N, T, P, S)
 * N = { programa, declaraciones, declaraciones_p, declaracion, tipo, lista_var, lista_var_p, sentencias, sentencias_p, sentencia, E, E_p, T, T_p, F }
 * T = { int, float, if, else, while, identificador, numero, ;, ,, =, +, -, *, /, (, ) }
 * S = programa
 * P = {
 *   programa -> declaraciones sentencias
 *   declaraciones -> declaracion declaraciones_p
 *   declaraciones_p -> declaracion declaraciones_p | epsilon
 *   declaracion -> tipo lista_var ;
 *   tipo -> int | float
 *   lista_var -> identificador lista_var_p
 *   lista_var_p -> , identificador lista_var_p | epsilon
 *   sentencias -> sentencia sentencias_p
 *   sentencias_p -> sentencia sentencias_p | epsilon
 *   sentencia -> identificador = E ; | if ( E ) sentencias else sentencias | while ( E ) sentencias
 *   E -> T E_p
 *   E_p -> + T E_p | - T E_p | epsilon
 *   T -> F T_p
 *   T_p -> * F T_p | / F T_p | epsilon
 *   F -> ( E ) | identificador | numero
 * }
 */

// 2. Determinar la enumeración para el conjunto T
enum Token { primero, t_eof, t_int, t_float, t_if, t_else, t_while, t_id, t_numero, t_pyc, t_coma, t_asign, t_suma, t_resta, t_mult, t_div, t_pizq, t_pder };

// 3. Determinar la enumeración para el conjunto N
enum NoTerm { strEmpty, nt_programa, nt_declaraciones, nt_declaraciones_p, nt_declaracion, nt_tipo, nt_lista_var, nt_lista_var_p, nt_sentencias, nt_sentencias_p, nt_sentencia, nt_E, nt_E_p, nt_T, nt_T_p, nt_F };

#endif // !__SYMBOLS_HPP__
