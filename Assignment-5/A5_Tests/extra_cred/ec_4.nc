int a[3];

int main(){
    a[0] = 3;
    a[1] = 2;
    a[2] = 1;

    a[0] = a[0] * a[1] * a[2];

    int b[1];
    b[0] = a[0];

    char s[14] = "Hello World!\n";
    s[0] = 'c';
    s[0] = 'C';
    
    return 0;
}