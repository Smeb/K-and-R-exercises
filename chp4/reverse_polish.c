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
        case '/': {
                      if (b == 0) {
                          fprintf(stderr, "Attempted division by zero in %d / %d\n", a, b);
                          exit(1);
                      }
                      return a / b;
                  }
    }
    fprintf(stderr, "Logical error: Operand not defined in apply method\n");
    exit(1);
}

int pop(int *stack, int * index) {
    if(*index == 0) {
        fprintf(stderr, "Not enough numbers on stack to process operand\n");
        exit(1);
    }
    return stack[--(*index)];
}

void push(char c, int *stack, int *index) {
    int val = c - '0';
    while((c = getchar()) && isdigit(c)) {
        val = val * 10 + c - '0';
    }
    stack[(*index)++] = val;
}

int main(void) {
    int size = 48;
    int *stack = malloc(size * sizeof(int));
    int index = 0;
    char c;
    while(c != EOF && (c = getchar())) {
        if (isdigit(c)) {
            push(c, stack, &index);
        } else if (is_operand(c)) {
            int b = pop(stack, &index);
            int a = pop(stack, &index);
            stack[index++] = apply(a, b, c);
        }

        if (index == size) {
            size *= 2;
            stack = realloc(stack, size);
        }
    }

    if(index > 0) {
        printf("Result: %d\n", stack[index - 1]);
    }
    free(stack);
}
