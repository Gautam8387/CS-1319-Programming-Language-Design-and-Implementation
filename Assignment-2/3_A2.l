/* This is the lexical analysis file for a compiler  */
/* This will contain Regular Expressions for the tokens */ 
/* We are using Flex to generate the lexical analyzer */

%{
    #include <stdio.h>
}%

CHAR    "char"
ELSE    "else"
FOR     "for"
IF      "if"
INT     "int"
RETURN  "return"
VOID    "void"


/* Definitions of Rules \& Actions */
%%
{CHAR}  {printf("CHAR\n");}
{ELSE}  {printf("ELSE\n");}
{FOR}   {printf("FOR\n");}
{IF}    {printf("IF\n");}
{INT}   {printf("INT\n");}
{RETURN}    {printf("RETURN\n");}
{VOID}  {printf("VOID\n");}

%%

/* C functions */
int main() {
	yylex(); /* Flex Engine */ 
	return 0;
}
