#include <ctype.h>
#include <stdio.h>

double atof(char *s) {
    double val, power;
    int i, sign;

    for(i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++, power *= 10)
        val = 10.0 * val + (s[i] - '0');

    return sign * val / power;
}

int main(void) {
    printf("%f\n", atof("10.01"));
    printf("%f\n", atof("-10.01"));
    printf("%f\n", atof("9.01"));
    printf("%f\n", atof("9"));
}
