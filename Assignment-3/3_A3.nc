int main() {
	int a = 1 + 2;
	//This is a comment
	int b = 3 - (-4); //So is this
	int c = -a;
	int d = a *b;
	int e = a / b;
	int f = a % b;

	int* aptr = &a;
	int g = aptr->node;

	int i;
    // int arr[5] = {1,2,3,4,5};

	for ( i = 0 ; i<= 5 ; i = i + 1 ) {
		if (*aptr > b) {
			return 1;
		} else if (a != b) {
			return 0;
		} else {
			return f;
		} 
	}
}