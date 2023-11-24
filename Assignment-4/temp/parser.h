#ifndef __PARSER_H
#define __PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_QUADS 10000
#define MAX_STRING_SIZE 1000

const unsigned int size_of_char = 1;
const unsigned int size_of_int = 4;
const unsigned int size_of_pointer = 4;

extern char* yytext;
extern int yyparse();

typedef struct SymTab SymTab;
typedef struct Sym Sym;
typedef struct SymType SymType;
typedef struct Quad Quad;

typedef struct Expression Expression;

extern SymTab* currST;
extern SymTab* globalST;
extern char* var_type;
extern SymTab* currST_Ptr;

typedef struct {
    char res[100];
    char op[100];
    char arg1[100];
    char arg2[100];
} Quad;

extern Quad QuadArray[1000];
extern int QuadCount;

void print_QuadArray();

#define FIND 4
#define INSERT 2

// SymTab struct
struct SymTab {
    char name[100];
    SymType* retType;
    Sym params[MAX_QUADS];
    int count;
    SymTab* parent;
    Sym table[MAX_QUADS];
    int ar[MAX_QUADS];
};

// Sym struct
struct Sym {
    char name[100];
    SymType* type;
    char init_val[100];
    int size;
    int offset;
    SymTab* nested;
    char category[10];
};

// SymType struct
struct SymType {
    char type[100];
    int width;
    SymType* arrtype;
};

// Quad struct
struct Quad {
    char res[100];
    char op[100];
    char arg1[100];
    char arg2[100];
};

void print_Quad(Quad q);
void type1(Quad q);
void type2(Quad q);

struct Expression {
    int isArray;
    int isPtr;
    int isBoolean;
    Sym* loc;
    Sym* Array;
    int truelist[MAX_QUADS];
    int falselist[MAX_QUADS];
    int nextlist[MAX_QUADS];
};

struct Statement {
    int nextlist[100];
};

void emit(char res[], char op[], char arg1[], char arg2[]);
void emitInt(char res[], char op[], int arg1, char arg2[]);
Sym* gentemp(SymType* type, char init_val[]);
void print_Quad(Quad q);
void backpatch(int list[], int address);
int* makelist(int address);
int* merge(int* l1, int* l2);
Expression* convertIntToBool(Expression* e);
Expression* convertBoolToInt(Expression* e);
Sym* convertType(Sym* s, char type[]);
int computeSize(SymType* st);
int typecheck(Sym* s1, Sym* s2);
int compareSymbolType(SymType* st1, SymType* st2);

int nextinstr();

void printType(SymType* st);

#endif