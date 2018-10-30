#include <stdio.h>

int any(char s1[], char s2[]) {
    for (int i = 0; s1[i] != '\0'; i++) {
        for (int j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j])
                return i;
        }
    }
    return -1;
}

int main() {
    char s1[] = "this is a test string";
    char s2[] = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    char s3[] = "alpaca";

    printf("%d\n", any(s1, s3));
    printf("%d\n", any(s2, s3));
}
