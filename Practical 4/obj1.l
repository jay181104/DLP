%{
#include <stdio.h>
%}
%%
[0-9]+     { printf("%s\n", yytext); }
[^0-9\n]+  {  }
\n         { return 0; }
%%
int main() {
    yylex();  // Call lexer
    return 0;
}
int yywrap() {
    return 1;
}

/* // flex obj1.l
// g++ lex.yy.c -o lexer -lfl
// lexer */
