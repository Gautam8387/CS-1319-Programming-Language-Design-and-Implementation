int printInt(int num);
int printStr(char * c);
int readInt(int *eP);

int main(){
    int ret = printStr("Hello World\n");
    ret = printInt(ret);
    int read = readInt(0);
}