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

// Program 8: Fibonacci: Co-Recursion
// Find fibonacci by co-recursion
int f_odd(int);
int f_even(int);

int fibonacci(int n) {
    return (n % 2 == 0)? f_even(n): f_odd(n);
}

int f_odd(int n) {
    return (n == 1)? 1: f_even(n-1) + f_odd(n-2);
}

int f_even(int n) {
    return (n == 0)? 0: f_odd(n-1) + f_even(n-2);
}

int main() {
    int n = 10;
    int r;
    r = fibonacci(n);
    printStr("fibo(");
    printInt(n);
    printStr(") = ");
    printInt(r);
    return 0;
}