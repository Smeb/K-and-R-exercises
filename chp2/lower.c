#include <stdio.h>

void lower(char s[]) {
    for (int i = 0; s[i] != '\0'; i++)
        s[i] = (s[i] > 'Z' || s[i] < 'A') ? s[i] : s[i] - 'A' + 'a';
}

int main() {
    char s[] = "THIS IS A STRING in all caps except the end";
    printf("%s\n", s);
    lower(s);
    printf("%s\n", s);
    printf("%lu\n", sizeof s);
}
