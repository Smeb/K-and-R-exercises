#include <stdio.h>

#define MAX_LINE 1000
#define MAX_LINES 1000

int get_line(char line[], int max_line);

int whitespace(char c) {
    return c == '\n' || c == ' ' || c == '\t';
}

int delete_trailing(char s[], int end_index) {
    if (end_index == 0)
        return 0;

    int index = end_index - 1; 
    while (index > 0 && whitespace(s[index])) {
        index--;
    }

    if (!whitespace(s[index]))
        index++;

    if (index != 0 && index < end_index) {
        s[index++] = '\n';
    }
    s[index] = '\0';

    return index;
}

int get_line(char s[], int lim) {
    int i = 0;
    int c;

    for (i = 0; (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';

    return i;
}

int main() {
    char lines[MAX_LINES][MAX_LINE];
    int n_lines = 0;
    int len;

    while((len = get_line(lines[n_lines], MAX_LINE)) > 0 && n_lines < MAX_LINES) {
        len = delete_trailing(lines[n_lines], len);

        if (len != 0) {
            n_lines++;
        }
    }

    for (int line = 0; line < n_lines; line++) {
        printf("%s", lines[line]);
    }
}
