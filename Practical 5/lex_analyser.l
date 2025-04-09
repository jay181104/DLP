%{
#include <stdio.h>
%}

%option noyywrap

KEYWORD      "int"|"char"|"return"|"void"|"long"|"float"|"struct"|"scanf"|"printf"
IDENTIFIER   [a-zA-Z_][a-zA-Z0-9_]*
CONSTANT     [0-9]+(\.[0-9]+)?
STRING       \'.\'
PUNCTUATION  [(){};,]
OPERATOR     [=+\-*/%]
COMMENT      \/\/.*|\/\*([^*]|\*+[^*/])*\*+\/
WHITESPACE   [ \t\n]+

%%
{KEYWORD}      { printf("Keyword: %s\n", yytext); }
{IDENTIFIER}   { printf("Identifier: %s\n", yytext); }
{CONSTANT}     { printf("Constant: %s\n", yytext); }
{STRING}       { printf("String: %s\n", yytext); }
{PUNCTUATION}  { printf("Punctuation: %s\n", yytext); }
{OPERATOR}     { printf("Operator: %s\n", yytext); }
{COMMENT}      { printf("Comment ignored\n"); }
{WHITESPACE}   { /* Ignore whitespace */ }
.              { printf("Lexical Error: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

/* Commands to run:
flex lex_analyser.l
gcc lex.yy.c -o lexer.exe
lexer.exe < input1.c
*/
