#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("%d\n", CHAR_MAX);
    printf("%d\n", SHRT_MAX);
    printf("%d\n", INT_MAX);
    printf("%ld\n", LONG_MAX);

    printf("%f\n\n", FLT_MAX);
    printf("%f\n\n", DBL_MAX);
    printf("hello " "world\n");
    printf("%d\n", (+3) - (-2));
}
