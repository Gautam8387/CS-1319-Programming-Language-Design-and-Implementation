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


/* Definitions of Rules \& Actions */
%%
{CHARACTER} {printf("CHARACTER\n");}
{ELSE}      {printf("Keyword ELSE\n");}
{FOR}       {printf("Keyword FOR\n");}
{IF}        {printf("Keyword IF\n");}
{INTEGER}   {printf("Keyword INT\n");}
{RETURN}    {printf("Keyword RETURN\n");}
{VOID}      {printf("Keyword VOID\n");}
%%

int main() {
	yylex(); /* Flex Engine */ 
	return 0;
}
