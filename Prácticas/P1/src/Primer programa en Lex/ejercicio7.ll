%{
  #include <iostream>
%}

%option c++
%option noyywrap


digito          [0-9]
digito_hex      [0-9a-fA-F]
letra           [a-zA-Z_]
alfanumerico    [a-zA-Z0-9_]
espacio         [ \t\n\r]

	/* 7.1 Expresión regular para hexadecimales en C++ (ej: 0x1A, 0X2b, 0x0) */
hexadecimal     0[xX]{digito_hex}+

	/* 7.2 Cinco palabras reservadas de C++ */
reservada       int|float|if|else|while

	/* 7.3 Identificadores válidos en C++ con longitud máxima de 32 caracteres */
	/* Inicia con letra o guion bajo, seguido de 0 a 31 caracteres alfanuméricos */
identificador   {letra}{alfanumerico}{0,31}

%%

	

	/* 7.4 Espacios en blanco (se ignoran) */
{espacio}+      { /* Acción léxica vacía para descartar espacios */ }

	/* Las palabras reservadas deben evaluarse antes que los identificadores */
{reservada}     { std::cout << "Palabra reservada: " << yytext << std::endl; }
{hexadecimal}   { std::cout << "Hexadecimal: " << yytext << std::endl; }
{identificador} { std::cout << "Identificador: " << yytext << std::endl; }
{digito}+       { std::cout << "Número decimal: " << yytext << std::endl; }

.               { std::cout << "Carácter no reconocido: " << yytext << std::endl; }

%%

	
int main() {
  FlexLexer* lexer = new yyFlexLexer;
  lexer->yylex();
  delete lexer;
  return 0;
}

