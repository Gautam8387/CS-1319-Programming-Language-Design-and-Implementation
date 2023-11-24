// Group 03: julius-stabs-back
// Gautam Ahuja, Nistha Singh

#include "3_A4_translator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "3_A4.tab.h"

extern void yyerror(char *s); // This function is called when there is a parsing error
extern int yyparse(void);
symboltable* globalST;
symboltable* currST;


symboltableentry *lookup(symboltable* currST, char* yytext){
    for(int i=0; i<currST->count; i++){ // for all the entries in the symbol table, check if the name matches
        if(strcmp(currST->table_entries[i].name, yytext) == 0){
            return &(currST->table_entries[i]); // return the entry if found
        }
    }
    // check if the entry is in the parent symbol table
    if(currST->parent != NULL){
        if(lookup(currST->parent, yytext) != NULL){
            return lookup(currST->parent, yytext);
        }
    }
    // Create a new entry if not found
    symboltableentry* entry = (symboltableentry*)malloc(sizeof(symboltableentry));
    entry->name = strdup(yytext);
    entry->type = NULL;
    entry->initial_value = NULL;
    entry->size = 0;
    entry->offset = 0;
    entry->next = NULL;
    // insert the entry in the symbol table
    currST->table_entries = (symboltableentry*)realloc(currST->table_entries, sizeof(symboltableentry)*(currST->count+1));
    currST->table_entries[currST->count] = *entry;
    currST->count++;
    return entry;
}

symboltable* create_symboltable(char* name){
    symboltable* newST = (symboltable*)malloc(sizeof(symboltable));
    newST->name = name;
    newST->parent = NULL;
    newST->count = 0;
    newST->_argList = NULL;
    newST->table_entries = NULL;
    newST->_retVal = NULL;
    newST->next = NULL;
    return newST;
}

char* printType(symboltype* type){
    if(type == NULL){
        return "NULL";
    }
    switch(type->type){
        case TYPE_VOID:
            return "void";
        case TYPE_INT:
            return "int";
        case TYPE_CHAR:
            return "char";
        case TYPE_PTR:
            char* str = (char*)malloc(sizeof(char)*10);
            sprintf(str, "%s*", printType(type->ptr));
            return str;
        case TYPE_ARRAY:
            char* str1 = (char*)malloc(sizeof(char)*50);
            sprintf(str1, "array(%d,%s)", type->width, printType(type->ptr));
            return str1;
        case TYPE_FUNC:
        // TO EDIT: int x (int, char) -> int, etc.
            return "function";
        default:
            return "NULL";
    }
}

void print_ST(symboltable *currST){
    printf("------------------------------------------------------------------------------------------------------------------\n");
    (currST->parent)?printf("Symbol Table: %s\t\t\t\t\t\t\t Parent: %s\n\n", currST->name, currST->parent->name):printf("Symbol Table: %s\t\t\t\t\t\t\t Parent: NULL\n", currST->name);
    // lines
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("Name\t\tType\t\tInitial Value\t\tSize\t\tOffset\t\tNested Table\n");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0; i< currST->count; i++){
        symboltableentry* entry = &(currST->table_entries[i]);
        printf("%s\t\t", entry->name);
        printf("%s\t\t", printType(entry->type));
        printf("%s\t\t", entry->initial_value);
        printf("%d\t\t", entry->size);
        printf("%d\t\t", entry->offset);
        if(entry->next != NULL){
            printf("%s\n", entry->next->name);
        }
        else{
            printf("NULL\n");
        }
    }
    printf("\n");
    printf("------------------------------------------------------------------------------------------------------------------\n\n");
}

/*
TODO:
- Add a function to print the symbol table
- Add UPDATE
    = Add a function to update_type the symbol table entry
    = Add a function to update_size the symbol table entry

*/

int main(){
    globalST = create_symboltable("Global");
    currST = globalST;
    yyparse();
    printf("Global Symbol Table:\n");
    print_ST(globalST);
    return 0;
}