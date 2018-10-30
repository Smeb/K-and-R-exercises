#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

int any(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0') {
        int j = 0;
        while (s2[j] != '\0') {
            if(s2[j++] == s1[i])
                return i;
        }
        i++;
    }

    return -1;
}

int atoi1(char s[]) {
    int i = 0;
    int value = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; i++)
        value = 10 * value + (s[i] - '0');
    return value;
}

int lower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    else
        return c;
}

int htoi(char s[]) {
    int i = 0;
    int len = strlen(s);
    int sum = 0;
    if (len > 3 && (s[1] == 'x' || s[1] == 'X'))
        i = 2;
    while (i < len) {
        sum *= 16;
        if (s[i] >= 'a' && s[i] <= 'f')
            sum += s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            sum += s[i] - 'A' + 10;
        else if (isdigit(s[i]))
            sum += s[i] - '0';
        else
            printf("String contains invalid characters");
        i++;
    }

    return sum;
}

int main() {
    printf("%s, 0x%x\n", "0x4001", htoi("0x4001"));
    printf("%s, 0x%x\n", "0X4001", htoi("0X4001"));
    printf("%s, 0x%x\n", "4001", htoi("4001"));
    printf("%s, 0x%x\n", "abcdef", htoi("abcdef"));
    printf("%s, 0x%x\n", "a", htoi("a"));
    printf("%s, 0x%d\n", "4001", atoi1("4001"));
    printf("%c, %c, %c, %c\n", 'c', lower('c'), 'C', lower('C'));
    printf("%s : %s ; %d\n", "test", "no", any("test", "no"));
    printf("%s : %s ; %d\n", "test", "no", any("test", "e"));
}
