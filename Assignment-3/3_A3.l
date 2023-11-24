/* Group 03: julius-stabs-back */
/* Gautam Ahuja, Nistha Singh */ 

/* Declarations */
%{
    #include <string.h>
    #include <stdio.h>
    #include "3_A3.tab.h" 
%}

/* Regular Expressions */

CHARACTER               "char"
ELSE                    "else"
FOR                     "for"
IF                      "if"
INTEGER                 "int"
RETURN                  "return"
VOID                    "void"

IDENTIFIER              [_a-zA-Z][_a-zA-Z0-9]* 
SIGN                    [+-]
NONZERO_DIGIT           [1-9]
DIGIT                   [0-9]
INTEGER_CONSTANT        0|{NONZERO_DIGIT}{DIGIT}*
ESCAPE_SEQUENCE         \\['"?\\abfnrtv]
C_CHAR                  ({ESCAPE_SEQUENCE})|([^\'\\\n])
CHAR_SEQUENCE           {C_CHAR}
CHARACTER_CONSTANT      ([\'])({CHAR_SEQUENCE})([\'])
CONSTANT                ({INTEGER_CONSTANT})|({CHARACTER_CONSTANT})
S_CHAR                  ({ESCAPE_SEQUENCE})|([^\"\\\n])
S_CHAR_SEQUENCE         {S_CHAR}*
STRING_LITERAL          ([\"])({S_CHAR_SEQUENCE})([\"])
/* PUNCTUATORS             "["|"]"|"("|")"|"{"|"}"|"->"|"&"|"*"|"+"|"-"|"/"|"%"|"!"|"?"|"<"|">"|"<="|">="|"=="|"!="|"&&"|"||"|"="|":"|";"|"," */
MULTI_LINE_COMMENT      (\/\*)([^\*]|\*[^\/])*(\*\/)
SINGLE_LINE_COMMENT     (\/\/)([^\n])*
COMMENT                 ({MULTI_LINE_COMMENT})|({SINGLE_LINE_COMMENT})
WHITESPACE              [ \t\n\r]


/* Definitions of Rules \& Actions */
%%
{CHARACTER}             { return CHARACTER; }
{ELSE}                  { return ELSE; }
{FOR}                   { return FOR; }
{IF}                    { return IF; }
{INTEGER}               { return INTEGER; }
{RETURN}                { return RETURN; }
{VOID}                  { return VOID; }
{IDENTIFIER}            { return IDENTIFIER; }
{INTEGER_CONSTANT}      { return INTEGER_CONSTANT; }
{CHARACTER_CONSTANT}    { return CHARACTER_CONSTANT; }
{STRING_LITERAL}        { return STRING_LITERAL; }
"["                     { return L_BOX_BRACKET; }
"]"                     { return R_BOX_BRACKET; }
"("                     { return L_PARENTHESIS; }
")"                     { return R_PARENTHESIS; }
"{"                     { return L_CURLY_BRACE; }
"}"                     { return R_CURLY_BRACE; }
"->"                    { return ARROW; }
"&"                     { return AMPERSAND; }
"*"                     { return ASTERISK; }
"+"                     { return PLUS; }
"-"                     { return MINUS; }
"!"                     { return EXCLAMATION; }
"/"                     { return DIV; }
"%"                     { return MOD; }
"<"                     { return LESS_THAN; }
">"                     { return GREATER_THAN; }
"<="                    { return LESS_THAN_EQUAL; }
">="                    { return GREATER_THAN_EQUAL; }
"=="                    { return IS_EQUAL; }
"!="                    { return NOT_EQUAL; }
"&&"                    { return LOGICAL_AND; }
"||"                    { return LOGICAL_OR; }
"?"                     { return QUESTION; }
":"                     { return COLON; }
"="                     { return ASSIGN; }
";"                     { return SEMICOLON; }
","                     { return COMMA; }
{COMMENT}               { /* Ignore Comments */ }
{WHITESPACE}            { /* Ignore Whitespace */ }
.                       { return -1; }
%%

int yywrap()
{
	return 1;
}