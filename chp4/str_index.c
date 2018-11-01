#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strindex(char *s, char *t) {
    int j, k;
    for (int i = strlen(s) - 1; i >= 0; i--) {
        for (j = i, k = 0; s[j] != '\0' && t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (t[k] == '\0')
            return i;
    }
    return -1;
}

int get_line(char *s, int lim) {
    char c;
    int i = 0;
    while(lim-- > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

int main() {
    int size = 1000;
    char match[] = "ould";
    char *s = malloc(size);
    while(get_line(s, size)) {
        printf("%d\n", strindex(s, match));
    }
}
