#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations
struct SymTab;
struct Sym;
struct SymType;
struct Quad;
struct Expression;
struct Statement;

// Symbol Table Flags
#define FIND 4
#define INSERT 2

// Global Symbol Tables
extern struct SymTab* currST;
extern struct SymTab* globalST;

// Global Variables
extern char* yytext;
extern int yyparse();
extern char* var_type;
extern struct SymTab* currST_Ptr;

// Quad Structure
struct Quad {
    char res[256];   // Result
    char op[256];    // Operator
    char arg1[256];  // Argument 1
    char arg2[256];  // Argument 2
};

// Symbol Table Entry Structure
struct Sym {
    char name[256];        // Name of the symbol
    struct SymType* type;  // Type of the symbol
    char init_val[256];    // Initial value of the symbol if specified
    int size;              // Size of the symbol
    int offset;            // Offset of symbol in Symbol Table
    struct SymTab* nested; // Points to the nested symbol table
    char category[10];     // Category of the symbol (global, local, or param)
};

// Symbol Type Structure
struct SymType {
    char type[256];       // Type of the symbol
    int width;            // Size of Array (if an Array) and default 1 otherwise
    struct SymType* arrtype;  // Stores the array type if applicable
};

// Symbol Table Structure
struct SymTab {
    char name[256];          // Name of the Table
    struct SymType* retType;  // Return type of the function
    struct Sym* params;       // Parameters of the function
    int count;                // Count of temporary variables
    struct SymTab* parent;    // Parent ST of the current ST
    struct Sym** table;       // Symbol Table implemented as a map
};

// Expression Structure
struct Expression {
    struct Sym* loc;  // Pointer to the symbol table entry of the expression
    int isBoolean;
    struct Sym* Array;
    int isArray;
    int isPtr;
    int* truelist;    // Truelist for boolean expression
    int* falselist;   // Falselist for boolean expression
    int* nextlist;    // Nextlist for other types of expressions
};

// Statement Structure
struct Statement {
    int* nextlist;  // Nextlist for Statement with dangling exit
};

// Function Declarations
void print_QuadArray();
struct SymTab* lookup(char* name, int flags);
void update_offsets(struct SymTab* symtab);
void print(struct SymTab* symtab);
struct Sym* create_Sym(char* name, char* t, struct SymType* ptr, int width);
struct Sym* update(struct Sym* sym, struct SymType* type);
struct SymType* create_SymType(char* type, struct SymType* ptr, int width);
struct Quad* create_Quad(char* res, char* op, char* arg1, char* arg2);
void print_Quad(struct Quad* quad);
struct Expression* create_Expression();
struct Statement* create_Statement();
void emit(char* res, char* op, char* arg1, char* arg2);
struct Sym* gentemp(struct SymType* type, char* init_val);
void backpatch(int* list, int address);
int* makelist(int address);
int* merge(int* l1, int* l2);
struct Expression* convertIntToBool(struct Expression* expr);
struct Expression* convertBoolToInt(struct Expression* expr);
struct Sym* convertType(struct Sym* sym, char* type);
int computeSize(struct SymType* type);
int typecheck(struct Sym* s1, struct Sym* s2);
int compareSymbolType(struct SymType* type1, struct SymType* type2);
int nextinstr();
char* printType(struct SymType* type);

#endif
