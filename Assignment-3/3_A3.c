// Group 03: julius-stabs-back
// Gautam Ahuja, Nistha Singh
// Driver function for the parser

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "3_A3.tab.h"

extern void yyerror(char *s);

// We are building Bison Parser
int main(){
    // extern int yydebug; // for debugging
    // yydebug = 1;
    // Initialize the parser
    int parser = yyparse();
    // If parser returns 0, then the input is valid
    if(parser == 0){
        printf("Valid Input\n");
    }
    // If parser returns 1, then the input is invalid
    else{
        printf("Invalid Input\n");
    }
    return 0;    
}
