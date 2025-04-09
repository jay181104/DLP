%{
#include <stdio.h>
#include <string.h>
%}
%%
[Cc]harusat    { printf("university"); }
.|\n           { putchar(yytext[0]); }

%%
int main() {
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}
