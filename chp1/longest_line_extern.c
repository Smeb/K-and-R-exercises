#include <stdio.h>
#define MAXLINE 1000

int max = 0;
char line[MAXLINE];
char longest[MAXLINE];

int get_line(void) {
    int c, i;
    extern char line[];

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;

    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';

    return i;
}

void copy(void) {
    int i = 0;
    extern char line[], longest[];

    while ((longest[i] = line[i]) != '\0')
        i++;
    longest[i] = line[i];
}

int main() {
    int len;
    extern int max;
    extern char longest[];
    while((len = get_line())) {
        if (len > max) {
            max = len;
            copy();
        }
    }
    printf("%s", longest);
}
