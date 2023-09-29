/* This is the lexical analysis file for a compiler  */
/* This will contain Regular Expressions for the tokens */ 
/* We are using Flex to generate the lexical analyzer */

%{
    
%}
/* Regular Expressions */
CHARACTER   "char"
ELSE        "else"
FOR         "for"
IF          "if"
INTEGER     "int"
RETURN      "return"
VOID        "void"
/* Identifier start withs a "_" or "a-z" or "A-Z". It can end there or can continue as identifier-nondigit or identifier-digit, hence the kleaner closure. */
IDENTIFIER  [_a-zA-Z][_a-zA-Z0-9]* 
/* integer-constant: 0 or (sign) nonzero-digit  or integer-constant digit */
/* nonzero-digit: 1-9; sign +,- */
INTEGER_CONSTANT    [0]|([+|-]?[1-9][0-9]*)
/* escape-sequence: any one of the \', \'', \?, \\, \a, \b, \f, \n, \r, \t, \v */
ESCAPE_SEQUENCE    [\'\"?\\abfnrtv]
/* c-char: escape-sequence or any character except single quote ', backslash \, or new line */
C_CHAR              ({ESCAPE_SEQUENCE})|([^\'\\\n])
/* c-char-sequence: c-char | c-char-sequence c-char */
CHAR_SEQUENCE       {C_CHAR}+
/* character-constant: 'c-char-sequence' where c-char-sequence = c-char | c-char-sequence c-char */
CHARACTER_CONSTANT  ([\'])({CHAR_SEQUENCE})([\'])
WHITESPACE  [ \t\n]


/* Definitions of Rules \& Actions */
%%
{CHARACTER}     {printf("<KEYWORD char>\n");}
{ELSE}          {printf("<KEYWORD else>\n");}
{FOR}           {printf("<KEYWORD for>\n");}
{IF}            {printf("<KEYWORD if>\n");}
{INTEGER}       {printf("<KEYWORD int>\n");}
{RETURN}        {printf("<KEYWORD return>\n");}
{VOID}          {printf("<KEYWORD void>\n");}
{IDENTIFIER}    {printf("<IDENTIFIER %s>\n", yytext);}
{INTEGER_CONSTANT}  {printf("<INTEGER_CONSTANT %s>\n", yytext);}
{CHARACTER_CONSTANT}    {printf("<CHARACTER_CONSTANT %s>\n", yytext);}
{WHITESPACE}    /*Ignore whitespace*/
.               {}
%%

int yywrap(){
    return 1;
}