#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int expandable(char s[], int size, int i) {
    if (i + 2 >= size)
        return 0;
    if (s[i + 1] != '-')
        return 0;
    if (s[i] > s[i + 2])
        return 0;
    if (isdigit(s[i]) && isdigit(s[i + 2])) {
        return 1;
    }
    if (isalpha(s[i]) && isalpha(s[i + 2])) {
        if (s[i] >= 'a' && s[i + 2] <= 'z')
            return 1;
        if (s[i] >= 'A' && s[i + 2] <= 'Z')
            return 1;
    }
    return 0;
}

void expand_sequence(const char sequence[], char **output, const int i, int *w, int *size) {
    int expansion = sequence[i + 2] - sequence[i];
    if (*w + expansion + 1 > *size) {
        *size = *size + (*w + expansion - *size) + 1;
        *output = realloc(*output, *size);
    }

    for(int j = sequence[i]; j <= sequence[i + 2]; j++)
        (*output)[(*w)++] = j;
}

char *expand(char s[]) {
    int i, w, len, size;
    w = 0, i = 0;
    len = strlen(s);
    size = len;
    char *output = malloc(len);
    while(i < len) {
        if (expandable(s, len, i)) {
            expand_sequence(s, &output, i, &w, &size);
            i += 3;
        } else {
            output[w++] = s[i++];
        }
    }

    return output;
}

int main(void) {
    char s[] = "a-z";
    char t[] = "A-Z";
    char r[] = "0-9";
    char z[] = "A-Za-z0-9";
    printf("%s\n", expand(s));
    printf("%s\n", expand(r));
    printf("%s\n", expand(t));
    printf("%s\n", expand(z));
}
