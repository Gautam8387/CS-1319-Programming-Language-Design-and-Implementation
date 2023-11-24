#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "promise.h"

#define size_of_char 1
#define size_of_int 4
#define size_of_pointer 4

// Global variables
struct SymTab* currST;
struct SymTab* globalST;
struct Quad* QuadArray;
int nextQuadIndex = 0;

// Function Definitions

void print_QuadArray() {
    printf("THREE ADDRESS CODE (TAC):\n");
    for (int j = 0; j < nextQuadIndex; j++) {
        struct Quad* q = &QuadArray[j];
        if (strcmp(q->op, "label") == 0) {
            printf("\n%d: ", j);
            print_Quad(q);
        } else {
            printf("%d: \t", j);
            print_Quad(q);
        }
    }
    printf("\n");
}

void print_Quad(struct Quad* q) {
    if (strcmp(q->op, "+") == 0 || strcmp(q->op, "-") == 0 ||
        strcmp(q->op, "*") == 0 || strcmp(q->op, "/") == 0 ||
        strcmp(q->op, "\%") == 0) {
        printf("%s = %s %s %s", q->res, q->arg1, q->op, q->arg2);
    } else if (strcmp(q->op, "==") == 0 || strcmp(q->op, "!=") == 0 ||
               strcmp(q->op, "<=") == 0 || strcmp(q->op, "<") == 0 ||
               strcmp(q->op, ">") == 0 || strcmp(q->op, ">=") == 0) {
        printf("if %s %s %s goto %s", q->arg1, q->op, q->arg2, q->res);
    } else if (strcmp(q->op, "goto") == 0) {
        printf("goto %s", q->res);
    } else if (strcmp(q->op, "=") == 0 || strcmp(q->op, "=str") == 0) {
        printf("%s = %s", q->res, q->arg1);
    } else if (strcmp(q->op, "=&") == 0) {
        printf("%s = &%s", q->res, q->arg1);
    } else if (strcmp(q->op, "=*") == 0) {
        printf("%s = *%s", q->res, q->arg1);
    } else if (strcmp(q->op, "*=") == 0) {
        printf("*%s = %s", q->res, q->arg1);
    } else if (strcmp(q->op, "uminus") == 0) {
        printf("%s = -%s", q->res, q->arg1);
    } else if (strcmp(q->op, "=[]") == 0) {
        printf("%s = %s[%s]", q->res, q->arg1, q->arg2);
    } else if (strcmp(q->op, "[]=") == 0) {
        printf("%s[%s] = %s", q->res, q->arg1, q->arg2);
    } else if (strcmp(q->op, "return") == 0) {
        printf("return %s", q->res);
    } else if (strcmp(q->op, "param") == 0) {
        printf("param %s", q->res);
    } else if (strcmp(q->op, "call") == 0) {
        printf("%s = call %s, %s", q->res, q->arg1, q->arg2);
    } else if (strcmp(q->op, "Function") == 0) {
        printf("%s: ", q->res);
    }
    printf("\n");
}

void emit(char* op, char* res, char* arg1, char* arg2) {
    struct Quad* q = &QuadArray[nextQuadIndex++];
    strcpy(q->op, op);
    strcpy(q->res, res);
    strcpy(q->arg1, arg1);
    strcpy(q->arg2, arg2);
}

struct Sym* lookup(struct SymTab* st, char* name, int flags) {
    int i;
    for (i = 0; i < st->count; ++i) {
        struct Sym* sym = &st->table[i];
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
    }

    if (st->parent != NULL && (flags & FIND)) {
        struct Sym* ptr = lookup(st->parent, name, FIND);
        if (ptr != NULL) {
            return ptr;
        }
    }

    if (flags & INSERT) {
        struct Sym* symbol = create_Sym(name, "", NULL, 0);
        st->table[st->count++] = *symbol;
        return &st->table[st->count - 1];
    }

    return NULL;
}

struct Sym* create_Sym(char* name, char* init_val, struct SymType* arrtype, int width) {
    struct Sym* sym = malloc(sizeof(struct Sym));

    strcpy(sym->name, name);
    sym->type = create_SymType("int", NULL, 0);  // Assuming default type is "int" for simplicity
    sym->size = computeSize(sym->type);
    strcpy(sym->init_val, init_val);
    sym->offset = 0;
    sym->nested = NULL;

    return sym;
}


struct Sym* gentemp(struct SymType* type, char* init_val) {
    char tmp_name[256];
    sprintf(tmp_name, "t%d", currST->count++);

    while (lookup_Sym(currST, tmp_name, FIND) != NULL) {
        sprintf(tmp_name, "t%d", currST->count++);
    }

    struct Sym* s = create_Sym(tmp_name, "", type, 0);
    s->size = computeSize(type);
    strcpy(s->init_val, init_val);
    currST->table[currST->count++] = *s;

    return &currST->table[currST->count - 1];
}


void backpatch(int* list1, int addr) {
    char addr_str[256];
    sprintf(addr_str, "%d", addr);

    int* it = list1;
    while (*it != -1) {
        struct Quad* q = &QuadArray[*it];
        strcpy(q->res, addr_str);
        it++;
    }
}

int* makelist(int addr) {
    int* newlist = malloc(2 * sizeof(int));
    newlist[0] = addr;
    newlist[1] = -1;
    return newlist;
}

int* merge(int* l1, int* l2) {
    int len_l1 = 0;
    int* it = l1;
    while (*it != -1) {
        len_l1++;
        it++;
    }

    int len_l2 = 0;
    it = l2;
    while (*it != -1) {
        len_l2++;
        it++;
    }

    int* merged = (int*)malloc((len_l1 + len_l2 + 1) * sizeof(int));

    it = l1;
    int* dest = merged;
    while (*it != -1) {
        *dest = *it;
        dest++;
        it++;
    }

    it = l2;
    while (*it != -1) {
        *dest = *it;
        dest++;
        it++;
    }

    *dest = -1;

    return merged;
}


struct Expression* convertBoolToInt(struct Expression* e) {
    if (e->isBoolean) {
        e->loc = gentemp(create_SymType("int", NULL, 0), "");
        backpatch(e->truelist, nextinstr());
        emit("=", e->loc->name, "true", "");
        int p = nextinstr() + 1;
        char str[256];
        sprintf(str, "%d", p);
        emit("goto", str, "", "");
        backpatch(e->falselist, nextinstr());
        emit("=", e->loc->name, "false", "");
    }
    return e;
}

struct Expression* convertIntToBool(struct Expression* e) {
    if (!e->isBoolean) {
        e->falselist = makelist(nextinstr());
        emit("==", "", e->loc->name, "0");
        e->truelist = makelist(nextinstr());
        emit("goto", "", "", "");
    }
    return e;
}

int typecheck(struct Sym* s1, struct Sym* s2) {
    struct SymType* type1 = s1->type;
    struct SymType* type2 = s2->type;

    if (type1 == NULL && type2 == NULL)
        return 1;  // Both symbol types are NULL
    else if (type1 == NULL || type2 == NULL || strcmp(type1->type, type2->type) != 0)
        return 0;  // One of them is NULL or base type isn't the same

    return compareSymbolType(type1->arrtype, type2->arrtype);
}

int compareSymbolType(struct SymType* t1, struct SymType* t2) {
    int flag = 0;
    if (t1 == NULL && t2 == NULL)
        flag = 1;  // Both symbol types are NULL
    else if (t1 == NULL || t2 == NULL || strcmp(t1->type, t2->type) != 0)
        flag = 2;  // One of them is NULL or base type isn't the same

    if (flag == 1)
        return 1;
    else if (flag == 2)
        return 0;
    else
        return compareSymbolType(t1->arrtype, t2->arrtype);
}

int nextinstr() {
    return nextQuadIndex;
}

int computeSize(struct SymType* t) {
    if (strcmp(t->type, "void") == 0)
        return 0;
    else if (strcmp(t->type, "char") == 0)
        return size_of_char;
    else if (strcmp(t->type, "int") == 0)
        return size_of_int;
    else if (strcmp(t->type, "ptr") == 0)
        return size_of_pointer;
    else if (strcmp(t->type, "func") == 0)
        return 0;
    else if (strcmp(t->type, "arr") == 0)
        return t->width * computeSize(t->arrtype);
    else
        return -1;
}

char* printType(struct SymType* t) {
    if (t == NULL)
        return "null";
    if (strcmp(t->type, "void") == 0)
        return "void";
    else if (strcmp(t->type, "char") == 0)
        return "char";
    else if (strcmp(t->type, "int") == 0)
        return "int";
    else if (strcmp(t->type, "ptr") == 0) {
        char* arrtype_str = printType(t->arrtype);
        char* result_str = malloc(strlen(arrtype_str) + 7);
        sprintf(result_str, "ptr(%s)", arrtype_str);
        return result_str;
    } else if (strcmp(t->type, "arr") == 0) {
        char* arrtype_str = printType(t->arrtype);
        char* result_str = malloc(strlen(arrtype_str) + 13);
        sprintf(result_str, "arr(%d,%s)", t->width, arrtype_str);
        return result_str;
    } else if (strcmp(t->type, "func") == 0)
        return "func";
    else if (strcmp(t->type, "block") == 0)
        return "block";
    else
        return "NA";
}

void update_offsets(struct SymTab* st) {
    struct SymTab** funcTables = malloc(1000 * sizeof(struct SymTab*));
    int offset = 0;
    
    for (int i = 0; i < st->count; ++i) {
        struct Sym* sym = &st->table[i];
        sym->offset = offset;
        offset += sym->size;
        
        if (sym->nested != NULL) {
            funcTables[sym->nested->count++] = sym->nested;
        }
    }
    
    for (int i = 0; i < st->count; ++i) {
        if (funcTables[i] != NULL) {
            update_offsets(funcTables[i]);
        }
    }

    free(funcTables);
}


int main(int argc, char** argv) {
    globalST = malloc(sizeof(struct SymTab));
    strcpy(globalST->name, "Global");
    currST = globalST;
    QuadArray = malloc(1000 * sizeof(struct Quad));
    yyparse();
    update_offsets(globalST);
    printf("\n");
    if (argc > 1 && strcmp(argv[1], "-tac") == 0) {
        print_QuadArray();
        print(globalST);
    }

    return 0;
}
