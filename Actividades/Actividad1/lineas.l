%option noyywrap
%option yylineno

%%
\n      { printf("\n%d\t", yylineno); }
.       { ECHO; }
%%

int main() {
    printf("1\t"); /* Me da algo de ansiedad que no se empiece con el 1 xd */
    yylex();
    return 0;
}

