#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int is_operand(char symbol) {
    switch(symbol) {
        case '*': return 1;
        case '+': return 1;
        case '-': return 1;
        case '/': return 1;
    }
    return 0;
}

int apply(int a, int b, char operand) {
    switch(operand) {
        case '*': return a * b;
        case '+': return a + b;
        case '-': return a - b;
        case '/': return a / b;
    }
    fprintf(stderr, "Logical error: Operand not defined in apply method");
    exit(1);
}

int main(void) {
    int size = 48;
    int *stack = malloc(size * sizeof(int));
    int index = 0;
    char c;
    while(c != EOF && (c = getchar())) {
        if (isdigit(c)) {
            int val = c - '0';
            while((c = getchar()) && isdigit(c)) {
                val = val * 10 + c - '0';
            }
            stack[index++] = val;
        } else if (is_operand(c)) {
            if(index - 2 < 0) {
                fprintf(stderr, "Not enough numbers on stack to process operand\n");
                exit(1);
            }

            int b = stack[--index];
            int a = stack[--index];
            stack[index++] = apply(a, b, c);
        }

        if (index == size) {
            size *= 2;
            stack = realloc(stack, size);
        }
    }

    if(index > 0) {
        printf("%d\n", stack[index - 1]);
    }
}
