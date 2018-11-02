#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int is_operand(char symbol) {
    switch(symbol) {
        case '*': return 1;
        case '+': return 1;
        case '-': return 1;
        case '/': return 1;
        case '%': return 1;
    }
    return 0;
}

double apply(double a, double b, char operand) {
    switch(operand) {
        case '*': return a * b;
        case '+': return a + b;
        case '-': return a - b;
        case '/': {
                      if (b == 0) {
                          fprintf(stderr, "Attempted division by zero in %f / %f\n", a, b);
                          exit(1);
                      }
                      return a / b;
                  }
        case '%': {
                      return fmod(a, b);
                  }
    }
    fprintf(stderr, "Logical error: Operand not defined in apply method\n");
    exit(1);
}

double pop(double *stack, int * index) {
    if(*index == 0) {
        fprintf(stderr, "Not enough numbers on stack to process operand\n");
        exit(1);
    }
    return stack[--(*index)];
}

double get_val(char c, int *index) {
    int sign = (c == '-') ? -1 : 1;
    double val, power;
    
    val = (isdigit(c)) ? c - '0' : 0.0;

    while((c = getchar()) && isdigit(c))
        val = val * 10 + c - '0';

    if(c != '.')
        return sign * val;

    for(power = 1.0; (c = getchar()) && isdigit(c); power *= 10.0)
        val = val * 10 + c - '0';

    return sign * val / power;
}

void push(char c, double *stack, int *index) {
    stack[(*index)++] = get_val(c, index);
}

void handle_operand(char c, double *stack, int *index) {
    double b = pop(stack, index);
    double a = pop(stack, index);
    stack[(*index)++] = apply(a, b, c);
}

void handle_value(char c, double *stack, int *index) {
    push(c, stack, index);
}

int main(void) {
    int size = 48;
    double *stack = malloc(size * sizeof(double));
    int index = 0;
    char c, peek;
    while(c != EOF && (c = getchar())) {
        if (c == '-') {
            peek = getchar();
            ungetc(peek, stdin);
            if (isdigit(peek)) {
                handle_value(c, stack, &index);
            } else {
                handle_operand(c, stack, &index);
            }
        } else if (isdigit(c)) {
            handle_value(c, stack, &index);
        } else if (is_operand(c)) {
            handle_operand(c, stack, &index);
        }

        if (index == size) {
            size *= 2;
            stack = realloc(stack, size);
        }
    }

    if(index > 0) {
        printf("Result: %f\n", stack[index - 1]);
    }
    free(stack);
}
