#include <stdio.h>

#define COLUMN 80

int main() {
    int c;
    int i = 0;
    char line[COLUMN + 1];
    while((c = getchar()) != EOF) {
        if (c == '\n') {
            line[COLUMN] = '\0';
            printf("%sn", line);
            i = 0;
        } else if (i == COLUMN) {
            while(i != 0 && line[i - 1] == '.')
                line[i--] = '\0';
            line[i] = '\0';
            printf("%s\n", line);
            i = 0;
        }
        if (c == ' ' || c == '\t')
            line[i++] = '.';
        else
            line[i++] = c;
    }
}
