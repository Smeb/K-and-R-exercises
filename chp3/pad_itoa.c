#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_str(char *str, int len) {
    char c;
    for (int i = 0; i < len / 2; i++)
        c = str[len - i - 1], str[len - i - 1] = str[i], str[i] = c;
}

char *itoa(int value, int pad) {
    int max_int_size = sizeof(int) * 8 + 2;
    char *output = malloc((pad > max_int_size) ? pad : max_int_size);
    int size = 0;
    int sign = (value > 0) ? 1 : - 1;

    do {
        output[size++] = value % 10 * sign + '0';
    } while (value /= 10);

    while(size < pad - ((sign == 1) ? 0 : 1))
        output[size++] = '0';

    if (sign == -1)
        output[size++] = '-';

    output[size] = '\0';

    reverse_str(output, size);

    return realloc(output, size + 1);
}

int main(void) {
    printf("%s\n", itoa(INT_MAX, 50));
    printf("%s\n", itoa(INT_MIN, 50));
    printf("%s\n", itoa(4, 3));
}
