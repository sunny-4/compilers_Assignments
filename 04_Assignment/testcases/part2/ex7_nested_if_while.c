int main() {
    int i;
    int ans;
    i = 0;
    ans = 0;
    while (i < 10) {
        if (i % 2 == 0) {
            ans = ans + i;
        }
        i = i + 1;
    }
    return ans;
}
