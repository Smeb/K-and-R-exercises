#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

char map_digit(int digit) {
    switch (digit) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        default: exit(1);
    }
}

void reverse_str(char *str, int len) {
    char c;
    for (int i = 0; i < len / 2; i++)
        c = str[i], str[i] = str[len - i - 1], str[len - i - 1] = c;
}

char *itob(int n, int base) {
    if (base <= 1)
        return NULL;
    char *output = malloc(sizeof(int) * 8 + 2);
    int sign = (n > 0) ? 1 : -1;
    int size = 0;
    do {
        output[size++] = map_digit(n % base * sign);
    } while (n /= base);
    if (sign == -1)
        output[size++] = '-';
    output[size] = '\0';

    reverse_str(output, size);

    return realloc(output, size + 1);
}

void print_row(int value, int base) {
        printf("%34s %12d %2d\n", itob(value, base), value, base);
}

int main(void) {
    printf("%34s %12s %2s\n", "value in base", "base 10", "base");
    for (int i = 2; i < 16; i++) {
        print_row(INT_MAX, i);
        print_row(INT_MIN, i);
    }
}
