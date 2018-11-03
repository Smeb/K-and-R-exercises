#include <stdio.h>
#include <string.h>

#define BUFFER_MAX 5
int reader = 0;
int writer = 0;
char buffer[BUFFER_MAX];

void inc(int *value) {
    *value = (*value + 1) % BUFFER_MAX;
}

void ungets(char *s) { 
    for(int i = 0; s[i] != '\0'; i++) {
        buffer[writer] = s[i];
        inc(&writer);
        if(writer == reader)
            inc(&reader);
    }
}

char getsc() {
    char c;
    if (reader != writer) {
        c = buffer[reader];
        inc(&reader);
    } else {
        c = getchar();
    }
    return c;
}

void get_str(char *s) {
    int i;
    char c;
    for(i = 0; (c = getsc()) != EOF; i++)
        s[i] = c;
    s[i] = '\0';
}

void zero_str(char *s) {
    for(int i = 0; s[i] != '\0'; i++)
        s[i] = '\0';
}

int main(void) {
    char s[1000];
    int i = 0;
    char c;

    get_str(s);
    printf("str: %s", s);
    ungets(s);
    zero_str(s);
    printf("str: %s\n", s);
    get_str(s);
    printf("str: %s", s);
    return 0;
}
