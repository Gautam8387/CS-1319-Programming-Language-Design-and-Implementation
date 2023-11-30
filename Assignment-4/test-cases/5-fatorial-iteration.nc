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

// Program 5: Factorial: Iteration
// Find factorial by iteration
int main() {
    int n;
    int i = 0;
    int r = 1;
    readInt(&n);
    for(i = 1; i <= n; i = i + 1)
        r = r * i;
    printInt(n);
    printStr("! = ");
    printInt(r);
    return 0;
}