int main(){
    char * s = "abc\n";
    int * a = s;
    void * b = a;
    b = s;
    s = b;
    a = b;
}