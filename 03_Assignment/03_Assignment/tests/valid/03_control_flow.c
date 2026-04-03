int main() {
    int i;
    int total;
    i = 0;
    total = 0;

    while (i < 5) {
        total = total + i;
        i++;
    }

    do {
        total = total - 1;
    } while (total > 3);

    for (i = 0; i < 3; i++) {
        if (i == 1) {
            continue;
        } else {
            total = total + 2;
        }
    }

    return total;
}
