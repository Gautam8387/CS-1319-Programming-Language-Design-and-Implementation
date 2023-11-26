#ifndef __PARSER_H
#define __PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define size_of_void 0;
#define size_of_char 1;
#define size_of_int 4;
#define size_of_pointer 4;
#define MAX_STACK 100

// Global Symbol Tables
extern struct symboltable* currST;       // Current Symbol Table
extern struct symboltable* globalST;     // Global Symbol Table
extern struct symboltable* new_ST;       // New Symbol Table -- used in function declaration
extern struct var_type_stack var_type;// stack for storing the type of the variable
extern struct string_list* string_head; // head of the string list
extern char* yytext;        
extern void yyerror(char *s);
extern int yyparse(void);


enum symboltype_enum {
    TYPE_VOID,
    TYPE_INT,
    TYPE_CHAR,
    TYPE_PTR,
    TYPE_FUNC,
    TYPE_ARRAY
};

enum category_enum {
    TYPE_LOCAL,
    TYPE_GLOBAL,
    TYPE_PARAM,
    TYPE_TEMP
};


/**************************************************************************/
/*                        SYMBOL TABLE STRUCTURES                         */
/**************************************************************************/
struct symboltype{
    enum symboltype_enum type; // Type of symbol
    int width;                 // Size of Array (default 1)
    struct symboltype* ptr;    // Pointer to type of symbol (for TYPE_PTR)
};
typedef struct symboltype symboltype;

struct symboltableentry{       // Structure of a symbol table entry (ROW) for variables
    char* name;                // Name of symbol
    symboltype* type;          // Type of symbol
    char* initial_value;        // Initial value of symbol
    int size;                  // Size of symbol
    int offset;                // Offset of symbol
    enum category_enum category; // Category of symbol
    struct symboltable* next; // Pointer to next symboltableentry -- nested
};
typedef struct symboltableentry symboltableentry;

struct symboltable{            // Structure of a symbol table (TABLE)
    char* name;                // Name of symbol table
    struct symboltable* parent; // Pointer to parent symbol table
    int count;                 // Count of entries in symbol table
    int tempCount;             // Count of temporary variables in symbol table
    symboltableentry* _argList; // List of arguments of function
    symboltableentry** table_entries;   // Pointer to entries in symbol table -- linked list of entries
    symboltype* _retVal;        // Return type of function
    struct symboltable* next;         // Pointer to next symbol table
};
typedef struct symboltable symboltable;

/**************************************************************************/
/*      Expression, Statement, and Function Structures                    */
/**************************************************************************/
struct expression{
    symboltableentry *loc; // Pointer to symbol table entry of variable
    symboltableentry *arrBase; // Pointer to symbol table entry of array base
    bool isBool;           // Is expression boolean?
    bool isPtr;            // Is expression pointer?
    bool isArray;          // Is expression array?
    bool isFunc;           // Is expression function?
    int* trueList;         // List of true labels
    int* falseList;        // List of false labels
    int* nextList;         // List of next labels
};
typedef struct expression expression;

struct statement{
    int* nextList;         // List of next labels
};
typedef struct statement statement;

expression* create_expression();


/**************************************************************************/
/*                            VARIABLE STACK                              */
/**************************************************************************/
// stack for variable type
struct var_type_stack{
    enum symboltype_enum type[MAX_STACK]; // Type of symbol
    int top;                   // Top of stack
};
typedef struct var_type_stack var_type_stack;
// Stack Functions
void stack_intialize(var_type_stack *s);
void push(var_type_stack* stack, enum symboltype_enum type); // Push a type to the stack
enum symboltype_enum pop(var_type_stack *s); // Pop a type from the stack

// linked list for string
struct string_list{
    char* str;
    int entries;
    struct string_list* next;
};
typedef struct string_list string_list;
// String List Functions
string_list* string_list_initialize();
void ll_insert(string_list* head, char* str);
void ll_delete(string_list* head);


/**************************************************************************/
/*                        SYMBOL TABLE FUNCTIONS                          */
/**************************************************************************/
symboltableentry *lookup(symboltable* currST, char* yytext); // Lookup a symbol in the symbol table
symboltable* create_symboltable(char* name); // Create a new symbol table
symboltype* create_symboltype(enum symboltype_enum type, int width, symboltype* ptr); // Create a new symbol type
symboltableentry* gentemp(symboltype* type, char* initial_value); // Generate a temporary variableint get_size(symboltype* type); // Get the width of a symbol
void update_type(symboltableentry* entry, symboltype* type); // Update the type of a symbol
void update_table(symboltable* currST, symboltableentry* entry); // Update the symbol table
void print_ST(symboltable *currST); // Print the symbol table
void upddate_ST(symboltable* currST, symboltableentry* entry); // Update the symbol table
char* printType(symboltype* type); // Print the type of a symbol
char* printCategory(enum category_enum category); // Print the category of a symbol

#endif // __PARSER_H