#include "headers/ParserLL.hpp"


ParserLL::ParserLL(Lexer *lexer)
{
    this->lexer = lexer;
    loadSyms();
    loadProds();
    loadTable();
}

ParserLL::~ParserLL()
{
}


void ParserLL::loadSyms()
{
  /*********************************************
   * 4. Agregar todos los símbolos (N'∪T) de G'*
   *********************************************/
    grammar.setNum(17, 15);
    grammar.start = nt_programa;

    // Simbolos terminales (T)
    
    grammar.addSymbol(t_eof,    Symbol(t_eof));
    grammar.addSymbol(t_int,    Symbol(t_int));
    grammar.addSymbol(t_float,  Symbol(t_float));
    grammar.addSymbol(t_if,     Symbol(t_if));
    grammar.addSymbol(t_else,   Symbol(t_else));
    grammar.addSymbol(t_while,  Symbol(t_while));
    grammar.addSymbol(t_id,     Symbol(t_id));
    grammar.addSymbol(t_numero, Symbol(t_numero));
    grammar.addSymbol(t_pyc,    Symbol(t_pyc));
    grammar.addSymbol(t_coma,   Symbol(t_coma));
    grammar.addSymbol(t_asign,  Symbol(t_asign));
    grammar.addSymbol(t_suma,   Symbol(t_suma));
    grammar.addSymbol(t_resta,  Symbol(t_resta));
    grammar.addSymbol(t_mult,   Symbol(t_mult));
    grammar.addSymbol(t_div,    Symbol(t_div));
    grammar.addSymbol(t_pizq,   Symbol(t_pizq));
    grammar.addSymbol(t_pder,   Symbol(t_pder));

    // Simbolos no terminales (N')
    grammar.addSymbol(strEmpty,           Symbol(strEmpty));
    grammar.addSymbol(nt_programa,        Symbol(nt_programa));
    grammar.addSymbol(nt_declaraciones,   Symbol(nt_declaraciones));
    grammar.addSymbol(nt_declaraciones_p, Symbol(nt_declaraciones_p));
    grammar.addSymbol(nt_declaracion,     Symbol(nt_declaracion));
    grammar.addSymbol(nt_tipo,            Symbol(nt_tipo));
    grammar.addSymbol(nt_lista_var,       Symbol(nt_lista_var));
    grammar.addSymbol(nt_lista_var_p,     Symbol(nt_lista_var_p));
    grammar.addSymbol(nt_sentencias,      Symbol(nt_sentencias));
    grammar.addSymbol(nt_sentencias_p,    Symbol(nt_sentencias_p));
    grammar.addSymbol(nt_sentencia,       Symbol(nt_sentencia));
    grammar.addSymbol(nt_E,               Symbol(nt_E));
    grammar.addSymbol(nt_Ep,             Symbol(nt_Ep));
    grammar.addSymbol(nt_T,               Symbol(nt_T));
    grammar.addSymbol(nt_Tp,             Symbol(nt_Tp));
    grammar.addSymbol(nt_F,               Symbol(nt_F));
    
}

void ParserLL::loadProds()
{
  /************************************************
   * 5. Agregar todas las producciones (P') de G' *
   ************************************************/  
    
    grammar.addProd(1,  Production(nt_programa,        {nt_declaraciones, nt_sentencias}));
    grammar.addProd(2,  Production(nt_declaraciones,   {nt_declaracion, nt_declaraciones_p}));
    grammar.addProd(3,  Production(nt_declaraciones_p, {nt_declaracion, nt_declaraciones_p}));
    grammar.addProd(4,  Production(nt_declaraciones_p, {strEmpty}));
    grammar.addProd(5,  Production(nt_declaracion,     {nt_tipo, nt_lista_var, t_pyc}));
    grammar.addProd(6,  Production(nt_tipo,            {t_int}));
    grammar.addProd(7,  Production(nt_tipo,            {t_float}));
    grammar.addProd(8,  Production(nt_lista_var,       {t_id, nt_lista_var_p}));
    grammar.addProd(9,  Production(nt_lista_var_p,     {t_coma, t_id, nt_lista_var_p}));
    grammar.addProd(10, Production(nt_lista_var_p,     {strEmpty}));
    grammar.addProd(11, Production(nt_sentencias,      {nt_sentencia, nt_sentencias_p}));
    grammar.addProd(12, Production(nt_sentencias_p,    {nt_sentencia, nt_sentencias_p}));
    grammar.addProd(13, Production(nt_sentencias_p,    {strEmpty}));
    grammar.addProd(14, Production(nt_sentencia,       {t_id, t_asign, nt_E, t_pyc}));
    grammar.addProd(15, Production(nt_sentencia,       {t_if, t_pizq, nt_E, t_pder, nt_sentencias, t_else, nt_sentencias}));
    grammar.addProd(16, Production(nt_sentencia,       {t_while, t_pizq, nt_E, t_pder, nt_sentencias}));
    grammar.addProd(17, Production(nt_E,               {nt_T, nt_Ep}));
    grammar.addProd(18, Production(nt_Ep,             {t_suma, nt_T, nt_Ep}));
    grammar.addProd(19, Production(nt_Ep,             {t_resta, nt_T, nt_Ep}));
    grammar.addProd(20, Production(nt_Ep,             {strEmpty}));
    grammar.addProd(21, Production(nt_T,               {nt_F, nt_Tp}));
    grammar.addProd(22, Production(nt_Tp,             {t_mult, nt_F, nt_Tp}));
    grammar.addProd(23, Production(nt_Tp,             {t_div, nt_F, nt_Tp}));
    grammar.addProd(24, Production(nt_Tp,             {strEmpty}));
    grammar.addProd(25, Production(nt_F,               {t_id}));
    grammar.addProd(26, Production(nt_F,               {t_numero}));
    grammar.addProd(27, Production(nt_F,               {t_pizq, nt_E, t_pder}));
}

void ParserLL::loadTable()
{

  /*************************************************
   **     6.Cargar la tabla de AS predictivo      **
   *************************************************/

    table[nt_programa][t_int]   = 1;
    table[nt_programa][t_float] = 1;

    table[nt_declaraciones][t_int]   = 2;
    table[nt_declaraciones][t_float] = 2;

    table[nt_declaraciones_p][t_int]   = 3;
    table[nt_declaraciones_p][t_float] = 3;
    table[nt_declaraciones_p][t_id]    = 4;
    table[nt_declaraciones_p][t_if]    = 4;
    table[nt_declaraciones_p][t_while] = 4;

    table[nt_declaracion][t_int]   = 5;
    table[nt_declaracion][t_float] = 5;

    table[nt_tipo][t_int]   = 6;
    table[nt_tipo][t_float] = 7;

    table[nt_lista_var][t_id] = 8;

    table[nt_lista_var_p][t_coma] = 9;
    table[nt_lista_var_p][t_pyc]  = 10;

    table[nt_sentencias][t_id]    = 11;
    table[nt_sentencias][t_if]    = 11;
    table[nt_sentencias][t_while] = 11;

    table[nt_sentencias_p][t_id]    = 12;
    table[nt_sentencias_p][t_if]    = 12;
    table[nt_sentencias_p][t_while] = 12;
    table[nt_sentencias_p][t_else]  = 13;
    table[nt_sentencias_p][t_eof]   = 13;

    table[nt_sentencia][t_id]    = 14;
    table[nt_sentencia][t_if]    = 15;
    table[nt_sentencia][t_while] = 16;

    table[nt_E][t_id]     = 17;
    table[nt_E][t_numero] = 17;
    table[nt_E][t_pizq]   = 17;

    table[nt_Ep][t_suma]  = 18;
    table[nt_Ep][t_resta] = 19;
    table[nt_Ep][t_pyc]   = 20;
    table[nt_Ep][t_pder]  = 20;

    table[nt_T][t_id]     = 21;
    table[nt_T][t_numero] = 21;
    table[nt_T][t_pizq]   = 21;

    table[nt_Tp][t_mult]  = 22;
    table[nt_Tp][t_div]   = 23;
    table[nt_Tp][t_suma]  = 24;
    table[nt_Tp][t_resta] = 24;
    table[nt_Tp][t_pyc]   = 24;
    table[nt_Tp][t_pder]  = 24;

    table[nt_F][t_id]     = 25;
    table[nt_F][t_numero] = 26;
    table[nt_F][t_pizq]   = 27;
}

int ParserLL::parse()
{
  /**************************************************
   ** 7. Implementar el algoritmo de AS predictivo **
   **************************************************/

  //Auxiliares
  stack<Symbol> pila;    
  map<Token, int>::iterator accion;    
  vector<int> body;    
  Symbol X;

  // inicia la pila con el marcador de fin de archivo y el símbolo inicial S
  pila.push(grammar.getSym(t_eof));
  pila.push(grammar.getSym(grammar.start));

  // lee el 1er token de la entrada
  token = eat();

  while (!pila.empty())
  {
      X = pila.top();

      // si la cima de la pila es el simbolo de fin de archivo
      if (X.getType() == terminal && X.getToken() == t_eof)
      {
          if (token == t_eof)
          {
              aceptar("Cadena aceptada: Fin de archivo.");
              return 0;
          }
          else
          {
              error("Error sintáctico en la línea " + to_string(lexer->getLine()) + ": se esperaba fin de archivo.");
          }
      }
      // en caso de que la cima de la pila es un simbolo terminal
      else if (X.getType() == terminal)
      {
          if (X.getToken() == token)
          {
              pila.pop();
              token = eat(); // Avanzar
          }
          else
          {
              error("Error sintáctico en la línea " + to_string(lexer->getLine()) + ": token inesperado '" + string(lexer->YYText()) + "'.");
          }
      }
      // si la cima de la pila es un simbolo no terminal
      else
      {
          NoTerm nt = X.getNoTerm();
          accion = table[nt].find(token);

          if (accion != table[nt].end())
          {
              int prodNum = accion->second;
              body = grammar.getProd(prodNum).getBody();
              pila.pop();

              // apila el cuerpo de la produccion en orden inverso (si no es epsilon)
              if (!(body.size() == 1 && body[0] == strEmpty))
              {
                  for (int i = body.size() - 1; i >= 0; i--)
                  {
                      pila.push(grammar.getSym(body[i]));
                  }
              }
          }
          else
          {
              error("Error sintáctico en la línea " + to_string(lexer->getLine()) + ": no existe transición para el token '" + string(lexer->YYText()) + "'.");
          }
      }
  }

  return 0;
}

void ParserLL::error(string msg)
{
    cout<<msg<<endl;
    exit(EXIT_FAILURE);
}

Token ParserLL::eat()
{
    return (Token) lexer->yylex();    
}

void ParserLL::aceptar(string msg)
{
    cout<<msg<<endl;
}
