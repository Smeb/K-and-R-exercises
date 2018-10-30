#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8

int main()
{
        int c, i;
        i = 0;

        while((c = getchar()) != EOF) {
            if (c == '\t') {
                putchar(' ');
                i++;
                while(i % TABSTOP != 0) {
                    putchar(' ');
                    i++;
                }
            } else if (c == '\n') {
                putchar(c);
                i = -1;
            } else {
                putchar(c);
            }
            i++;
        }

        return 0;
}
