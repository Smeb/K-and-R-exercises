#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int head_match(char *str, char *match) {
    for(int i = 0; i < strlen(match); i++)
        if(str[i] != match[i])
            return 0;
    return 1;
}

int str_index(char *str, char *cmp) {
    int i, j, k;
    for (i = 0; str[i] != '\0'; i++) {
        for (j = i, k = 0; cmp[k] != '\0' && str[j] == cmp[k]; j++, k++)
            ;
        if (cmp[k] == '\0')
            return i;
    }


    return -1;
}

int get_line(char *str, int lim) {
    int i = 0;
    char c;

    while(--lim > 0 && (c = getchar()) != '\n' && c != EOF)
        str[i++] = c;

    str[i] = '\0';
    return i;
}

int main(void) {
    char match[] = "ould";
    char str[1000];
    int matches = 0;

    while((get_line(str, 1000))) {
        if(str_index(str, match) != -1) {
            matches++;
            printf("%s\n", str);
        }
    }
    return matches;
}
