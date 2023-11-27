// Group 03: julius-stabs-back
// Gautam Ahuja, Nistha Singh

#include "3_A4_translator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "3_A4.tab.h"

extern void yyerror(char *s); // This function is called when there is a parsing error
extern int yyparse(void);

/**************************************************************************/
/*      Expression, Statement, and Function Structures                    */
/**************************************************************************/
expression* create_expression(){
    expression* newExp = (expression*)malloc(sizeof(expression));
    newExp->isBool = false;
    newExp->isArray = false;
    newExp->isPtr = false;
    newExp->isFunc = false;
    newExp->loc = NULL;
    newExp->arrBase = NULL;
    newExp->trueList = NULL;
    newExp->falseList = NULL;
    newExp->nextList = NULL;
    return newExp;
}


/**************************************************************************/
/*                            VARIABLE STACK                              */
/**************************************************************************/
var_type_stack var_type;
void stack_intialize(var_type_stack *s){
    // printf("Initializing Stack\n");
    s->top = -1;
}
void push(var_type_stack *s, enum symboltype_enum type){
    if(s->top == MAX_STACK-1){
        // yyerror("Stack Overflow");
        exit(1);
    }
    s->top++;
    s->type[s->top] = type;
    // printf("Pushed %d\n", type);
}
enum symboltype_enum pop(var_type_stack *s){
    if(s->top == -1){
        // yyerror("Stack Underflow");
        exit(1);
    }
    enum symboltype_enum type = s->type[s->top];
    s->top--;
    return type;
}

string_list* string_head;
string_list* string_list_initialize(){
    string_list* head = (string_list*)malloc(sizeof(string_list));
    head->str = NULL;
    head->entries = 0;
    head->next = NULL;
    return head;
}
void ll_insert(string_list* head, char* str){
    // check if it is the first entry
    if(head->str == NULL){
        head->str = strdup(str);
        head->entries++;
        return;
    }
    // insert new entry at the end
    string_list* temp = (string_list*)malloc(sizeof(string_list));
    temp->str = strdup(str);
    // compute the number of entries
    int count = 0;
    string_list* curr = head;
    while(curr->next != NULL){
        count++;
        curr = curr->next;
    }
    temp->entries = count+1;
    temp->next = NULL;
    curr->next = temp;    
}

void ll_delete(string_list* head){
    string_list* curr = head;
    while(curr != NULL){
        string_list* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

/**************************************************************************/
/*                        SYMBOL TABLE FUNCTIONS                          */
/**************************************************************************/
symboltable* globalST;          // pointer to Global Symbol Table
symboltable* currST;            // pointer to Current Symbol Table
symboltable* new_ST;            // pointer to new Symbol Table  -- used in function declaration

// return the size of the type
int get_size(symboltype* type){
    if(type == NULL){
        return 0;
    }
    switch(type->type){
        case TYPE_VOID:
            return size_of_void;
        case TYPE_INT:
            return size_of_int;
        case TYPE_CHAR:
            return size_of_char;
        case TYPE_PTR:
            return size_of_pointer;
        case TYPE_ARRAY:
            return type->width * get_size(type->ptr);
        case TYPE_STRING:
            return type->width;
    }
}

// update the size of the symbol table entry
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
            sprintf(str, "*%s", printType(type->ptr));
            return str;
        case TYPE_ARRAY:
            char* str1 = (char*)malloc(sizeof(char)*50);
            sprintf(str1, "array(%d,%s)", type->width, printType(type->ptr));
            return str1;
        case TYPE_FUNC:
        // TO EDIT: int x (int, char) -> int, etc.
            return "function";
        case TYPE_STRING:
            return "string";
        default:
            return "NULL";
    }
}

// print category of the symbol table entry
char* printCategory(enum category_enum category){
    switch(category){
        case TYPE_LOCAL:
            return "local";
        case TYPE_GLOBAL:
            return "global";
        case TYPE_PARAM:
            return "param";
        case TYPE_TEMP:
            return "temp";
        default:
            return "NULL";
    }
}

// lookup if entry exist, create if dont.
symboltableentry *lookup(symboltable* currST, char* yytext){
    // printf("Symbol LookUp in table, %s\n", currST->name);
    for(int i=0; i <currST->count; i++){ // for all the entries in the symbol table, check if the name matches
        if(strcmp((currST->table_entries[i])->name, yytext) == 0){
            return (currST->table_entries[i]); // return the entry if found
        }
    }
    // printf("Symbol not found. CHecking in parent table\n");
    // check if the entry is in the parent symbol table
    if(currST->parent != NULL){
        if(lookup(currST->parent, yytext) != NULL){
            return lookup(currST->parent, yytext);
        }
    }
    // printf("Symbol not found in parent table. Creating a new entry for \"%s\"\n", yytext);
    // Create a new entry if not found
    symboltableentry* entry = (symboltableentry*)malloc(sizeof(symboltableentry));
    entry->name = strdup(yytext);
    entry->type = NULL;
    entry->initial_value = NULL;
    entry->size = 0;
    entry->offset = 0;
    entry->next = NULL;
    (currST->parent)?(entry->category = TYPE_LOCAL):(entry->category = TYPE_GLOBAL); // if parent is not null, then it is local, else global
    // insert the entry in the symbol table
    currST->table_entries = (symboltableentry**)realloc(currST->table_entries, sizeof(symboltableentry)*(currST->count+1));
    currST->table_entries[currST->count] = entry;
    currST->count++;
    return entry;
}

// cretae a new symbol table with ONLY name set
symboltable* create_symboltable(char* name){
    symboltable* newST = (symboltable*)malloc(sizeof(symboltable));
    newST->name = name;
    newST->parent = NULL;
    newST->count = 0;
    newST->tempCount = 0;
    newST->_argList = NULL;
    newST->table_entries = NULL;
    newST->_retVal = NULL;
    newST->next = NULL;
    return newST;
}

// create a new symbol type with type. width by default is 1. Pointer is NULL by default
symboltype* create_symboltype(enum symboltype_enum type, int width, symboltype* ptr){
    symboltype* newType = (symboltype*)malloc(sizeof(symboltype));
    newType->type = type;
    newType->width = width;
    newType->ptr = ptr;
    return newType;
}

// update type and size of of the symbol table entry
void update_type(symboltableentry* entry, symboltype* type){
    // printf("Pointer to entry: %p\n", entry);
    // printf("Pointer to type: %p\n", type);
    entry->type = type;
    entry->size = get_size(type);
    // printf("Updated type of %s to %s\n", entry->name, printType(type));
    return;
}

// generate a temporary variable.
// the lookup function generates and stores the entry in currentST.
symboltableentry* gentemp(symboltype* type, char* initial_value) {
    char tempName[20];
    sprintf(tempName, "t%d", currST->tempCount++);
    // Lookup or create a new entry for the temporary variable
    symboltableentry* tempEntry = lookup(currST, tempName);
    // Update type and initial value
    update_type(tempEntry, type);
    (initial_value==NULL)?(tempEntry->initial_value = NULL):(tempEntry->initial_value = strdup(initial_value));
    tempEntry->category = TYPE_TEMP;
    return tempEntry;
}


// Print the symbol table
void print_ST(symboltable *currST){
    printf("=============================================================================================================\n");
    (currST->parent)?printf("Symbol Table: %s\t\t\t\t\t\t\t Parent: %s\n\n", currST->name, currST->parent->name):printf("Symbol Table: %s\t\t\t\t\t\t\t Parent: NULL\n", currST->name);
    // lines
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("Name\tType\tCategory\tInitial Value\tSize\tOffset\tNested Table\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    for(int i=0; i< currST->count; i++){
        symboltableentry* entry = (currST->table_entries[i]);
        printf("%s\t", entry->name);
        printf("%s\t", printType(entry->type));
        printf("%s\t\t", printCategory(entry->category));
        printf("%s\t\t", entry->initial_value);
        printf("%d\t", entry->size);
        printf("%d\t", entry->offset);
        if(entry->next != NULL){
            printf("%s\n", entry->next->name);
        }
        else{
            printf("NULL\n");
        }
    }
    printf("\n");
    printf("=============================================================================================================\n\n");
}

/*
TODO:
    - emit()
    - backpatch()
    - merge()
    - makelist()
    - nextinstr()
    - Array Declaration -- width setup
    - Function Declaration
    - Size of Array (width)
    - typecheck() and type_conversion()
    - Quads
    - TAC
*/

int main(){
    printf("Initializing Symbol Tables\n");
    globalST = create_symboltable("Global");
    currST = globalST;
    stack_intialize(&var_type);
    string_head = string_list_initialize();
    // gentemp test
    // symboltableentry* temp = gentemp(create_symboltype(TYPE_INT, 1, NULL), "69");
    // gentemp update test
    printf("Starting Parser\n");
    yyparse();
    printf("Global Symbol Table:\n");
    print_ST(globalST);
    return 0;
}