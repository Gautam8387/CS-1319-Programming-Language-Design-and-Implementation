int factorial(int n) {
    int result = 1;
	int i=0;
    for (i=1;i<=n;i=i+ 1) {
        result = result * i;
    }
    return result;
}
