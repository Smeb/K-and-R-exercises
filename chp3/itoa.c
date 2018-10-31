#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char *itoa2(int value) {
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

void reverse_str(char *str) {
    char c;
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
        c = str[len - i - 1], str[len - i - 1] = str[i], str[i] = c;
}

char *itoa(int value) {
    char *output = malloc(sizeof(int) + 2);
    int size = 0;
    int sign = (value > 0) ? 1 : - 1;

    do {
        output[size++] = value % 10 * sign + '0';
    } while (value /= 10);

    if (sign == -1)
        output[size++] = '-';

    output[size] = '\0';

    reverse_str(output);

    output = realloc(output, size + 1);

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
    printf("%s\n", itoa(INT_MIN));
    printf("%s\n", itoa(INT_MAX));
}
