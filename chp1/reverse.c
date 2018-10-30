#include <stdio.h>

#define MAXLEN 1000

int get_line(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = '\n';

    s[i] = '\0';
    return i;
}

void swap(char s[], int a, int b) {
    char tmp = s[a];
    s[a] = s[b];
    s[b] = s[a];
}

void reverse(char s[], int len) {
    char r[MAXLEN];
    char tmp;
    r[len] = '\0';
    r[len - 1] = '\n';
    for (int i = 0; i < (len - 2) / 2; i++)
        swap(s, i, len - 2 - i);
}

int main() {
    int len;
    char s[MAXLEN];
    while((len = get_line(s, MAXLEN)) != 0) {
        reverse(s, len);
        printf("%s", s);
    }
}
