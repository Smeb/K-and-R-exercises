#include <stdio.h>

void remove_c(char s[], int i) {
    int j = i + 1;
    while(s[j] != '\0') {
        s[i++] = s[j++];
    }
    s[i] = s[j];
}

void squeeze(char s1[], char s2[]) {
    int k = 0;
    for(int i = 0; s1[i] != '\0'; i++) {
        int j;
        for(j = 0; (s1[i] != s2[j]) && s2[j] != '\0'; j++)
            ;
        if(s2[j] == '\0')
            s1[k++] = s1[i];
    }
    s1[k] = '\0';
}

int main() {
    char s1[] = "this is a test string";
    char s2[] = "this is a test string";
    char s3[] = "abcdefghi ";

    printf("%s\n", s1);
    squeeze(s1, s3);
    printf("%s\n", s1);
}
