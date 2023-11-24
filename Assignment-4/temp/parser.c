#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUADS 1000
#define MAX_STRING_SIZE 100

SymTab globalST;
SymTab* currST;
SymTab* currST_Ptr;
char var_type[100];
int QuadCount = 0;
Quad QuadArray[MAX_QUADS];
char allstrings[MAX_QUADS][MAX_STRING_SIZE];

// Expression struct
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

// Quad struct
struct Quad {
    char res[100];
    char op[100];
    char arg1[100];
    char arg2[100];
};

// Function Declarations
void print_Quad(Quad q);
void emit(char op[], char res[], char arg1[], char arg2[]);
Sym* gentemp(SymType* type, char init_val[]);
void backpatch(int list[], int addr);
int* makelist(int addr);
int* merge(int a[], int b[]);
Expression* convertBoolToInt(Expression* e);
Expression* convertIntToBool(Expression* e);
int typecheck(Sym* s1, Sym* s2);
int compareSymbolType(SymType* t1, SymType* t2);
int nextinstr();
int computeSize(SymType* t);
void printType(SymType* t);
void computeActivationRecord(SymTab* st);

// Expression constructor
Expression makeExpression() {
    Expression e;
    e.isArray = 0;
    e.isPtr = 0;
    e.isBoolean = 0;
    e.loc = NULL;
    e.Array = NULL;
    memset(e.truelist, -1, sizeof(e.truelist));
    memset(e.falselist, -1, sizeof(e.falselist));
    memset(e.nextlist, -1, sizeof(e.nextlist));
    return e;
}

// Sym constructor
Sym makeSym() {
    Sym s;
    s.type = NULL;
    s.size = 0;
    s.offset = 0;
    s.nested = NULL;
    memset(s.name, 0, sizeof(s.name));
    memset(s.init_val, 0, sizeof(s.init_val));
    memset(s.category, 0, sizeof(s.category));
    return s;
}

// Sym constructor with parameters
Sym makeSymWithParams(char name[], char t[], SymType* arrtype, int width) {
    Sym s = makeSym();
    strcpy(s.name, name);
    s.type = malloc(sizeof(SymType));
    strcpy(s.type->type, t);
    s.type->arrtype = arrtype;
    s.type->width = width;
    s.size = computeSize(s.type);
    return s;
}

// SymType constructor
SymType makeSymType(char type[], SymType* arrtype, int width) {
    SymType t;
    strcpy(t.type, type);
    t.arrtype = arrtype;
    t.width = width;
    return t;
}

// SymTab constructor
SymTab makeSymTab(char name[]) {
    SymTab st;
    strcpy(st.name, name);
    st.retType = NULL;
    st.count = 0;
    st.parent = NULL;
    return st;
}

// Quad constructor
Quad makeQuad(char res[], char arg1[], char op[], char arg2[]) {
    Quad q;
    strcpy(q.res, res);
    strcpy(q.arg1, arg1);
    strcpy(q.op, op);
    strcpy(q.arg2, arg2);
    return q;
}

// Function Definitions
void print_QuadArray() {
    printf("%-120s\n", "------------------------------------------------------------------------------------------------------------------------");
    printf("%-120s\n", "THREE ADDRESS CODE (TAC):");
    printf("%-120s\n", "------------------------------------------------------------------------------------------------------------------------");

    int j = 0;
    for (int i = 0; i < QuadCount; i++) {
        if (strcmp(QuadArray[i].op, "label") == 0) {
            printf("\n%-3d: ", j);
            print_Quad(QuadArray[i]);
        } else {
            printf("%-3d: \t", j);
            print_Quad(QuadArray[i]);
        }
        j++;
    }
    printf("%-120s\n", "------------------------------------------------------------------------------------------------------------------------");
}

void emit(char op[], char res[], char arg1[], char arg2[]) {
    QuadArray[QuadCount] = makeQuad(res, arg1, op, arg2);
    QuadCount++;
}

Sym* gentemp(SymType* type, char init_val[]) {
    char tmp_name[100];
    sprintf(tmp_name, "t%d", currST->count++);
    while (SymTab_lookup(currST, tmp_name, FIND) != NULL) {
        sprintf(tmp_name, "t%d", currST->count++);
    }

    Sym* s = SymTab_lookup(currST, tmp_name, INSERT);
    strcpy(s->name, tmp_name);
    s->type = type;
    s->size = computeSize(type);
    strcpy(s->init_val, init_val);

    return s;
}

// Update offsets of all the symbols in the symbol table
void update_offsets(SymTab* st) {
    int offset = 0;
    for (int i = 0; i < MAX_QUADS; i++) {
        if (st->table[i].name[0] == '\0') {
            break;
        }
        Sym* sym = &st->table[i];
        sym->offset = offset;
        offset += sym->size;
        if (sym->nested != NULL) {
            update_offsets(sym->nested);
        }
    }
}

// Lookup a symbol in the symbol table, whether it exists or not
Sym* SymTab_lookup(SymTab* st, const char* name, int flags) {
    for (int i = 0; i < MAX_QUADS; i++) {
        if (st->table[i].name[0] == '\0') {
            break;
        }

        if (strcmp(st->table[i].name, name) == 0) {
            return &st->table[i];
        }
    }

    if (st->parent != NULL && (flags & FIND)) {
        Sym* ptr = SymTab_lookup(st->parent, name, FIND);
        if (ptr != NULL) {
            return ptr;
        }
    }

    if (flags & INSERT) {
        for (int i = 0; i < MAX_QUADS; i++) {
            if (st->table[i].name[0] == '\0') {
                st->table[i].name = strdup(name);
                return &st->table[i];
            }
        }
    }

    return NULL;
}

void backpatch(int list[], int addr) {
    for (int i = 0; i < MAX_QUADS; i++) {
        if (list[i] == -1) {
            break;
        }
        QuadArray[list[i]].res = addr;
    }
}

int* makelist(int addr) {
    static int list[MAX_QUADS];
    list[0] = addr;
    for (int i = 1; i < MAX_QUADS; i++) {
        list[i] = -1;
    }
    return list;
}

int* merge(int a[], int b[]) {
    static int result[MAX_QUADS];
    int i, j;
    for (i = 0; i < MAX_QUADS; i++) {
        if (a[i] == -1) {
            break;
        }
        result[i] = a[i];
    }
    for (j = 0; j < MAX_QUADS; j++) {
        if (b[j] == -1) {
            break;
        }
        result[i + j] = b[j];
    }
    return result;
}

Expression* convertBoolToInt(Expression* e) {
    if (e->isBoolean) {
        e->loc = gentemp(&makeSymType("int", NULL, 0), "true");
        backpatch(e->truelist, nextinstr());
        emit        ("=", e->loc->name, "true");
        int p = nextinstr() + 1;
        char str[100];
        sprintf(str, "%d", p);
        emit("goto", str, "", "");
        backpatch(e->falselist, nextinstr());
        emit("=", e->loc->name, "false");
    }
    return e;
}

Expression* convertIntToBool(Expression* e) {
    if (!e->isBoolean) {
        e->falselist[0] = nextinstr();
        emit("==", "", e->loc->name, "0");
        e->truelist[0] = nextinstr();
        emit("goto", "", "", "");
    }
    return e;
}

int typecheck(Sym* s1, Sym* s2) {
    SymType* type1 = s1->type;
    SymType* type2 = s2->type;
    if (type1 == NULL && type2 == NULL) {
        return 1; // if both symbol types are NULL
    } else if (type1 == NULL || type2 == NULL || strcmp(type1->type, type2->type) != 0) {
        return 0; // if only one of them is NULL or if base type isn't the same
    }

    return compareSymbolType(type1->arrtype, type2->arrtype);
}

int compareSymbolType(SymType* t1, SymType* t2) {
    int flag = 0;
    if (t1 == NULL && t2 == NULL) {
        flag = 1; // if both symbol types are NULL
    } else if (t1 == NULL || t2 == NULL || strcmp(t1->type, t2->type) != 0) {
        flag = 0; // if only one of them is NULL or if base type isn't the same
    }
    if (flag == 1) {
        return 1;
    } else if (flag == 0) {
        return 0;
    } else {
        return compareSymbolType(t1->arrtype, t2->arrtype);
    }
}

int nextinstr() {
    return QuadCount;
}

int computeSize(SymType* t) {
    if (strcmp(t->type, "void") == 0) {
        return 0;
    } else if (strcmp(t->type, "char") == 0) {
        return size_of_char;
    } else if (strcmp(t->type, "int") == 0) {
        return size_of_int;
    } else if (strcmp(t->type, "ptr") == 0) {
        return size_of_pointer;
    } else if (strcmp(t->type, "func") == 0) {
        return 0;
    } else if (strcmp(t->type, "arr") == 0) {
        return t->width * computeSize(t->arrtype);
    } else {
        return -1;
    }
}

// Function to print the type of a symbol
void printType(SymType *t) {
    if (t == NULL) {
        printf("null");
        return;
    }

    if (strcmp(t->type, "void") == 0) {
        printf("void");
    } else if (strcmp(t->type, "char") == 0) {
        printf("char");
    } else if (strcmp(t->type, "int") == 0) {
        printf("int");
    } else if (strcmp(t->type, "ptr") == 0) {
        printf("ptr(%s)", printType(t->arrtype));
    } else if (strcmp(t->type, "arr") == 0) {
        printf("arr(%d,%s)", t->width, printType(t->arrtype));
    } else if (strcmp(t->type, "func") == 0) {
        printf("func");
    } else if (strcmp(t->type, "block") == 0) {
        printf("block");
    } else {
        printf("NA");
    }
}

void print(SymTab* st) {
    printf("Table Name: %s\n", st->name);

    if (st->retType != NULL) {
        printf("  |  Return Type: %s\n", printType(st->retType));
    }

    printf("------------------------------------------------------------\n");
    printf("%-25s%-20s%-30s%-15s%-15s%-15s\n", "Name", "Type", "Initial Value", "Size", "Offset", "Category");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < MAX_QUADS; i++) {
        if (st->table[i].name[0] == '\0') {
            break;
        }

        Sym* sym = &st->table[i];

        printf("%-25s%-20s%-30s%-15d%-15d%s\n",
               sym->name,
               printType(sym->type),
               (sym->init_val[0] == '\0' || strcmp(sym->init_val, "-") == 0) ? "undefined" : sym->init_val,
               sym->size,
               sym->offset,
               sym->category);

        if (sym->nested != NULL) {
            print(sym->nested);
        }
    }

    printf("------------------------------------------------------------\n");
    printf("\n");
}

// main function
int main(int argc, char** argv) {
    globalST = (SymTab){0};
    currST = &globalST;
    yyparse();
    update_offsets(&globalST);
    printf("\n");

    if (argc > 1 && strcmp(argv[1], "-tac") == 0) {
        print_QuadArray();
        print(&globalST);
    }
    return 0;
}