#include <stdio.h>

#define MAX_LEN 9

int main() {
    int c, length;
    int lengths[MAX_LEN];
    length = 0;
    for (int i = 0; i < MAX_LEN; i++) {
        lengths[i] = 0;
    }

    while((c = getchar()) != EOF) {
        if (c == '\t' || c == '\n' || c == ' ') {
            if (length == 0) 
                continue;
            else if (length < MAX_LEN)
                lengths[length - 1]++;
            else 
                lengths[MAX_LEN - 1]++;
            length = 0;
        } else {
            length++;
        }
    }

    int max = 0;
    for (int i = 0; i < MAX_LEN; i++) {
        if (lengths[i] > max)
            max = lengths[i];
    }

    for (int i = max; i > 0; i--) {
        for (int j = 0; j < MAX_LEN; j++) {
            if (lengths[j] >= i)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
    
    for (int i = 0; i < MAX_LEN; i++)
        printf("%c", i + '1');
    printf("+\n");
}
