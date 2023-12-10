// Group 03: julius-stabs-back
// Gautam Ahuja, Nistha Singh

#include "3_A5_translator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "3_A4.tab.h"

extern void yyerror(char *s); // This function is called when there is a parsing error
extern int yyparse(void);
extern FILE* yyin; 

/**************************************************************************/
/*                        GLOBAL VARIABLES                                */
/**************************************************************************/
qArray* quadArray;           // pointer to the head of the quad array linked list
var_type_stack var_type;            // declare the stack
string_list* string_head=NULL;           // linked list for string literals
symboltable* globalST;              // pointer to Global Symbol Table
symboltable* currST;                // pointer to Current Symbol Table
symboltable* new_ST;                // pointer to new Symbol Table  -- used in function declaration
static int tempCount = 0;               // count of the temporary variables
int _LabelCount = 0;
HashLabel* _lablesRecord[MAX_HASH_LABEL];
globalVars* _globalVars[MAX_HASH_GLOBAL];


/**************************************************************************/
/*      Expression, Statement, and Function Structures                    */
/**************************************************************************/
// to create a new expression -- all fields are initialized to NULL
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
    head->entries = -1;
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

int ll_length(string_list* head){
    int count = 0;
    string_list* curr = head;
    while(curr != NULL && curr->str != NULL){
        count++;
        curr = curr->next;
    }
    return count;
}

param_list* param_list_initialize(){
    param_list* head = (param_list*)malloc(sizeof(param_list));
    head->param = NULL;
    head->next = NULL;
    return head;
}

// insert a new string at the end of the linked list
void param_list_insert(param_list* head, char* str){
    // check if it is the first entry
    if(head->param == NULL){
        head->param = strdup(str);
        return;
    }
    // insert new entry at the end
    param_list* temp = (param_list*)malloc(sizeof(param_list));
    temp->param = strdup(str);
    temp->next = NULL;
    param_list* curr = head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = temp;
}

// delete the linked list end entry
param_list* param_list_delete(param_list* head){
    param_list* curr = head;
    while(curr != NULL){
        param_list* temp = curr;
        curr = curr->next;
        free(temp);
    }
    head = param_list_initialize();
    return head;
}

/**************************************************************************/
/*                        ACTIVATION RECORD HASH                          */
/**************************************************************************/
// HASH for Activation Record
unsigned int hash_ar(char *key){
    unsigned int hashValue = 0;
    while(*key !='\0'){
        hashValue += *key++;
    }
    return hashValue % MAX_HASH_AR;
}

void insert_ar(char* key, int value, HashAR* hashmap[]){
    if(key == NULL){
        // printf("Error insert_ar: Key cannot be NULL.\n");
        return;
    }
    int hashIndex = hash_ar(key);
    HashAR* temp = hashmap[hashIndex];
    while(temp != NULL){
        if(strcmp(temp->key, key) == 0){
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
    HashAR* newNode = (HashAR*)malloc(sizeof(HashAR));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashmap[hashIndex];
    hashmap[hashIndex] = newNode;
}

// search_ar() -- return the offset
int search_ar(char *key, HashAR *hashmap[]){
    if(key == NULL){
        // printf("Error search_ar: Key cannot be NULL.\n");
        return 0;
    }
    int hashIndex = hash_ar(key);
    HashAR* temp = hashmap[hashIndex];
    while(temp != NULL){
        if(strcmp(temp->key, key) == 0){
            return temp->value;
        }
        temp = temp->next;
    }
    return 0;
}

// HASH for Label (return label)
unsigned int hash_label(int key){
    return key % MAX_HASH_LABEL;
}

void insert_label(int key, int value, HashLabel *hashmap[]){
    if(key < 0){
        // printf("Error: Key cannot be negative.\n");
        return;
    }
    int hashIndex = hash_label(key);
    HashLabel* temp = hashmap[hashIndex];
    while(temp != NULL){
        if(temp->key == key){
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
    HashLabel* newNode = (HashLabel*)malloc(sizeof(HashLabel));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashmap[hashIndex];
    hashmap[hashIndex] = newNode;
}

bool label_count(int key, HashLabel *hashmap[]){
    if(key < 0){
        // printf("Error: Key cannot be negative.\n");
        return false;
    }
    int hashIndex = hash_label(key);
    HashLabel* temp = hashmap[hashIndex];
    while(temp != NULL){
        if(temp->key == key){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// lable_at() -- return the reference to the label
HashLabel* label_at(int key, HashLabel *hashmap[]){
    if(key < 0){
        // printf("Error: Key cannot be negative.\n");
        return NULL;
    }
    int hashIndex = hash_label(key);
    HashLabel* temp = hashmap[hashIndex];
    while(temp != NULL){
        if(temp->key == key){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// HASH for Global Variables
unsigned int hash_global(char *key){
    // used the djb2 hash function
    unsigned int hashValue = 5381;
    int c;
    while ((c = *key++)) {
        hashValue = ((hashValue << 5) + hashValue) + c; // hashValue * 33 + c
    }
    return hashValue % MAX_HASH_GLOBAL;
}

void insert_global(char* key, bool value, globalVars* hashmap[]){
    if(key == NULL){
        // printf("Error insert_global: Key cannot be NULL.\n");
        return;
    }
    int hashIndex = hash_global(key);
    globalVars* temp = hashmap[hashIndex];
    while(temp != NULL){
        if(strcmp(temp->key, key) == 0){
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
    globalVars* newNode = (globalVars*)malloc(sizeof(globalVars));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashmap[hashIndex];
    hashmap[hashIndex] = newNode;
}

bool search_global(char *key, globalVars *hashmap[]){
    if(key == NULL){
        // printf("Error search_global: Key cannot be NULL.\n");
        return false;
    }
    int hashIndex = hash_global(key);
    // printf("\nSearching for %s on %d\n", key, hashIndex);
    globalVars* temp = hashmap[hashIndex];
    while(temp != NULL){
        if(strcmp(temp->key, key) == 0){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

/**************************************************************************/
/*                          TARGET TRANSLATIONS                           */
/**************************************************************************/
void gen_activation_record(symboltable* currST){
    int local = -20;
    int param = -24;

    // iterate over the symbol table entries
    for(int i=0; i < currST->count; i++){
        symboltableentry* entry = currST->table_entries[i];
        // printf("Entry: %s\n", entry->name);
        if(entry->category == TYPE_PARAM){
            // printf("Param: %s\n", entry->name);
            param += entry->size;
            insert_ar(entry->name, param, currST->_aRecord);
        }
        else if(entry->category == TYPE_RETURN){
            // printf("Local: %s\n", entry->name);
            continue;   
        }
        else if(entry->category == TYPE_FUNCTION){
            // printf("Function: %s\n", entry->name);
            gen_activation_record(entry->next);
        }
        else{
            // printf("Local: %s\n", entry->name);
            local -= entry->size;
            insert_ar(entry->name, local, currST->_aRecord);
        }
    }
    return;
}

void print_activationRecord(FILE* file, symboltable* currST){
    fprintf(file, "\n\n==================================================================================================================\n");
    fprintf(file, "ACTIVATION RECORD: %s\n", currST->name);
    fprintf(file, "------------------------------------------------------------------------------------------------------------------\n");
    // name, category, offset, 
    fprintf(file, "%-15s%-15s%-15s%-15s\n", "Name", "Category", "Offset", "Nested Table");
    fprintf(file, "------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0; i< MAX_HASH_AR; i++){
        HashAR* temp = currST->_aRecord[i];
        // get symboltableentry of sa,e name from symbol table
        while(temp != NULL){
            symboltableentry* entry = lookup(currST, temp->key);
            fprintf(file, "%-15s", temp->key);
            fprintf(file, "%-15s", printCategory(entry->category));
            fprintf(file, "%-15d", temp->value);
            fprintf(file, "-\n");
            temp = temp->next;
        }
    }
    fprintf(file, "==================================================================================================================\n");
    // print the nested symbol tables
    for(int i=0; i< currST->count; i++){
        symboltableentry* entry = (currST->table_entries[i]);
        if(entry->next != NULL && entry->category == TYPE_FUNCTION){
            print_activationRecord(file, entry->next);
            fprintf(file, "\n");
        }
    }
}

// THREE ADDRESS CODE to x86 Assembly Code
/*
void iterate_hashmap(HashLabel* hashmap[], int size) {
    for (int i = 0; i < size; ++i) {
        HashLabel* current = hashmap[i];
        while (current != NULL) {
            // Process the current element (e.g., print key and value)
            printf("Key: %d, Value: %d\n", current->key, current->value);

            // Move to the next element in the linked list
            current = current->next;
        }
    }
}
*/

void tac2x86(FILE* file){
    // first loop
    qArray* currentQArray = quadArray;
    while(currentQArray !=NULL && currentQArray->arr != NULL && currentQArray->count != 0){
    // fprintf(file, "\n\nHELLO\n\n");
        quad* currQ = currentQArray->arr;
        if (currQ->op == OP_GOTO || currQ->op == OP_LT || currQ->op == OP_GT || currQ->op == OP_LT_EQUALS || currQ->op == OP_GT_EQUALS || currQ->op == OP_EQUALS || currQ->op == OP_NOT_EQUALS) {
            if (currQ->result == NULL) {
                currentQArray = currentQArray->nextQuad;
                continue;
            };
            int instr_no = atoi(currQ->result);
            insert_label(instr_no, 1, _lablesRecord);
        }
        currentQArray = currentQArray->nextQuad;
    }
    // second loop -- update _lablesRecord values and count
    // AMBIGIOUS
    for(int i=0; i < MAX_HASH_LABEL; i++){
        HashLabel* temp = _lablesRecord[i];
        while(temp != NULL){
            /*
            int instr_no = temp->key;
            int count = temp->value;
            int new_instr_no = instr_no + count;
            temp->value = new_instr_no;
            temp = temp->next;
            */
            // _LabelCount++;
            temp->value = ++_LabelCount;
            temp = temp->next;
        }
    }
    // begin the .asm file here
    for(int i=0; i< globalST->count; i++){
        symboltableentry* entry = (globalST->table_entries[i]);
        if(entry->category != TYPE_FUNCTION){
            // It is a Global Variable
            // CHAR
            if(entry->type->type == TYPE_CHAR){
                if(entry->initial_value == NULL){
                    // fprintf(file, "Global Char: %s\n", entry->name);
                    fprintf(file, "\t.comm\t%s,1,1\n", entry->name);
                }
                else{
                    // fprintf(file, "Global Char: %s = %s\n", entry->name, entry->initial_value);
                    fprintf(file, "\t.globl\t%s\n", entry->name);
                    // fprintf(file, "\t.data\n");
                    fprintf(file, "\t.type\t%s, @object\n", entry->name);
                    fprintf(file, "\t.size\t%s, 1\n", entry->name);
                    fprintf(file, "%s:\n", entry->name);
                    fprintf(file, "\t.byte\t%d\n", atoi(entry->initial_value));
                }
                // insert into global hashmap
                insert_global(entry->name, true, _globalVars);
            }
            // INT
            if(entry->type->type == TYPE_INT){
                if(entry->initial_value == NULL){
                    // fprintf(file, "Global Int: %s\n", entry->name);
                    fprintf(file, "\t.comm\t%s,4,4\n", entry->name);
                }
                else{
                    // fprintf(file, "Global Int: %s = %s\n", entry->name, entry->initial_value);
                    fprintf(file, "\t.globl\t%s\n", entry->name);
                    fprintf(file, "\t.data\n");
                    fprintf(file, "\t.align 4\n");
                    fprintf(file, "\t.type\t%s, @object\n", entry->name);
                    fprintf(file, "\t.size\t%s, 4\n", entry->name);
                    fprintf(file, "%s:\n", entry->name);
                    // long -> int
                    fprintf(file, "\t.long\t%d\n", atoi(entry->initial_value));
                }
                // insert into global hashmap
                insert_global(entry->name, true, _globalVars);
            }
            // ARRAY
            if(entry->type->type == TYPE_ARRAY){
                fprintf(file, "\t.comm\t%s,%d,4\n", entry->name, entry->size);
                // insert into global hashmap
                insert_global(entry->name, true, _globalVars);
            }
        }
    }
    
    // STRINGS -- LL at string_head
    string_list* currString = string_head;
    // get size
    int string_head_size = ll_length(string_head);
    // fprintf(file, "\n\nLENGTH: %d\n\n", string_head_size);
    if(string_head_size>0){
        fprintf(file, "\t.section\t.rodata\n");
        currString = string_head;
        while(currString != NULL){
            fprintf(file, ".LC%d:\n", currString->entries);
            fprintf(file, "\t.string\t%s\n", currString->str);
            currString = currString->next;
        }
    }

    // TEXT SECTION
    fprintf(file, "\t.text \n");
    // initialize params list
    param_list* params_head = param_list_initialize();
    currST = globalST;
    bool make_quad = false;
    // iterate over the quadArray
    currentQArray = quadArray;
    
    while(currentQArray != NULL && currentQArray->arr != NULL && currentQArray->count != 0){
        int iterator = currentQArray->count; // -1 ?
        if(label_count(iterator, _lablesRecord)){
            int count = label_at(iterator, _lablesRecord)->value;
            fprintf(file, ".L%d:\n", 2 * _LabelCount + count + 2);
        }
        
        char* op = printOP(currentQArray->arr->op);
        char* arg1 = (currentQArray->arr->arg1 == NULL)?(NULL):(strdup(currentQArray->arr->arg1));
        char* arg2 = (currentQArray->arr->arg2 == NULL)?(NULL):(strdup(currentQArray->arr->arg2));
        char* result = (currentQArray->arr->result == NULL)?(NULL):(strdup(currentQArray->arr->result));
        char* s = arg2;
        
        // Activation Record of Result
        char* result_ar;
        if(search_global(result, _globalVars)){
            // concatenate "(%rip)" to result
            result_ar = (char*)malloc(sizeof(char)*(strlen(result)+15));
            sprintf(result_ar, "%s(%%rip)", result);
        }
        else{
            //convert result of search_ar(result, currST->_aRecord) to string and concatenate "(%rbp)" to it
            int offset = search_ar(result, currST->_aRecord);
            result_ar = (char*)malloc(sizeof(char)*15);
            sprintf(result_ar, "%d(%%rbp)", offset);
        }

        // Activation Record of Arg1
        char* arg1_ar;
        if(search_global(arg1, _globalVars)){
            // concatenate "(%rip)" to arg1
            arg1_ar = (char*)malloc(sizeof(char)*(strlen(arg1)+15));
            sprintf(arg1_ar, "%s(%%rip)", arg1);
        }
        else{
            //convert result of search_ar(arg1, currST->_aRecord) to string and concatenate "(%rbp)" to it
            int offset = search_ar(arg1, currST->_aRecord);
            arg1_ar = (char*)malloc(sizeof(char)*15);
            sprintf(arg1_ar, "%d(%%rbp)", offset);
        }

        // Activation Record of Arg2
        char* arg2_ar;
        if(search_global(arg2, _globalVars)){
            // concatenate "(%rip)" to arg2
            arg2_ar = (char*)malloc(sizeof(char)*(strlen(arg2)+15));
            sprintf(arg2_ar, "%s(%%rip)", arg2);
        }
        else{
            //convert result of search_ar(arg2, currST->_aRecord) to string and concatenate "(%rbp)" to it
            int offset = search_ar(arg2, currST->_aRecord);
            arg2_ar = (char*)malloc(sizeof(char)*15);
            sprintf(arg2_ar, "%d(%%rbp)", offset);
        }
        // parameter type
        if(op == "param"){
            // push arg1 to params_head
            param_list_insert(params_head, result);
        }
        else{
            fprintf(file, "\t");
            // Binary Operations
            // Addition
            if (op == "+") {
                bool flag = true;
                if(s==NULL || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))){
                    flag = false;
                }
                else{
                    char* p;
                    strtol(s, &p, 10);
                    if(*p == 0)
                        flag = true;
                    else
                        flag = false;
                }
                if(flag){
                    fprintf(file, "addl \t$%d, %s\n", atoi(arg2), arg1_ar);
                }
                else{
                    // AMBIGIOUS
                    fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                    fprintf(file, "\tmovl\t%s, %%edx\n", arg2_ar);
                    fprintf(file, "\taddl \t%%edx, %%eax\n");
                    fprintf(file, "\tmovl\t%%eax, %s\n", result_ar);
                }
            }
            // Subtraction
            else if (op == "-"){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                fprintf(file, "\tmovl\t%s, %%edx\n", arg2_ar);
                fprintf(file, "\tsubl \t%%edx, %%eax\n");
                fprintf(file, "\tmovl\t%%eax, %s\n", result_ar);
            }
            // multiplication
            else if(op == "*"){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                bool flag = true;
                if(s==NULL || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))){
                    flag = false;
                }
                else{
                    char* p;
                    strtol(s, &p, 10);
                    if(*p == 0)
                        flag = true;
                    else
                        flag = false;
                }
                if(flag){
                    fprintf(file, "# %s = %s * %s\n", result, arg1, arg2);
                    fprintf(file, "\timull \t$%d, %%eax\n", atoi(arg2));
                    symboltable* tempTab = currST;
                    char* val;
                    // check if arg1 is a global variable
                    for(int i=0; i <tempTab->count; i++){ 
                        if(strcmp((tempTab->table_entries[i])->name, arg1) == 0){
                            val = strdup((tempTab->table_entries[i])->initial_value);    // value found, propagate the name
                        }
                    }
                }
                else{
                    fprintf(file, "\timull \t%s, %%eax\n", arg2_ar);
                    fprintf(file, "\tmovl\t%%eax, %s\n", result_ar);
                }
            }
            // division 
            else if(op=="/"){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                fprintf(file, "\tcltd\n");
                fprintf(file, "\tidivl \t%s\n", arg2_ar);
                fprintf(file, "\tmovl\t%%eax, %s\n", result_ar);
            }
            // modulo
            else if(op == "%"){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                fprintf(file, "\tcltd\n");
                fprintf(file, "\tidivl \t%s\n", arg2_ar);
                fprintf(file, "\tmovl\t%%edx, %s\n", result_ar);
            }
            // assign
            else if(op =="="){
                if(make_quad == true){
                    fprintf(file, "\tmovq \t%s, %%rax\n", arg1_ar);
                    fprintf(file, "\tmovq \t%%rax, %s\n", result_ar);
                    make_quad = false;
                }
                else{
                    s = arg1;//(arg1 == NULL)?(NULL):(strdup(arg1));
                    bool flag = true;
                    if(s==NULL || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))){
                        flag = false;
                    }
                    else{
                        char* p;
                        strtol(s, &p, 10);
                        if(*p == 0)
                            flag = true;
                        else
                            flag = false;
                    }
                    if(flag){
                        fprintf(file, "movl\t$%d, %%eax\n", atoi(arg1));
                    }
                    else{
                        fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                    }
                    fprintf(file, "\tmovl\t%%eax, %s\n", result_ar);
                }
            }
            else if(op=="=str"){
                fprintf(file, "movq \t$.LC%s, %s\n", arg1, result_ar);
            }
            // Relational
            else if(op=="=="){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                fprintf(file, "\tcmpl\t%s, %%eax\n", arg2_ar);
                int tempCount = label_at(atoi(result), _lablesRecord)->value;
                fprintf(file, "\tje .L%d\n", 2 * _LabelCount + tempCount + 2);
            }
            else if(op=="!="){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                fprintf(file, "\tcmpl\t%s, %%eax\n", arg2_ar);
                int tempCount = label_at(atoi(result), _lablesRecord)->value;
                fprintf(file, "\tjne .L%d\n", 2 * _LabelCount + tempCount + 2);
            }
            else if(op=="<"){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                fprintf(file, "\tcmpl\t%s, %%eax\n", arg2_ar);
                int tempCount = label_at(atoi(result), _lablesRecord)->value;
                fprintf(file, "\tjl .L%d\n", 2 * _LabelCount + tempCount + 2);
            }
            else if(op==">"){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                fprintf(file, "\tcmpl\t%s, %%eax\n", arg2_ar);
                int tempCount = label_at(atoi(result), _lablesRecord)->value;
                fprintf(file, "\tjg .L%d\n", 2 * _LabelCount + tempCount + 2);
            }
            else if(op=="<="){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                fprintf(file, "\tcmpl\t%s, %%eax\n", arg2_ar);
                int tempCount = label_at(atoi(result), _lablesRecord)->value;
                fprintf(file, "\tjle .L%d\n", 2 * _LabelCount + tempCount + 2);
            }
            else if(op==">="){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                fprintf(file, "\tcmpl\t%s, %%eax\n", arg2_ar);
                int tempCount = label_at(atoi(result), _lablesRecord)->value;
                fprintf(file, "\tjge .L%d\n", 2 * _LabelCount + tempCount + 2);
            }
            else if(op=="goto"){
                if (result != NULL) {
                    int tempCount = label_at(atoi(result), _lablesRecord)->value;
                    fprintf(file, "jmp .L%d\n", 2 * _LabelCount + tempCount + 2);
                }
            }

            // Unary Operations
            else if(op == "=&"){
                fprintf(file, "# %s = &%s\n", result, arg1);
                fprintf(file, "\tleaq\t%s, %%rax\n", arg1_ar);
                fprintf(file, "\tmovq \t%%rax, %s\n", result_ar);
                make_quad = true;
            }
            else if(op=="=*"){
                fprintf(file, "# %s = *%s\n", result, arg1);
                fprintf(file, "\tmovq\t%s, %%rax\n", arg1_ar);
                fprintf(file, "\tmovl\t(%%rax), %%eax\n");
                fprintf(file, "\tmovl\t%%eax, %s\n", result_ar);
            }
            else if(op=="*="){
                fprintf(file, "# *%s = %s\n", result, arg1);
                fprintf(file, "\tmovl\t%s, %%eax\n", result_ar);
                fprintf(file, "\tmovl\t%s, %%edx\n", arg1_ar);
                // cout << "\tmovl\t%edx, (%eax)";
                fprintf(file, "\tmovl\t%%edx, (%%eax)\n");
            }
            else if(op=="uminus"){
                fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                fprintf(file, "\tnegl\t%%eax\n");
                fprintf(file, "\tmovl\t%%eax, %s\n", result_ar);
            }
            else if(op == "=[]"){
                fprintf(file, "# =[] operation ; ");
                fprintf(file, "%s = %s[%s]\n", result, arg1, arg2);
                if(search_global(arg1, _globalVars)){
                    fprintf(file, "\tmovl\t%s, %%eax\n", arg2_ar);
                    fprintf(file, "\tmovslq\t%%eax, %%rdx\n");
                    fprintf(file, "\tleaq\t0(,%%rdx,4), %%rdx\n");
                    fprintf(file, "\tleaq\t%s, %%rax\n", arg1_ar);
                    fprintf(file, "\tmovl\t(%%rdx,%%rax), %%eax\n");
                    fprintf(file, "\tmovl\t%%eax, %s\n", result_ar);
                }
                else{
                    fprintf(file, "\tmovl\t%s, %%ecx\n", arg2_ar);
                    fprintf(file, "\tmovl\t%d(%%rbp,%%rcx,4), %%eax\n", search_ar(arg1, currST->_aRecord));
                    fprintf(file, "\tmovl\t%%eax, %s\n", result_ar);
                }
            }
            else if(op=="[]="){
                fprintf(file, "# []= operation ; ");
                fprintf(file, "%s[%s] = %s\n", result, arg1, arg2);
                if(search_global(result, _globalVars)){
                    fprintf(file, "\tmovl\t%s, %%eax\n", arg2_ar);
                    fprintf(file, "\tmovl\t%s, %%edx\n", arg1_ar);
                    fprintf(file, "\tmovslq\t%%edx, %%rdx\n");
                    fprintf(file, "\tleaq\t0(,%%rdx,4), %%rcx\n");
                    fprintf(file, "\tleaq\t%s, %%rdx\n", result_ar);
                    fprintf(file, "\tmovl\t%%eax, (%%rcx,%%rdx)\n");
                }
                else{
                    fprintf(file, "\tmovl\t%s, %%eax\n", arg1_ar);
                    fprintf(file, "\tmovl\t%s, %%edx\n", arg2_ar);
                    fprintf(file, "\tmovl\t%%edx, %d(%%rbp,%%rax,4)\n", search_ar(result, currST->_aRecord));
                }
            }
            else if(op=="return"){
                if(result != NULL){
                    fprintf(file, "\tmovl\t%s, %%eax\n", result_ar);
                }
                // jump to the end of the function -- epilogue
                fprintf(file, "\tjmp .LFE%d\n", _LabelCount);
            }
            else if(op=="param"){
                // push arg1 to params_head
                param_list_insert(params_head, result);
            }

            // function call
            else if(op=="call"){
                // 4 registers are used for passing parameters -- rdi, rsi, rdx, rcx
                param_list* tempPara = params_head;
                
                int paraCOUNT = 0;
                while(tempPara != NULL){
                    paraCOUNT++;
                    tempPara = tempPara->next;
                }
                tempPara = params_head;

                for(int i=0; i<paraCOUNT; i++){
                    if(i==0){
                        // first parameter 
                        int val = search_ar(tempPara->param, currST->_aRecord);
                        fprintf(file, "movl\t%d(%%rbp), %%eax\n", val);
                        fprintf(file, "\tmovq\t%d(%%rbp), %%rdi\n", val);
                    }
                    else if(i==1){
                        int val = search_ar(tempPara->param, currST->_aRecord);
                        fprintf(file, "movl\t%d(%%rbp), %%eax\n", val);
                        fprintf(file, "\tmovq\t%d(%%rbp), %%rsi\n", val);
                    }
                    else if(i==2){
                        int val = search_ar(tempPara->param, currST->_aRecord);
                        fprintf(file, "movl\t%d(%%rbp), %%eax\n", val);
                        fprintf(file, "\tmovq\t%d(%%rbp), %%rdx\n", val);
                    }
                    else if(i==3){
                        int val = search_ar(tempPara->param, currST->_aRecord);
                        fprintf(file, "movl\t%d(%%rbp), %%eax\n", val);
                        fprintf(file, "\tmovq\t%d(%%rbp), %%rcx\n", val);
                    }
                    else{
                        int val = search_ar(tempPara->param, currST->_aRecord);
                        fprintf(file, "\tmovq\t%d(%%rbp), %%rdi\n", val);
                    }
                    tempPara = tempPara->next;
                }
                // clear para stack
                params_head = param_list_delete(params_head);
                fprintf(file, "\tcall\t%s\n", arg1);
                fprintf(file, "\tmovl\t%%eax, %s\n", result_ar);
            }

            else if(op == "function"){
                // function begins -- prologue
                fprintf(file, ".globl\t%s\n", result);
                fprintf(file, "\t.type\t%s, @function\n", result);
                fprintf(file, "%s: \n", result);
                fprintf(file, ".LFB%d: \n", _LabelCount);
                fprintf(file, "\t.cfi_startproc\n");
                fprintf(file, "\tpushq\t%%rbp\n");
                fprintf(file, "\t.cfi_def_cfa_offset 8\n");
                fprintf(file, "\t.cfi_offset 5, -8\n");
                fprintf(file, "\tmovq\t%%rsp, %%rbp\n");
                fprintf(file, "\t.cfi_def_cfa_register 5\n");
                currST = lookup(globalST, result)->next;
                // get last entry of the symbol table -- count starts from 0
                symboltableentry* lastEntry = currST->table_entries[currST->count-1];
                // fprintf(file, "\n\nST ENTRY: %s\n\n", currST->name);
                // fprintf(file, "\n\nST ENTRYsss: %d\n\n", currST->count);
                // fprintf(file, "\n\nLAST ENTRY: %s\n\n", lastEntry->name);
                // fprintf(file, "\n\nLAST ENTRY SIZE: %d\n\n", lastEntry->size);
                // fprintf(file, "\n\nLAST ENTRY OFFSET: %d\n\n", lastEntry->offset);
                // get the size of the symbol table
                int sizeTemp = lastEntry->offset;
                // rsp register holds the address of the top of the stack
                fprintf(file, "\tsubq\t$%d, %%rsp\n", sizeTemp+24);  // MAX BUFFER: 4 Para + retVal + RA = 24 = (4+1+1)*4

                // function table -- paramaters section
                for(int i=0; i < currST->paramCount; i++){
                    symboltableentry* entry = currST->_argList[i];
                    if(i==0){
                        fprintf(file, "\tmovq\t%%rdi, %d(%%rbp)\n", search_ar(entry->name, currST->_aRecord));
                    }
                    else if(i==1){
                        fprintf(file, "\tmovq\t%%rsi, %d(%%rbp)\n", search_ar(entry->name, currST->_aRecord));
                    }
                    else if(i==2){
                        fprintf(file, "\tmovq\t%%rdx, %d(%%rbp)\n", search_ar(entry->name, currST->_aRecord));
                    }
                    else if(i==3){
                        fprintf(file, "\tmovq\t%%rcx, %d(%%rbp)\n", search_ar(entry->name, currST->_aRecord));
                    }
                }
            }
            // function end -- epilogue
            else if(op=="end"){
                fprintf(file, ".LFE%d: \n", _LabelCount++);
                fprintf(file, "leave\n");
                fprintf(file, "\t.cfi_restore 5\n");
                fprintf(file, "\t.cfi_def_cfa 4, 4\n");
                fprintf(file, "\tret\n");
                fprintf(file, "\t.cfi_endproc\n");
                fprintf(file, "\t.size\t%s, .-%s\n", result, result);
            }
            else{
                fprintf(file, "op: %s\n", op);
            }
            // fprintf(file, "\n");
        }
        currentQArray = currentQArray->nextQuad;
    }
    // footer
    fprintf(file, "\t.ident\t\"group-03-julius-stabs-back\"\n");
    fprintf(file, "\t.section\t.note.GNU-stack,\"\",@progbits\n");
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
            return size_of_pointer;
    }
}

// update the size of the symbol table entry
char* printType(symboltype* type){
    if(type == NULL){
        return "NULL";
    }
    char* str = NULL;
    char* str1 = NULL;
    switch(type->type){
        case TYPE_VOID:
            return "void";
        case TYPE_INT:
            return "int";
        case TYPE_CHAR:
            return "char";
        case TYPE_PTR:
            str = (char*)malloc(sizeof(char)*10);
            sprintf(str, "*%s", printType(type->ptr));
            return str;
        case TYPE_ARRAY:
            str1 = (char*)malloc(sizeof(char)*50);
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
        case TYPE_FUNCTION:
            return "function";
        case TYPE_RETURN:
            return "retVal";
        default:
            return "NULL";
    }
}

// check the types of two symbol types. 1 == true, 0 == false
int typecheck(symboltype* type1, symboltype* type2){
    if(type1 == NULL && type2 == NULL){
        return 0;
    }
    else if(type1 == NULL || type2 == NULL){
        return 0;
    }
    else if(type1->type == type2->type){
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
    // hash table initialization
    for(int i=0; i<MAX_HASH_AR; i++){
        newST->_aRecord[i] = NULL;
    }
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
        currST->paramCount++;
        return;
    }
    int count = 0;
    while(currST->_argList[count] != NULL){
        count++;
    }
    currST->_argList = (symboltableentry**)realloc(currST->_argList, sizeof(symboltableentry*)*(count+1));
    currST->_argList[count] = arg;
    currST->paramCount++;
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

void print_ST(FILE* file, symboltable *currST){
    fprintf(file, "\n\n==================================================================================================================\n");
    (currST->parent) ? fprintf(file, "Symbol Table: %-50s Parent: ST.%s\n", currST->name, currST->parent->name) : fprintf(file, "Symbol Table: %-35s Parent: NULL\n", currST->name);
    fprintf(file, "------------------------------------------------------------------------------------------------------------------\n");
    fprintf(file, "%-15s%-15s%-20s%-20s%-15s%-15s%-20s\n", "Name", "Type", "Category", "Initial Value", "Size", "Offset", "Nested Table");
    fprintf(file, "------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0; i< currST->count; i++){
        symboltableentry* entry = (currST->table_entries[i]);
        fprintf(file, "%-15s", entry->name);
        fprintf(file, "%-15s", printType(entry->type));
        fprintf(file, "%-20s", printCategory(entry->category));
        (entry->initial_value) ? fprintf(file, "%-20s", entry->initial_value) : fprintf(file, "%-20s", "-");
        fprintf(file, "%-15d", entry->size);
        fprintf(file, "%-15d", entry->offset); // offset is not updated
        if(entry->next != NULL){
            fprintf(file, "%-20s\n", entry->next->name);
        }
        else{
            fprintf(file, "-\n");
        }
    }
    // fprintf(file, "\n");
    fprintf(file, "==================================================================================================================\n");

    // print the nested symbol tables
    for(int i=0; i< currST->count; i++){
        symboltableentry* entry = (currST->table_entries[i]);
        if(entry->next != NULL && entry->category == TYPE_FUNCTION){
            print_ST(file, entry->next);
            fprintf(file, "\n");
        }
    }
}

// Set Offsets after table is generated 
void set_offset(symboltable* currST){
    int offset = 0;
    for(int i=0; i< currST->count; i++){
        symboltableentry* entry = (currST->table_entries[i]);
        if(entry->category == TYPE_FUNCTION){
            set_offset(entry->next);
        }
        entry->offset = offset;
        offset += entry->size;
    }
    return;
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
        case OP_ENDFUNC:
            return "end";
        default:
            return "NULL";
    }
}

// print the quad
void print_quad(FILE* file, quad* arr){
    switch(arr->op){
        case OP_PLUS:
        case OP_MINUS:
        case OP_MULT:
        case OP_DIV:
        case OP_MOD:
            fprintf(file, "%s = %s %s %s\n", arr->result, arr->arg1, printOP(arr->op), arr->arg2);
            break;
        case OP_EQUALS:
        case OP_NOT_EQUALS:
        case OP_LT:
        case OP_LT_EQUALS:
        case OP_GT:
        case OP_GT_EQUALS:
            fprintf(file, "if %s %s %s goto %s\n", arr->arg1, printOP(arr->op), arr->arg2, arr->result);
            break;
        case OP_GOTO:
            fprintf(file, "goto %s\n", arr->result);
            break;
        case OP_ASSIGN:
            fprintf(file, "%s = %s\n", arr->result , arr->arg1);
            break;
        case OP_ASSIGN_STR:
            fprintf(file, "%s = string(%s)\n", arr->result, arr->arg1);
            break;
        case OP_ASSIGN_AMPER:
            fprintf(file, "%s = &%s\n", arr->result, arr->arg1);
            break;
        case OP_ASSIGN_ASTERISK:
            fprintf(file, "%s = *%s\n", arr->result, arr->arg1);
            break;
        case OP_ASTERISK_ASSIGN:
            fprintf(file, "*%s = %s\n", arr->result, arr->arg1);
            break;
        case OP_UMINUS:
            fprintf(file, "%s = -%s\n", arr->result, arr->arg1);
            break;
        case OP_ASSIGN_BOX:
            fprintf(file, "%s = %s[%s]\n", arr->result, arr->arg1, arr->arg2);
            break;
        case OP_BOX_ASSIGN:
            fprintf(file, "%s[%s] = %s\n", arr->result, arr->arg1, arr->arg2);
            break;
        case OP_RETURN:
            fprintf(file, "return %s\n", arr->result);
            break;
        case OP_RETURN_VOID:
            fprintf(file, "return\n");
            break;
        case OP_PARAM:
            fprintf(file, "param %s\n", arr->result);
            break;
        case OP_CALL:
            fprintf(file, "%s = call %s, %s\n", arr->result, arr->arg1, arr->arg2);
            break;
        case OP_CALL_VOID:
            fprintf(file, "call %s, %s\n", arr->arg1, arr->arg2);
            break;
        case OP_FUNC:
            fprintf(file, "function %s:\n", arr->result);
            break;
        case OP_LABEL:
            fprintf(file, "%s:\n", arr->result);
            break;
        case OP_ENDFUNC:
            fprintf(file, "end %s\n", arr->result);
            break;
        default:
            fprintf(file, "NULL\n");
    }
}

// print the quad array -- this function prints the Three Address Code
void print_quadArray(FILE* file, qArray* head){
    qArray* curr = head;
    fprintf(file, "=============================================================================================================\n");
    fprintf(file, "THREE ADDRESS CODE\n");
    fprintf(file, "-------------------------------------------------------------------------------------------------------------\n");
    // if empty
    if(curr->arr == NULL){
        fprintf(file, "NULL\n");
        fprintf(file, "\n=============================================================================================================\n\n");
        return;
    }
    while(curr != NULL && curr->count != 0){
        fprintf(file, "%d: ", curr->count);
        print_quad(file, curr->arr);
        curr = curr->nextQuad;
    }
    fprintf(file, "\n=============================================================================================================\n\n");
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

int main(int argc, char** argv){
    printf("\n\n");
    // check if the input < 3 or if first para is non digit
    if (argc < 3 ) {
        printf("Usage: %s <1=out/2=asm> <nanoC file>\n", argv[0]);
        return 1;
    }
    const char* inname = argv[2];
    // remove the extension
    printf("Starting Compiler\n");
    int dot_at = strlen(inname)-3;
    char outname = inname[strlen(inname)-4]; // = (char*)malloc(sizeof(char)*dot_at+1);
    // for(int i=0; i!=dot_at; i++){
    //     outname[i] = inname[i];
    // }
    outname = inname[dot_at-1];
    printf("Input File: %s\n", inname);
    printf("Test Case: %c\n", outname);

    for(int i = 0; i < MAX_HASH_LABEL; i++){
        _lablesRecord[i] = NULL;
        _globalVars[i] = NULL;
    }

    printf("Initializing Symbol Tables\n");
    globalST = create_symboltable("Global", NULL);
    currST = globalST;
    printf("Initializing Variable STack\n");
    stack_intialize(&var_type);
    printf("Initializing String Linked List\n");
    string_head = string_list_initialize();
    printf("Initializing Quad Array\n");
    quadArray = quadArray_initialize(quadArray);

    printf("Starting Parser\n");
    // send input to parser
    FILE* file = fopen(inname, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;
    yyparse();
    printf("Parser Done, Updating Symbol Tables Offset\n");
    set_offset(globalST);
    printf("Generating Activation Records\n");
    gen_activation_record(globalST);

    if(strcmp(argv[1], "1") == 0){
        printf("Writing TACs\n");

        // open file for writing outname.out
        char* temp_o = "3_A5_quads";
        char* extension_out = (char*)malloc(sizeof(char)*6);
        sprintf(extension_out, "%c.out", outname);
        char* outname_out = (char*)malloc(sizeof(char)*25);
        sprintf(outname_out, "%s%s", temp_o, extension_out);

        FILE* file_out = fopen(outname_out, "w");
        if (!file_out) {
            perror("Error opening file");
            return 1;
        }
        printf("\tWriting TACs -- Activation Record\n");
        print_activationRecord(file_out, globalST);
        printf("\tWriting TACs -- Symbol Table\n");
        print_ST(file_out, globalST);
        printf("\tWriting TACs -- TAC\n");
        print_quadArray(file_out, quadArray);
        printf("\n\n\n");
        // close file
        fclose(file_out);
    }

    if(strcmp(argv[1], "2") == 0){
        printf("Writing TACs\n");

        // open file for writing outname.out
        char* temp_o = "3_A5_quads";
        char* extension_out = (char*)malloc(sizeof(char)*6);
        sprintf(extension_out, "%c.out", outname);
        char* outname_out = (char*)malloc(sizeof(char)*25);
        sprintf(outname_out, "%s%s", temp_o, extension_out);
        printf("HELLO\n");

        FILE* file_out = fopen(outname_out, "w");
        if (!file_out) {
            perror("Error opening file");
            return 1;
        }
        printf("\tWriting TACs -- Activation Record\n");
        print_activationRecord(file_out, globalST);
        printf("\tWriting TACs -- Symbol Table\n");
        print_ST(file_out, globalST);
        printf("\tWriting TACs -- TAC\n");
        print_quadArray(file_out, quadArray);
        printf("TAC DONE\n\n");
        // close file
        fclose(file_out);
        printf("Generating ASM\n");

        // open file for writing outname.asm
        char* temp_s = "3_A5_quads";
        char* extension_asm = (char*)malloc(sizeof(char)*4);
        sprintf(extension_asm, "%c.asm", outname);
        char* outname_asm = (char*)malloc(sizeof(char)*25);
        sprintf(outname_asm, "%s%s", temp_s, extension_asm);

        FILE* file_asm = fopen(outname_asm, "w");
        if (!file_asm) {
            perror("Error opening file");
            return 1;
        }
        tac2x86(file_asm);
        // close file
        fclose(file_asm);
        printf("ASM DONE\n\n\n");
    }
    fclose(file);
    return 0;
}