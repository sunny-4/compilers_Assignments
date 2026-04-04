extern int add(int a, int b) {
    int result;
    result = a + b;
    return result;
}

int main() {
    int x;
    int y;
    int *p;
    x = 10;
    y = 0x1F;
    p = &x;
    y = *p + y;
    y = sizeof(int) + y;
    return y;
}
