#include <stdio.h>

int main() {
    int c;
    while((c = getchar()) != EOF) {
        if (c == '\n' || c == '\t' || c == ' ')
            putchar('\n');
        else
            putchar(c);
    }
}
