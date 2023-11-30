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

// Program 2: Max of 3
// Find max of three numbers
int main() {
    int x = 2;
    int y = 3;
    int z = 1;
    int m;
    m = x > y? x: y;
    m = m > z? m: z;
    printStr("max(");
    printInt(x); printStr(", ");
    printInt(y); printStr(", ");
    printInt(z); printStr(") = ");
    printInt(m);
    return 0;
}