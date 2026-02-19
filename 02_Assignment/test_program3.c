// Test Program 3 - Functions and Pointers

extern void external_func();

int add(int a, int b) {
    return a + b;
}


double calculate(float x, float y) {
    double result = 0.0;
    result = x + y;
    return result;
}

int main() {
    int x = 5;
    int *ptr = &x;
    int **pptr = &ptr;
    
    // Function call
    int sum = add(10, 20);
    
    // Sizeof operator
    long size = sizeof(int);
    
    // Pointer operations
    *ptr = 100;
    
    // String test
    char str[] = "Hello World";
    
    // Hex and special chars
    int hex = 0xABCD;
    char newline = '\n';
    char tab = '\t';
    
    return 0;
}
