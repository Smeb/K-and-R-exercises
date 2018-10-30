#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

char *escape(char s[]) {
    int len = strlen(s);
    int i = 0;
    int w = 0;
    char *t = (char*)malloc(len * 2);
    while(i <= len) {
        switch(s[i]) {
            case '\n': {
                           t[w++] = '\\';
                           t[w++] = 'n';
                           break;
                       }
            case '\t': {
                           t[w++] = '\\';
                           t[w++] = 't';
                           break;
                       }
            case '\\': {
                           t[w++] = '\\';
                           t[w++] = '\\';
                           break;
                       }
            default:
                       t[w++] = s[i];
                       break;
        }
        i++;
    }
    return t;
}

char *unescape(char s[]) {
    int len = strlen(s);
    int i = 0;
    int w = 0;
    char *t = (char*)malloc(len * 2);
    while(i <= len) {
        switch(s[i]) {
            case '\\': {
                            i++;
                            switch(s[i]) {
                                case 'n': t[w++] = '\n'; break;
                                case 't': t[w++] = '\t'; break;
                                case '\\': t[w++] = '\\'; break;
                            }
                            break;
                       }
            default: {
                         t[w++] = s[i];
                         break;
                     }
        }
        i++;
    }
    return t;
}

int main() {
    char str[] = "this is the \t test \n input string\t\t\n";
    printf("%s\n", str);
    char *r = escape(str);
    printf("%s\n", r);
    char *s = unescape(str);
    printf("%s\n", s);
}
