int helper(int a, int b) {
    return a <= b;
}

int main() {
    int v;
    v = helper(3, 5);

    switch (v) {
        case 0:
            v = v + 10;
            break;
        case 1:
            v = v + 20;
            break;
        default:
            v = v + 30;
    }

    return v;
}
