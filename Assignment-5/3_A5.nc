int d = 99;

int fun(int c){
    if(c%d == 0) return c;
    else return c+1;
}

int main(){
    int a = 1;
    int ret = fun(a);
    return 0;
}