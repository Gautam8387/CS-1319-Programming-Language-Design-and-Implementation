// Group 03: julius-stabs-back
// Gautam Ahuja, Nistha Singh
// Initialize the yylex() function for the lexer
int yylex();
// main to drive the yylex() engine
int main() {
    int token;
    token = yylex();
        // Check if incoming token is INVALID (not in grammar)
    if(token == -1){
        // Stop the program immediately
        return 0;
    }
    return 0;
}