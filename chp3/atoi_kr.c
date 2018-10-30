#include <stdio.h>
#include <ctype.h>

int atoi2(char s[]) {
    int i, sign, sum;
    i = 0;
    for(i = 0; s[i] == ' ' && s[i] != '\0'; i++)
        ;

    sign = s[i] == '-' ? -1: 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for(sum = 0; isdigit(s[i]); i++) {
        sum = sum * 10 + s[i] - '0';
    }
    return sign * sum;
}

int main() {
    printf("%s, %d", "   -101000", atoi2("   -101000"));
}
