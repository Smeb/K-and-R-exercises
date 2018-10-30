#include <stdio.h>

void binary_printer(int value) {
    for (int i = 3; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            printf("%u", value >> (i * 8 + j) & 1);
        }
    }
    printf("\n");
}

// 76543210
int getbits(int x, int p, int n) {
    return (x >> (p - n + 1)) & ~(~0 << n);
}

int main() {
    binary_printer(0xFF);
    binary_printer(getbits(0xFF, 9, 3));
}
