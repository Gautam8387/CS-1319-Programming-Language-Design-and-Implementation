char alph(int i){
    if(i%2 == 0) return 'o';
    return 'e';
}

char up(char x){
    if(x == 'i') return 'I';
    return 'O';
}

char * make_string(char x){
    if(x == 'O'){
        char * res = "4Odd";
        return res;
    }
    else{
        char * res = "5Even";
        return res;
    }
}
int main(){
    char r = alph(1319);
    r = alph(1319-1);
    r = up(r);
    char * str = make_string(r);
    return 0;
}