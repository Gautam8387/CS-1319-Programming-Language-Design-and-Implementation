int newline(char x){
    if(x == '\n') return 1;
    return 0;
}

void newline_all(char * s, int n){
    int i = 0;
    for(i = 0; i < n; i = i + 1){
        s[i] = '\n';
    }
    return;
}

int main(){
    char s[14] = "Hello World!\n";
    int ret = newline(s[13]);
    newline_all(s, 14);
    return 0;
}