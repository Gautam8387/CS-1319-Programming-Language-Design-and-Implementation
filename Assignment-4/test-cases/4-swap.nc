// AUX Funtions
int printInt(int x){
    return x;
}
int readInt(int *n){
    return *n;
}
char printStr(char *s){
    return *s;
}

// Program 4: Swap
// Swap two numbers
void swap(int*, int*);
int main() {
    int x;
    int y;
    readInt(&x);
    readInt(&y);
    printStr("Before swap:\n");
    printStr("x = "); printInt(x);
    printStr(" y = "); printInt(y);
    swap(&x, &y);
    printStr("\nAfter swap:\n");
    printStr("x = "); printInt(x);
    printStr(" y = "); printInt(y);
    return 0;
}

void swap(int *p, int *q) {
    int t;
    t = *p;
    *p = *q;
    *q = t;
    return;
}
