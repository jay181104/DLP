%{
#include <stdio.h>
int char_count = 0, word_count = 0, line_count = 0;
%}
%%
.           { char_count++; }
\n          { char_count++; line_count++; }
[ \t]+      { }   // Ignore spaces and tabs
[a-zA-Z0-9]+ { word_count++; char_count += yyleng; }
%%
int main() {
    yylex();
    printf("\nCharacters: %d\nWords: %d\nLines: %d\n", char_count, word_count, line_count);
    return 0;
}
int yywrap() {
    return 1;
}
