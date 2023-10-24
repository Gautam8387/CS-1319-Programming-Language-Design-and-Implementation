/* Group 03: julius-stabs-back */
/* Gautam Ahuja, Nistha Singh */ 

char* copyArray(int *source, int *destination, int length) {
    int i;
	for (i = 0; i < length; i=i + 1) {
        destination[i] = source[i];
    }
	return destination;
	// Get Grades
	int a = source[0];
	int b = source[1];
	int c = source[2];
	if (a > b) {
        if (a > c) {
            return a;
        } else {
            return c;
        }
    } else {
        if (b > c) {
            return b;
        } else {
            return c;
        }
    }
	return "Hello, World!";
}
