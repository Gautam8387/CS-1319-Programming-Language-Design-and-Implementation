/* Group 03: julius-stabs-back */
/* Gautam Ahuja, Nistha Singh */ 

char* ArrayGrades(int *source, int *destination, int length) {
    int i;
	for (i = 0; i < length; i=i + 1) {
        destination[i] = source[i];
    }
	return destination;
	
	int a = source[0];
	int b = source[1];
	int c = source[2];
	if (a > b) {
        if (a > c) {
            return "Go";
        } else {
            return "Touch";
        }
    } else {
        if (b > c) {
            return "Some";
        } else {
            return "Grass";
        }
    }
	return "Hello, World! Seriously, what is this?";
}