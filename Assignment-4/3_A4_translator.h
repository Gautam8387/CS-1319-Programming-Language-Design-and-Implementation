#ifndef __PARSER_H
#define __PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size_of_char = 1;
#define size_of_int = 4;
#define size_of_pointer = 4;

// Global Symbol Tables
extern struct symboltable* currST;       // Current Symbol Table
extern struct symboltable* globalST;     // Global Symbol Table
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

struct symboltype{
    enum symboltype_enum type; // Type of symbol
    int width;                 // Size of Array (default 1)
    struct symboltype* ptr;           // Pointer to type of symbol (for TYPE_PTR)
};
typedef struct symboltype symboltype;

struct symboltableentry{       // Structure of a symbol table entry (ROW) for variables
    char* name;                // Name of symbol
    symboltype* type;          // Type of symbol
    char* initial_value;        // Initial value of symbol
    int size;                  // Size of symbol
    int offset;                // Offset of symbol
    struct symboltableentry* next; // Pointer to next symboltableentry -- nested
};
typedef struct symboltableentry symboltableentry;

struct symboltable{            // Structure of a symbol table (TABLE)
    char* name;                // Name of symbol table
    struct symboltable* parent; // Pointer to parent symbol table
    int count;                 // Count of entries in symbol table
    symboltableentry* _argList; // List of arguments of function
    symboltableentry* table_entries;   // Pointer to entries in symbol table -- linked list of entries
    symboltype* _retVal;        // Return type of function
    struct symboltable* next;         // Pointer to next symbol table
};
typedef struct symboltable symboltable;

symboltableentry *lookup(symboltable* currST, char* yytext); // Lookup function for symbol table
symboltable* create_symboltable(char* name); // Create a new symbol table

void print_ST(symboltable *currST); // Print the symbol table
char* printType(symboltype* type); // Print the type of a symbol

#endif // __PARSER_H