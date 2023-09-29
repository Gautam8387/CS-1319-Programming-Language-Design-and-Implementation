/* This is the lexical analysis file for a compiler  */
/* This will contain Regular Expressions for the tokens */ 
/* We are using Flex to generate the lexical analyzer */

%{
    #include <stdio.h>
%}
/* Regular Expressions */
CHARACTER   "char"
ELSE        "else"
FOR         "for"
IF          "if"
INTEGER     "int"
RETURN      "return"
VOID        "void"
WHITESPACE  [ \t\n]


/* Definitions of Rules \& Actions */
%%
{CHARACTER} {printf("<KEYWORD char>\n");}
{ELSE}      {printf("<KEYWORD else>\n");}
{FOR}       {printf("<KEYWORD for>\n");}
{IF}        {printf("<KEYWORD if>\n");}
{INTEGER}   {printf("<KEYWORD int>\n");}
{RETURN}    {printf("<KEYWORD return>\n");}
{VOID}      {printf("<KEYWORD void>\n");}
{WHITESPACE}    /*Ignore whitespace*/
%%

int yywrap(){
    return 1;
}