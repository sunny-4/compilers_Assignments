int main() {
    struct Node n;
    struct Node *p;
    int arr;
    char c;

    p = &n;
    arr = 1;
    arr = arr + "hello" "world"[0];
    p->value = arr;
    n.value = p->value;
    c = 'a';

    return n.value;
}
