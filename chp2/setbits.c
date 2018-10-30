#include <stdio.h>
#include <limits.h>

void binary_printer(int value) {
    for(int i = sizeof(int) - 1; i >= 0; i--) {
        for(int j = 7; j >= 0; j--) {
            printf("%u", value >> (8 * i + j) & 1);
        }
    }
    printf("\n");
}

int setbits(int x, int p, int n, int y) {
    int xbits = (x & (~(~(~0 << n) << (p - n + 1))));
    int ybits = (y & ~(~0 << n)) << (p - n + 1);
    return xbits | ybits;
}

int invert(int x, int p, int n) {
    return x ^ ~(~0 << n) << (p - n + 1);
}

int rightrot(x, n) {
    int wrap = x >> (8 * sizeof(x) - n);
    int over = x << n;
    return over | wrap;
}

int main() {
    // setbits(~0, 4, 4, 5);
    // invert(5, 2, 3);
    // rightrot(~0, 3);
    int uintmax = UINT_MAX;
    int onesc = ~0;
    printf("%u\n", onesc);
    printf("%u\n", onesc >> 31);
    printf("%u\n", 5 >> 31);
    printf("%u\n", -5 >> 31);
    return 0;
}

