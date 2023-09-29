// File to test the 3_A2.l file
#include <stdio.h>

// Pass in the yywrap() function 
int yywrap(){
    return 1;
}

int main(){
    yylex();
}