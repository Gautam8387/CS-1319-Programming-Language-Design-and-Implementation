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

// Program 7: Factorial: Recursion
// Find factorial by recursion
int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n-1);
}

int main() {
    int n = 5;
    int r;
    r = factorial(n);
    printInt(n);
    printStr("! = ");
    printInt(r);
    return 0;
}