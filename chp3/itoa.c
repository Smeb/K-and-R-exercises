#include <stdio.h>
#include <stdlib.h>

char *itoa(int value) {
    // convert an input value into a string

    int size = 1;
    int max = 10;
    while (value / max) {
        // 100, 2 1000, 3, 10000, 4 100000, 5, 1000000, 6
        max *= 10;
        size += 1;
    }
    max /= 10;

    int sign = (value >= 0) ? 1: -1;
    int i = (sign == 1) ? 0 : 1;
    size = (sign == 1) ? size : size + 1;
    value *= sign;

    char *output = malloc(size + 1);

    if (sign == -1) {
        output[0] = '-';
    }

    for (; i < size; i++) {
        output[i] = '0' + value / max;
        value %= max;
        max /= 10;
    }
    output[size] = '\0';


    return output;
}

int main(void) {
    printf("%s\n", itoa(130101));
    printf("%s\n", itoa(120412010));
    printf("%s\n", itoa(400));
    printf("%s\n", itoa(0));
    printf("%s\n", itoa(-100));
    printf("%s\n", itoa(-130101));
    printf("%s\n", itoa(-120412010));
    printf("%s\n", itoa(-400));
}
