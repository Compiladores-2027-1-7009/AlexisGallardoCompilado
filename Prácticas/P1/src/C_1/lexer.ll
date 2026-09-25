%{
#include <iostream>
#include <string>
using namespace std;

#include "tokens.hpp"
#include "Lexer.hpp"

%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="C_1::Lexer"
%option case-insensitive

 /* Definicion macros y RegEx */
DIG [0-9]
letra [a-zA-Z_]
alfanum [a-zA-Z0-9_]
esp [ \t\n\r]

 /* exponentes y componentes num */
exponente [eE][+-]?{DIG}+
num_real {DIG}+"."{DIG}*({exponente})?|{DIG}+{exponente}
num_entero {DIG}+

%%

 /* Reglas y acciones lexicas */
{esp}+ { /* Para ignorar los espacios, tab y saltos de linea */ }

 /* palabras reservadas */
"int"	{ return C_1::INT; }
"float"	{ return C_1::FLOAT; }
"if"	{ return C_1::IF; }
"else"	{ return C_1::ELSE; }
"while"	{ return C_1::WHILE; }

 /* Operadores y delimitadores */
"+"	{ return C_1::MAS; }
"-"	{ return C_1::MENOS; }
"*"	{ return C_1::MUL; }
"/"	{ return C_1::DIV; }
"="	{ return C_1::ASIG; }
"("	{ return C_1::LPAR; }
")"	{ return C_1::RPAR; }
","     { return C_1::COMA; }
";"	{ return C_1::PYC; }

 /* Constantes num */
{num_real}	{ return C_1::NUMERO; }
{num_entero}	{ return C_1::NUMERO; }
 
 /* identificadores */
{letra}{alfanum}* { return C_1::ID; }
 
  /* imprime ERROR LEXICO junto a un caracter si este no es reconocido */
.   { cout << "ERROR LEXICO" << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}

