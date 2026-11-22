#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G'(N', T, P', S)
 *
 * Gramatica G'(N', T, P', S)
 * 
 * 1.  programa       -> declaraciones sentencias
 * 2.  declaraciones  -> declaracion declaraciones'
 * 3.  declaraciones' -> declaracion declaraciones'
 * 4.  declaraciones' -> ε
 * 5.  declaracion    -> tipo lista_var ;
 * 6.  tipo           -> int
 * 7.  tipo           -> float
 * 8.  lista_var      -> identificador lista_var'
 * 9.  lista_var'     -> , identificador lista_var'
 * 10. lista_var'     -> ε
 * 11. sentencias     -> sentencia sentencias'
 * 12. sentencias'    -> sentencia sentencias'
 * 13. sentencias'    -> ε
 * 14. sentencia      -> identificador = E ;
 * 15. sentencia      -> if ( E ) sentencias else sentencias
 * 16. sentencia      -> while ( E ) sentencias
 * 17. E              -> T E'
 * 18. E'             -> + T E'
 * 19. E'             -> - T E'
 * 20. E'             -> ε
 * 21. T              -> F T'
 * 22. T'             -> * F T'
 * 23. T'             -> / F T'
 * 24. T'             -> ε
 * 25. F              -> identificador
 * 26. F              -> numero
 * 27. F              -> ( E )
 */

/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { t_eof, t_int, t_float, t_if, t_else, t_while, t_id, t_numero, t_pyc, t_coma, t_asign, t_suma, t_resta, t_mult, t_div, t_pizq, t_der};

/**
 * 3. Determinar la enumeración para el conjunto N
 */
enum NoTerm { strEmpty = 100 /** Eempieza con 100 para evitar colision de llaves con Token en Grammar::syms*/,  nt_programa,  nt_declaraciones,  nt_declaraciones_p,  nt_declaracion,  nt_tipo,  nt_lista_var,  nt_lista_var_p,  nt_sentencias,  nt_sentencias_p,  nt_sentencia,  nt_E,  nt_Ep,  nt_T,  nt_Tp,  nt_F};

#endif // !__SYMBOLS_HPP__
