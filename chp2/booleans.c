#include <stdio.h>
#define LIMIT 1000

int main() {
    int i, c;
    char buffer[LIMIT];
    for(i = 0; i < (LIMIT - 1) * (c = getchar()) != '\n' * (c != EOF); i++)
        buffer[i] = c;
    buffer[i] = '\0';
    printf("%s\n", buffer);
}
