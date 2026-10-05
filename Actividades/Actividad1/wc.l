%option noyywrap

%{
int lineas = 0;
int palabras = 0;
int bytes = 0;
%}

%%
\n      { lineas++; bytes++; }
[^\t\r\n ]+ { palabras++; bytes += yyleng; }
.       { bytes++; }
%%

int main() {
    yylex();
    printf("%d %d %d\n", lineas, palabras, bytes);
    return 0;
}

