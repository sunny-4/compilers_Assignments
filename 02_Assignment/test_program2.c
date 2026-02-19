// Test Program 2 - Loops and Arrays

int main() {
    int arr[10];
    int i = 0;
    
    // For loop test
    for (i = 0; i < 10; i++) {
        arr[i] = i * 2;
    }
    
    // While loop test
    while (i > 0) {
        i--;
    }
    
    // Do-while loop test
    do {
        i++;
    } while (i < 5);
    
    // Switch statement test
    switch (i) {
        case 1:
            break;
        case 2:
            break;
        default:
            break;
    }
    
    return 0;
}
