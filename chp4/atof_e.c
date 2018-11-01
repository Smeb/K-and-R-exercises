#include <ctype.h>
#include <math.h>
#include <stdio.h>

double atof(char *s) {
    double val, power;
    int exponent, i, sign;

    for (i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++, power *= 10.0)
        val = 10.0 * val + (s[i] - '0');

    val = sign * val / power;
    if (s[i] == 'e')
        i++;

    sign = (s[i] == '-') ? -1 : 1;

    for (exponent = 0; isdigit(s[i]); i++)
        exponent = 10 * exponent + (s[i] - '0');

    return val * pow(10, sign * exponent);
}

int main(void) {
    printf("%f\n", atof("10.00e0"));
}
