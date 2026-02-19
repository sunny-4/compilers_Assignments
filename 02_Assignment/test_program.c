// Sample C-like program to test the lexer

int main() {
    int x = 10;
    float y = 3.14;
    char ch = 'a';
    
    // Test all operators
    int sum = x + 5;
    int diff = x - 3;
    int prod = x * 2;
    int quot = x / 2;
    int rem = x % 3;
    
    // Relational operators
    if (x < 20) {
        x++;
    }
    
    if (x > 5) {
        x--;
    }
    
    if (x <= 15) {
        sum = sum + 1;
    }
    
    if (x >= 10) {
        sum = sum - 1;
    }
    
    if (x == 10) {
        x = x * 2;
    }
    
    if (x != 0) {
        x = x / 2;
    }
    
    // Logical operators
    if (x > 5 && x < 20) {
        x = x + 1;
    }
    
    if (x < 5 || x > 15) {
        x = x - 1;
    }
    
    // Bitwise operators
    int a = 5 & 3;
    int b = 5 | 3;
    int c = 5 ^ 3;
    int d = ~5;
    
    // Hexadecimal
    int hex = 0x1A2B;
    int hex2 = 0xFFFF;
    
    // Pointers
    int *ptr;
    int **pptr;
    int &ref = x;
    
    // Structure access
    struct Point {
        int x;
        int y;
    };
    
    struct Point p;
    p.x = 10;
    p.y = 20;
    
    struct Point *ppt;
    ppt->x = 30;
    ppt->y = 40;
    
    // Special operator
    int comp = (x <=> y);
    
    /* Multi-line comment
       testing multiple lines
       of comments */
    
    return 0;
}
