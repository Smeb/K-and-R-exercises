#include <stdio.h>

int power(int base, int n) {
    int p;
    for (p = 1; n > 0; n--)
        p *= base;
    return p;
}

int main() {
    for (int i = 0; i < 10; i++) {
        printf("%d: %6d %6d\n", i, power(2, i), power(-3, i));
    }

    return 0;
}
