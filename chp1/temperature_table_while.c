#include <stdio.h>

void fahr_to_celsius_table() {
    float fahr, celsius;
    int lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;

    printf("Fahrenheit | Celsius\n");
    while(fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%10.0f %9.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

void celsius_to_fahr_table() {
    float fahr, celsius;
    int lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;

    printf("Celsius | Fahrenheit\n");
    while(celsius <= upper) {
        fahr = (9.0/5.0) * celsius + 32.0;
        printf("%8.0f %11.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}

int main() {
    fahr_to_celsius_table();
    celsius_to_fahr_table();
}
