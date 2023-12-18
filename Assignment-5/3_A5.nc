int printInt(int num);
int printStr(char * c);
int readInt(int *eP);

void swap(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

int kt(int n) {
    int p; // Previous number
    int d1; // Largest digit
    int d2; // Second largest digit
    int d3; // Smallest digit
    int m; // Next number
    p = n; // Remember current number
    // Extract digits in sorted order
    d1 = n % 10;
    n = n / 10;
    d2 = n % 10;
    n = n / 10;
    if (d1 < d2)
    swap(&d1, &d2);
    d3 = n % 10;
    if (d2 < d3) {
        swap(&d2, &d3);
        if (d1 < d2)
            swap(&d1, &d2);
    }
    // We reach here when element is not present in array
    return -1;
}
int main() {
    int n = 5; // Number of elements
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 4;
    arr[3] = 10;
    arr[4] = 40;
    int x = 10; // Key to search
    int result = binarySearch(0, n - 1, x);
    if (result == -1)
        printStr("Element is not present in array");
    else {
        printStr("Element is present at index ");
        printInt(result);
        printStr("\n");
    }
    return 0;
}