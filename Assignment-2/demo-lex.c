// The Whole block is a lex
// Take This block and I am writing a C code in between
%{
	#include <stdio.h>
	#include <stdlib.h>
%}
// Definition Section
DIGITS [0-9] 	// Character class 
ALPHA [a-z]

%%
// RULES -- Linear in order

// Check for digit first
{DIGITS} {
	printf("Digit: %s\n", yytext);
	// Returns after digit exits.
	return 5;
}

// THIS recognizes [digit-alpha] eg, 0a, 2h, etc.
{DIGITS}{ALPHA} {
	printf("Digit: %s\n", yytext);
	// Returns after digit exits.
	return 5;
}

// Check for alphabet then
{ALPHA} {
	printf("Alpha: %s\n", yytext);
	return 6;
}

// Any other
. {
	printf("Invalid Input: %s\n", );
	return yywrap();
	// flex used for batches of files. If we do not do a yywrap() it wont return.
}
%%

// C CODE PART 

int yywrap(){
	return 1;
}

int main(){
	int token;
	// call the lexer.
	yylex(); // without return
	// if return in rules
	while(token == yylex()){
		printf("%d\n", token);
	}

}


// Compile: flex test.l
// gcc lex.yy.c