/* Group 03: julius-stabs-back */
/* Gautam Ahuja, Nistha Singh */ 
/* Terminal Symbols:  %token */ 
/* Non-Terminal Symbols:  %type */
/* Start Symbol: %start */

/* Declarations */
%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    extern int yylex();     // Lexical Analyzer generated by Flex
    void yyerror(char *s);  // Error function for Bison
    extern char* yytext;    // yytext declaration
%}

%union {
    int ival;
    char* str;
};

/* start symbol */
%start translation_unit

/* Terminals */
%token CHARACTER                        // "char"
%token ELSE                             // "else"  
%token FOR                              // "for"    
%token IF                               // "if"
%token INTEGER                          // "int"
%token RETURN                           // "return"
%token VOID                             // "void"
%token L_BOX_BRACKET                    // "["
%token R_BOX_BRACKET                    // "]"
%token L_PARENTHESIS                    // "("
%token R_PARENTHESIS                    // ")"
%token L_CURLY_BRACE                    // "{"
%token R_CURLY_BRACE                    // "}"
%token ARROW                            // "->"
%token AMPERSAND                        // "&"
%token ASTERISK                         // "*"
%token PLUS                             // "+"  
%token MINUS                            // "-"
%token EXCLAMATION                      // "!"
%token DIV                              // "/"
%token MOD                              // "%"
%token LESS_THAN                        // "<"
%token GREATER_THAN                     // ">" 
%token LESS_THAN_EQUAL                  // "<="
%token GREATER_THAN_EQUAL               // ">="
%token DOUBLE_EQUAL                     // "=="
%token NOT_EQUAL                        // "!="
%token LOGICAL_AND                      // "&&"
%token LOGICAL_OR                       // "||"
%token QUESTION                         // "?"
%token COLON                            // ":"
%token ASSIGN                           // "="
%token SEMICOLON                        // ";"
%token COMMA                            // ","
%token PUNCTUATOR
%token WS

%token IDENTIFIER                       
%token <ival> INTEGER_CONSTANT
%token <str> CHARACTER_CONSTANT
%token <str> STRING_LITERAL

/* Operators Associativity and Precedence */
/* As per the slides of module 5 */
%right ASSIGN
%right QUESTION COLON
%left LOGICAL_OR
%left LOGICAL_AND
%left NOT_EQUAL DOUBLE_EQUAL
%left LESS_THAN LESS_THAN_EQUAL GREATER_THAN GREATER_THAN_EQUAL
%left PLUS MINUS
%left ASTERISK DIV MOD

%%
/* Grammar Rules */

/* EXPRESSIONS */
primary_expression : IDENTIFIER {printf("primary-expression\n");}
                   | constant {printf("primary-expression\n");}
                   | STRING_LITERAL {printf("primary-expression\n");}
                   | L_PARENTHESIS expression R_PARENTHESIS {printf("primary-expression\n");}
                   ;

constant : INTEGER_CONSTANT
         | CHARACTER_CONSTANT
         ;

postfix_expression : primary_expression {printf("postfix-expression\n");}
                   | postfix_expression L_BOX_BRACKET expression R_BOX_BRACKET {printf("postfix-expression\n");}
                   | postfix_expression L_PARENTHESIS argument_expression_list_opt R_PARENTHESIS {printf("postfix-expression\n");}
                   | postfix_expression ARROW IDENTIFIER {printf("postfix-expression\n");}
                   ;

argument_expression_list_opt : argument_expression_list
                             |
                             ;

argument_expression_list : assignment_expression {printf("argument-expression-list\n");}
                         | argument_expression_list COMMA assignment_expression {printf("argument-expression-list\n");}
                         ;

unary_expression : postfix_expression {printf("unary-expression\n");}
                 | unary_operator unary_expression {printf("unary-expression\n");}
                 ;

unary_operator : AMPERSAND {printf("unary-operator\n");}
               | ASTERISK {printf("unary-operator\n");}
               | PLUS {printf("unary-operator\n");}
               | MINUS {printf("unary-operator\n");}
               | EXCLAMATION {printf("unary-operator\n");}
               ;

multiplicative_expression : unary_expression {printf("multiplicative-expression\n");}
                          | multiplicative_expression ASTERISK unary_expression {printf("multiplicative-expression\n");}
                          | multiplicative_expression DIV unary_expression {printf("multiplicative-expression\n");}
                          | multiplicative_expression MOD unary_expression {printf("multiplicative-expression\n");}
                          ;

additive_expression : multiplicative_expression {printf("additive-expression\n");}
                    | additive_expression PLUS multiplicative_expression {printf("additive-expression\n");}
                    | additive_expression MINUS multiplicative_expression {printf("additive-expression\n");}
                    ; 

relational_expression : additive_expression {printf("relational-expression\n");}
                      | relational_expression LESS_THAN additive_expression {printf("relational-expression\n");}
                      | relational_expression GREATER_THAN additive_expression {printf("relational-expression\n");}
                      | relational_expression LESS_THAN_EQUAL additive_expression {printf("relational-expression\n");}
                      | relational_expression GREATER_THAN_EQUAL additive_expression {printf("relational-expression\n");}
                      ;

equality_expression : relational_expression {printf("equality-expression\n");}
                    | equality_expression DOUBLE_EQUAL relational_expression {printf("equality-expression\n");}
                    | equality_expression NOT_EQUAL relational_expression {printf("equality-expression\n");}
                    ;

logical_and_expression : equality_expression {printf("logical-AND-expression\n");}
                       | logical_and_expression LOGICAL_AND equality_expression {printf("logical-AND-expression\n");}
                       ;

logical_or_expression : logical_and_expression {printf("logical-OR-expression\n");}
                      | logical_or_expression LOGICAL_OR logical_and_expression {printf("logical-OR-expression\n");}
                      ;

conditional_expression : logical_or_expression {printf("conditional-expression\n");}
                       | logical_or_expression QUESTION expression COLON conditional_expression {printf("conditional-expression\n");}
                       ;

assignment_expression : conditional_expression {printf("assignment-expression\n");}
                      | unary_expression ASSIGN assignment_expression {printf("assignment-expression\n");}
                      ;

expression : assignment_expression {printf("expression\n");}
           ;

/* DECLARATIONS */

declaration : type_specifier init_declarator SEMICOLON {printf("declaration\n");}
            ;

init_declarator : declarator {printf("init-declarator\n");}
                | declarator ASSIGN initializer {printf("init-declarator\n");}
                ;

type_specifier : VOID {printf("type-specifier\n");}
               | CHARACTER {printf("type-specifier\n");}
               | INTEGER {printf("type-specifier\n");}
               ;

declarator : pointer_opt direct_declarator {printf("declarator\n");}
           ;

direct_declarator : IDENTIFIER {printf("direct-declarator\n");}
                  | IDENTIFIER L_BOX_BRACKET INTEGER_CONSTANT R_BOX_BRACKET {printf("direct-declarator\n");}
                  | IDENTIFIER L_PARENTHESIS parameter_list_opt R_PARENTHESIS {printf("direct-declarator\n");}
                  ;

pointer : ASTERISK {printf("pointer\n");}
        ;

parameter_list : parameter_declaration {printf("parameter-list\n");}
               | parameter_list COMMA parameter_declaration {printf("parameter-list\n");}
               ;

parameter_declaration : type_specifier pointer_opt identifier_opt {printf("parameter-declaration\n");}
                      ;

identifier_opt : IDENTIFIER
               | 
               ;

parameter_list_opt : parameter_list
                   | 
                   ;

pointer_opt : pointer
            | 
            ;

initializer : assignment_expression {printf("initializer\n");}
            ;

/* STATEMENTS */
statement : compound_statement {printf("statement\n");}
          | expression_statement {printf("statement\n");}
          | selection_statement {printf("statement\n");}
          | iteration_statement {printf("statement\n");}
          | jump_statement {printf("statement\n");}
          ;

compound_statement : L_CURLY_BRACE block_item_list_opt R_CURLY_BRACE {printf("compound-statement\n");}
                   ;

block_item_list : block_item {printf("block-item-list\n");}
                | block_item_list block_item {printf("block-item-list\n");}
                ;   

block_item_list_opt : block_item_list
                    | 
                    ;

block_item : declaration {printf("block-item\n");}
           | statement {printf("block-item\n");}
           ;

expression_statement : expression_opt SEMICOLON {printf("expression-statement\n");}
                     ;

selection_statement : IF L_PARENTHESIS expression R_PARENTHESIS statement {printf("selection-statement\n");}
                    | IF L_PARENTHESIS expression R_PARENTHESIS statement ELSE statement {printf("selection-statement\n");}
                    ;

iteration_statement : FOR L_PARENTHESIS expression_opt SEMICOLON expression_opt SEMICOLON expression_opt R_PARENTHESIS statement {printf("iteration-statement\n");}
                    ;

jump_statement : RETURN expression_opt SEMICOLON {printf("jump-statement\n");}
               ;

expression_opt : expression
               |
               ;

/* TRANSLATION UNIT */
translation_unit : function_definition {printf("translation-unit\n");}
                 | declaration {printf("translation-unit\n");}
                 ;

function_definition : type_specifier declarator compound_statement {printf("function-definition\n");}
                    ;

%%
/* C++ Code for functions */

void yyerror(char *s) {
    printf("Error: %s on '%s'\n", s, yytext);
}