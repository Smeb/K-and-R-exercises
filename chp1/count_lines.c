#include <stdio.h>

#define IN  1
#define OUT 0

int main() {
    int c, char_count, word_count, line_count, state;
    state = OUT;
    char_count = 0;
    word_count = 0;
    line_count = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            line_count++;
            state = OUT;
        } else if (c == ' ' || c == '\t') {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            word_count++;
        }
        char_count++;
    }

    printf("words: %d; lines: %d; chars: %d\n", word_count, line_count, char_count);
}
