#include <stdio.h>

#define TABSTOP 8

void flush_spaces(int space_start, int space_end) {
    for (int i = space_start; i < space_end; i++)
        putchar('.');
}

int main() {
    int c, i, space_start;
    char buffer[TABSTOP];
    i = 0;
    space_start = -1;

    while((c = getchar()) != EOF) {
        if (space_start == - 1) {
            if (c == ' ')
                space_start = i;
            else
                putchar(c);
        } else {
            if (c == ' ') {
                if (i % TABSTOP == 0) {
                    // If at tabstop, write a tab and start space count from new tabstop
                    putchar('\t');
                    space_start = i;
                }
            } else {
                if (c == '\t') {
                    // A tab overwrites all seen spaces in current tabstop window
                    putchar('\t');
                } else if (i % TABSTOP == 0) {
                    // String of spaces leading to a tabstop
                    putchar('\t');
                    putchar(c);
                } else {
                    // String of spaces then a character before a tabstop
                    flush_spaces(space_start, i);
                    putchar(c);
                }
                space_start = -1;
            }
        }

        if (c == '\n')
            i = 0;
        else
            i++;
    }
}
