#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_s(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

char *random_string(int size) {
    char *s = malloc(size);
    for (int i = 0; i < size - 1; i++) {
        s[i] = rand() % ('z' - 'a') + 'a';
    }

    s[size - 1] = '\0';

    return s;
}

int main(void) {
    char *s =  random_string(10);
    printf("%s\n", s);
    reverse_s(s);
    printf("%s\n", s);
}
