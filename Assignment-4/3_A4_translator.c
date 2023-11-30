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
/*                        GLOBAL VARIABLES                                */
/**************************************************************************/
qArray* quadArray;           // pointer to the head of the quad array linked list
var_type_stack var_type;            // declare the stack
string_list* string_head;           // linked list for string literals
symboltable* globalST;              // pointer to Global Symbol Table
symboltable* currST;                // pointer to Current Symbol Table
symboltable* new_ST;                // pointer to new Symbol Table  -- used in function declaration
static int tempCount = 0;               // count of the temporary variables



/**************************************************************************/
/*      Expression, Statement, and Function Structures                    */
/**************************************************************************/
// to create a new expression
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
    newExp->nextList = (int*)malloc(sizeof(int));
    newExp->nextList[0] = -1;
    newExp->returnLabel = 0;
    return newExp;
}

// to create a new statement
statement* create_statement(){
    statement* newStmt = (statement*)malloc(sizeof(statement));
    // end of list is -1
    newStmt->nextList = (int*)malloc(sizeof(int));
    newStmt->nextList[0] = -1;
    newStmt->returnLabel = 0;
    return newStmt;
}

// backpatch() -- backpatch a list of labels with a label
// nextList is updated by nextInstr() which already increments the count -- no need to increment again
// point directly to the required instruction in quadArray
void backpatch(int* list, int label){
    // printf("Backpatching\n");
    char str[50];
    sprintf(str, "%d", label);
    if (str==NULL){
        str[0] = '0';
    }
    // printf("\n\nList[%d]: %d\n\n", i, list[i]);
    // list contains the list of labels to be backpatched
    int i=0;
    while(list[i] != -1){
        // printf("List[%d]: %d\n", i, list[i]);
        // go to list[i] of quadArray and update the result
        // quadArray is a linked list of quad arrays
        qArray* curr = quadArray;
        while(curr->count != list[i]){
            curr = curr->nextQuad;
        }
        // update the result
        curr->arr->result = strdup(str);
        // printf("Updated result: %s\n", curr->arr->result);
        i=i+1;
    }
    return;
}

// makelist
int* makelist(int label){
    int* list = (int*)malloc(2*sizeof(int));
    list[0] = label;
    list[1] = -1;
    return list;
}

// merge
int* merge(int* list1, int* list2){
    // get lengths of both lists
    int len1 = 0;
    while(list1[len1] != -1){
        len1++;
    }
    int len2 = 0;
    while(list2[len2] != -1){
        len2++;
    }
    // create a new list
    int* newMerged = (int*)calloc((len1+len2+1), sizeof(int));
    int i=0;
    while(list1[i] != -1){
        newMerged[i] = list1[i];
        i++;
    }
    int j=0;
    while(list2[j] != -1){
        // Check if list2[j] is already in newMerged
        int k;
        for (k = 0; k < i; ++k) {
            if (newMerged[k] == list2[j]) {
                break;
            }
        }
        // If list2[j] is not already in newMerged, add it
        if (k == i) {
            newMerged[i] = list2[j];
            i++;
        }
        j++;
    }
    newMerged[i] = -1;
    return newMerged;
}

// Bool to Int
expression* bool2int(expression* expr){
    if(expr->isBool){
        // generate a new temp 
        expr->loc = gentemp(create_symboltype(TYPE_INT, 1, NULL), NULL);
        // backpatch the true list with next instruction
        backpatch(expr->trueList, nextInstr());
        // emit the quad for true
        emit(OP_ASSIGN, "true", NULL, expr->loc->name);
        // goto the end of the false list
        char str[100];
        int pNext = nextInstr()+1;
        sprintf(str, "%d", pNext);
        emit(OP_GOTO, NULL, NULL, str);
        // backpatch the false list with next instruction
        backpatch(expr->falseList, nextInstr());
        // emit the quad for false
        emit(OP_ASSIGN, "false", NULL, expr->loc->name);
    }
    return expr;
}

// Int to Bool
expression* int2bool(expression* expr){
    if(expr->isBool == false){
        expr->falseList = makelist(nextInstr());
        // emit == 0
        emit(OP_EQUALS, expr->loc->name, "0", NULL);
        // print_quadArray(quadArray);
        expr->trueList = makelist(nextInstr());
        // emit goto
        emit(OP_GOTO, NULL, NULL, NULL);
    }
    return expr;
}

/**************************************************************************/
/*                            VARIABLE STACK                              */
/**************************************************************************/

// stact initialization
void stack_intialize(var_type_stack *s){
    // printf("Initializing Stack\n");
    s->top = -1;
}

// push -- add a new type to the stack at end
void push(var_type_stack *s, enum symboltype_enum type){
    if(s->top == MAX_STACK-1){
        // yyerror("Stack Overflow");
        exit(1);
    }
    s->top++;
    s->type[s->top] = type;
    // printf("Pushed %d\n", type);
}

// pop -- remove the last type from the stack
enum symboltype_enum pop(var_type_stack *s){
    if(s->top == -1){
        // yyerror("Stack Underflow");
        exit(1);
    }
    enum symboltype_enum type = s->type[s->top];
    s->top--;
    return type;
}

// String List initialization -- create a new head
string_list* string_list_initialize(){
    string_list* head = (string_list*)malloc(sizeof(string_list));
    head->str = NULL;
    head->entries = 0;
    head->next = NULL;
    return head;
}

// insert a new string at the end of the linked list
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

// delete the linked list end entry
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
        case TYPE_FUNC:
            return 0;
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

// check the types of two symbol types. 1 == true, 0 == false
int typecheck(symboltype* type1, symboltype* type2){
    if(type1 == NULL && type2 == NULL){
        return 0;
    }
    if(type1->type == type2->type){
        if(type1->type == TYPE_ARRAY || type1->type == TYPE_PTR){
            return typecheck(type1->ptr, type2->ptr);
        }
        else{
            return 1;
        }
    }
    else{
        return 0;
    }
}


// parent lookup -- lookup in the parent symbol table
symboltableentry* parentLookup(symboltable* currST, char* yytext){
    for(int i=0; i < currST->count; i++){ // for all the entries in the symbol table, check if the name matches
        if(strcmp((currST->table_entries[i])->name, yytext) == 0){
            return (currST->table_entries[i]); // return the entry if found
        }
    }
    return NULL;
}
// lookup if entry exist, create if dont.
symboltableentry *lookup(symboltable* currST, char* yytext){
    // printf("\nSymbol %s LookUp in table, %s\n", yytext, currST->name);
    for(int i=0; i <currST->count; i++){ // for all the entries in the symbol table, check if the name matches
        if(strcmp((currST->table_entries[i])->name, yytext) == 0){
            return (currST->table_entries[i]); // return the entry if found
        }
    }
    // check if the entry is in the parent symbol table
    if(currST->parent != NULL){
        // printf("Symbol not found. Checking in parent table \"%s\"\n", currST->parent->name);
        symboltableentry* parentEntry = parentLookup(currST->parent, yytext);
        if(parentEntry){
            return parentEntry;
        }
    }
    // printf("\nSymbol not found in parent table. Creating a new entry for \"%s\" in %s\n", yytext, currST->name);
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
symboltable* create_symboltable(char* name, symboltable* parent){
    symboltable* newST = (symboltable*)malloc(sizeof(symboltable));
    newST->name = name;
    newST->parent = parent;
    newST->count = 0;
    // newST->tempCount = 0;
    newST->paramCount = 0;
    newST->_argList = NULL;
    newST->table_entries = NULL;
    newST->_retVal = NULL;
    newST->next = NULL;
    newST->returnLabel = 0;
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
    sprintf(tempName, "t%d", tempCount++);
    // Lookup or create a new entry for the temporary variable
    symboltableentry* tempEntry = lookup(currST, tempName);
    // Update type and initial value
    update_type(tempEntry, type);
    (initial_value==NULL)?(tempEntry->initial_value = NULL):(tempEntry->initial_value = strdup(initial_value));
    tempEntry->category = TYPE_TEMP;
    return tempEntry;
}

// generate pramaeter type
// the lookup function generates and stores the entry in currentST.
symboltableentry* genparam(symboltype* type, char* initial_value) {
    char paramName[20];
    sprintf(paramName, "para%d", currST->paramCount++);
    // Lookup or create a new entry for the temporary variable
    symboltableentry* paramEntry = lookup(currST, paramName);
    // Update type and initial value
    update_type(paramEntry, type);
    (initial_value==NULL)?(paramEntry->initial_value = NULL):(paramEntry->initial_value = strdup(initial_value));
    paramEntry->category = TYPE_PARAM;
    return paramEntry;
}

// add a new argument to the argument list of the function. Linked List end addition
void push_args(symboltable* currST, symboltableentry* arg){
    if(currST->_argList == NULL){
        currST->_argList = (symboltableentry**)malloc(sizeof(symboltableentry*));
        currST->_argList[0] = arg;
        return;
    }
    int count = 0;
    while(currST->_argList[count] != NULL){
        count++;
    }
    currST->_argList = (symboltableentry**)realloc(currST->_argList, sizeof(symboltableentry*)*(count+1));
    currST->_argList[count] = arg;
    return;
}

// Update count of return label
void update_return_ST(symboltable* currST, int update){
    currST->returnLabel += update;
    return;
}

// add a new entry to the symbol table
void update_ST(symboltable* currST, symboltableentry* entry){
    currST->table_entries = (symboltableentry**)realloc(currST->table_entries, sizeof(symboltableentry)*(currST->count+1));
    currST->table_entries[currST->count] = entry;
    currST->count++;
    return;
}

void print_ST(symboltable *currST){
    printf("\n\n==================================================================================================================\n");
    (currST->parent) ? printf("Symbol Table: %-50s Parent: ST.%s\n", currST->name, currST->parent->name) : printf("Symbol Table: %-35s Parent: NULL\n", currST->name);
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("%-15s%-15s%-20s%-20s%-15s%-20s\n", "Name", "Type", "Category", "Initial Value", "Size", "Nested Table");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0; i< currST->count; i++){
        symboltableentry* entry = (currST->table_entries[i]);
        printf("%-15s", entry->name);
        printf("%-15s", printType(entry->type));
        printf("%-20s", printCategory(entry->category));
        printf("%-20s", entry->initial_value);
        printf("%-15d", entry->size);
        // printf("%-15s", "-");
        if(entry->next != NULL){
            printf("%-20s\n", entry->next->name);
        }
        else{
            printf("-\n");
        }
    }
    // printf("\n");
    printf("==================================================================================================================\n");

    // print the nested symbol tables
    for(int i=0; i< currST->count; i++){
        symboltableentry* entry = (currST->table_entries[i]);
        if(entry->next != NULL && entry->category == TYPE_FUNC){
            print_ST(entry->next);
            printf("\n");
        }
    }
}

/**************************************************************************/
/*                              QUADS and TAC                             */
/**************************************************************************/

// Operator Codes -- char* op
char* printOP(enum op_code op){
    switch(op){
        case OP_PLUS:
            return "+";
        case OP_MINUS:
            return "-";
        case OP_MULT:
            return "*";
        case OP_DIV:
            return "/";
        case OP_MOD:
            return "\%";
        case OP_EQUALS:
            return "==";
        case OP_NOT_EQUALS:
            return "!=";
        case OP_LT:
            return "<";
        case OP_LT_EQUALS:
            return "<=";
        case OP_GT:
            return ">";
        case OP_GT_EQUALS:
            return ">=";
        case OP_GOTO:
            return "goto";
        case OP_ASSIGN:
            return "=";
        case OP_ASSIGN_STR:
            return "=str";
        case OP_ASSIGN_AMPER:
            return "=&";
        case OP_ASSIGN_ASTERISK:
            return "=*";
        case OP_ASTERISK_ASSIGN:
            return "*=";
        case OP_UMINUS:
            return "uminus";
        case OP_ASSIGN_BOX:
            return "=[]";
        case OP_BOX_ASSIGN:
            return "[]=";
        case OP_RETURN:
        case OP_RETURN_VOID:
            return "return";
        case OP_PARAM:
            return "param";
        case OP_CALL:
        case OP_CALL_VOID:
            return "call";
        case OP_FUNC:
            return "function";
        case OP_LABEL:
            return "label";
        default:
            return "NULL";
    }
}

// print the quad
void print_quad(quad* arr){
    switch(arr->op){
        case OP_PLUS:
        case OP_MINUS:
        case OP_MULT:
        case OP_DIV:
        case OP_MOD:
            printf("%s = %s %s %s\n", arr->result, arr->arg1, printOP(arr->op), arr->arg2);
            break;
        case OP_EQUALS:
        case OP_NOT_EQUALS:
        case OP_LT:
        case OP_LT_EQUALS:
        case OP_GT:
        case OP_GT_EQUALS:
            printf("if %s %s %s goto %s\n", arr->arg1, printOP(arr->op), arr->arg2, arr->result);
            break;
        case OP_GOTO:
            printf("goto %s\n", arr->result);
            break;
        case OP_ASSIGN:
            printf("%s = %s\n", arr->result , arr->arg1);
            break;
        case OP_ASSIGN_STR:
            printf("%s = string(%s)\n", arr->result, arr->arg1);
            break;
        case OP_ASSIGN_AMPER:
            printf("%s = &%s\n", arr->result, arr->arg1);
            break;
        case OP_ASSIGN_ASTERISK:
            printf("%s = *%s\n", arr->result, arr->arg1);
            break;
        case OP_ASTERISK_ASSIGN:
            printf("*%s = %s\n", arr->result, arr->arg1);
            break;
        case OP_UMINUS:
            printf("%s = -%s\n", arr->result, arr->arg1);
            break;
        case OP_ASSIGN_BOX:
            printf("%s = %s[%s]\n", arr->result, arr->arg1, arr->arg2);
            break;
        case OP_BOX_ASSIGN:
            printf("%s[%s] = %s\n", arr->result, arr->arg1, arr->arg2);
            break;
        case OP_RETURN:
            printf("return %s\n", arr->result);
            break;
        case OP_RETURN_VOID:
            printf("return\n");
            break;
        case OP_PARAM:
            printf("param %s\n", arr->result);
            break;
        case OP_CALL:
            printf("%s = call %s, %s\n", arr->result, arr->arg1, arr->arg2);
            break;
        case OP_CALL_VOID:
            printf("call %s, %s\n", arr->arg1, arr->arg2);
            break;
        case OP_FUNC:
            printf("function %s:\n", arr->result);
            break;
        case OP_LABEL:
            printf("%s:\n", arr->result);
            break;
        case OP_ENDFUNC:
            printf("end %s\n", arr->result);
            break;
        default:
            printf("NULL\n");
    }
}

// print the quad array -- this function prints the Three Address Code
void print_quadArray(qArray* head){
    qArray* curr = head;
    printf("=============================================================================================================\n");
    printf("THREE ADDRESS CODE\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    // if empty
    if(curr->arr == NULL){
        printf("NULL\n");
        printf("\n=============================================================================================================\n\n");
        return;
    }
    while(curr != NULL && curr->count != 0){
        printf("%d: ", curr->count);
        print_quad(curr->arr);
        curr = curr->nextQuad;
    }
    printf("\n=============================================================================================================\n\n");
}

// initilize quadArray
qArray* quadArray_initialize(qArray* head){
    head = (qArray*)malloc(sizeof(qArray));
    head->arr = NULL;
    head->count = 1;
    head->nextQuad = NULL;
    return head;
}

// Emit a quad -- add to quadArray
void emit(enum op_code op, char* arg1, char* arg2, char* result){
    // initial case -- nextQuad is NULL
    if(quadArray->arr == NULL){
        quadArray->arr = (quad*)malloc(sizeof(quad));
        quadArray->arr->op = op;
        (arg1 == NULL)?(quadArray->arr->arg1 = NULL):(quadArray->arr->arg1 = strdup(arg1));
        (arg2 == NULL)?(quadArray->arr->arg2 = NULL):(quadArray->arr->arg2 = strdup(arg2));
        (result == NULL)?(quadArray->arr->result = NULL):(quadArray->arr->result = strdup(result));
        quadArray->nextQuad = NULL;
        return;
    }
    // if the quadArray is not empty, then add the quad to the end of the linked list
    qArray* curr = quadArray;
    while(curr->nextQuad != NULL){
        curr = curr->nextQuad;
    }
    curr->nextQuad = (qArray*)malloc(sizeof(qArray));
    curr->nextQuad->arr = (quad*)malloc(sizeof(quad));
    curr->nextQuad->arr->op = op;
    (arg1 == NULL)?(curr->nextQuad->arr->arg1 = NULL):(curr->nextQuad->arr->arg1 = strdup(arg1));
    (arg2 == NULL)?(curr->nextQuad->arr->arg2 = NULL):(curr->nextQuad->arr->arg2 = strdup(arg2));
    (result == NULL)?(curr->nextQuad->arr->result = NULL):(curr->nextQuad->arr->result = strdup(result));
    curr->nextQuad->count = curr->count + 1;
    curr->nextQuad->nextQuad = NULL;
    return;
}

// Get the next instruction number. Quad Starts at 1. Next instruction is the count of the last quad + 1
int nextInstr(){
    qArray* curr = quadArray;
    while(curr->nextQuad != NULL){
        curr = curr->nextQuad;
    }
    return curr->count+1;
}

/*
TODO:
    - FOR LOOP
*/

int main(){
    printf("Initializing Symbol Tables\n");
    globalST = create_symboltable("Global", NULL);
    currST = globalST;
    stack_intialize(&var_type);
    string_head = string_list_initialize();
    quadArray = quadArray_initialize(quadArray);
    // gentemp test
    // symboltableentry* temp = gentemp(create_symboltype(TYPE_INT, 1, NULL), "69");
    // gentemp update test
    printf("Starting Parser\n");
    yyparse();
    printf("Global Symbol Table:\n");
    print_ST(globalST);
    printf("\n\n\n");
    print_quadArray(quadArray);
    return 0;
}