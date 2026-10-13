#include "headers/Parser.hpp"
#include <iostream>

namespace C_1
{
  Parser::Parser(/* args */)
  {
  }

  Parser::Parser(Lexer *lexer)
  {
    this->lexer = lexer;
  }
    
  Parser::~Parser()
  {
  }

  void Parser::programa(){
    declaraciones();
    sentencias();
  }

  /************************************************************************/
  /**                                                                    **/
  /**                       Funciones por cada NT                        **/
  /**                                                                    **/
  /************************************************************************/

void Parser::declaraciones() {
    declaracion();
    declaraciones_p();
  }

  void Parser::declaraciones_p() {
    if (token == t_int || token == t_float) {
      declaracion();
      declaraciones_p();
    }
  }

  void Parser::declaracion() {
    tipo();
    lista_var();
    match(t_pyc);
  }

  void Parser::tipo() {
    if (token == t_int) {
      match(t_int);
    } else if (token == t_float) {
      match(t_float);
    } else {
      error("Se esperaba un tipo de dato");
    }
  }

  void Parser::lista_var() {
    match(t_id);
    lista_var_p();
  }

  void Parser::lista_var_p() {
    if (token == t_coma) {
      match(t_coma);
      match(t_id);
      lista_var_p();
    }
  }

  void Parser::sentencias() {
    sentencia();
    sentencias_p();
  }

  void Parser::sentencias_p() {
    if (token == t_id || token == t_if || token == t_while) {
      sentencia();
      sentencias_p();
    }
  }

  void Parser::sentencia() {
    if (token == t_id) {
      match(t_id);
      match(t_asign);
      E();
      match(t_pyc);
    } else if (token == t_if) {
      match(t_if);
      match(t_pizq);
      E();
      match(t_pder);
      sentencias();
      match(t_else);
      sentencias();
    } else if (token == t_while) {
      match(t_while);
      match(t_pizq);
      E();
      match(t_pder);
      sentencias();
    } else {
      error("Se esperaba una sentencia");
    }
  }

  void Parser::E() {
    T();
    E_p();
  }

  void Parser::E_p() {
    if (token == t_suma) {
      match(t_suma);
      T();
      E_p();
    } else if (token == t_resta) {
      match(t_resta);
      T();
      E_p();
    }
  }

  void Parser::T() {
    F();
    T_p();
  }

  void Parser::T_p() {
    if (token == t_mult) {
      match(t_mult);
      F();
      T_p();
    } else if (token == t_div) {
      match(t_div);
      F();
      T_p();
    }
  }

  void Parser::F() {
    if (token == t_pizq) {
      match(t_pizq);
      E();
      match(t_pder);
    } else if (token == t_id) {
      match(t_id);
    } else if (token == t_numero) {
      match(t_numero);
    } else {
      error("Se esperaba '(', identificador o numero");
    }
  }

  void Parser::match(int expected) {
    if (token == expected) {
      token = eat();
    } else {
      error("Token inesperado");
    }
  }

  Token Parser::eat(){
    return (Token) lexer->yylex();
  }

  void Parser::error(string msg){
    cout << "ERROR DE SINTAXIS " << msg << " en la línea "<< lexer->getLine() <<endl;
  }   

  void Parser::parse(){
    token = eat();
    programa();
    if(token == t_eof)
      cout << "La cadena es aceptada" << endl;
    else 
      cout << "La cadena no pertenece al lenguaje generado por la gramática" << endl;
  }

}
