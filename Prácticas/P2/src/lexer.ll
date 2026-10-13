%{
#include <iostream>
#include <string>
using namespace std;

#include "headers/Symbols.hpp"
#include "headers/Lexer.hpp"

int line=1;
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"

	/* def regulares para simplificar los patrones */
DIGITO      [0-9]
LETRA       [a-zA-Z_]
IDENT       {LETRA}({LETRA}|{DIGITO})*
NUMERO      {DIGITO}+(\.{DIGITO}+)?([eE][+-]?{DIGITO}+)?


%%

[ \t\r]+ {}
"\n" 	 {line++;}
"int"       { return t_int; }
"float"     { return t_float; }
"if"        { return t_if; }
"else"      { return t_else; }
"while"     { return t_while; }

{IDENT}     { return t_id; }
{NUMERO}    { return t_numero; }

";"         { return t_pyc; }
","         { return t_coma; }
"="         { return t_asign; }
"+"         { return t_suma; }
"-"         { return t_resta; }
"*"         { return t_mult; }
"/"         { return t_div; }
"("         { return t_pizq; }
")"         { return t_pder; }

<<EOF>>     { return t_eof; }

.           { cout << "ERROR LEXICO: SÃ­mbolo no reconocido '" << yytext << "' en la lÃ­nea " << line << endl; }

%%

int yyFlexLexer::yywrap(){
    return 1;
}

int Lexer::getLine()
{
    return line;
}
