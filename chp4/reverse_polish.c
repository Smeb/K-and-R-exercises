#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"

#define MAX_COMMAND 10

enum {
    ADD,
    MUL,
    DIV,
    SUB,
    MOD,
    DUPLICATE,
    SWAP,
    PEEK,
    CLEAR,
    SIN,
    EXP,
    POW
};

int is_unary_operand(char operand) {
    switch(operand) {
        case '*': case '+': case '-': case '/': case '%':
            return 1;
    }
    return 0;
}

double pop(double *stack, int * index) {
    if(*index == 0) {
        fprintf(stderr, "Not enough numbers on stack to process operand\n");
        exit(1);
    }
    return stack[--(*index)];
}

void push(double val, double *stack, int *index) {
    stack[(*index)++] = val;
}

void clear(int *index) {
    *index = 0;
}

void swap(double *stack, int *index) {
    double a = pop(stack, index);
    double b = pop(stack, index);
    push(a, stack, index);
    push(b, stack, index);
}

int stack_empty(int index) {
    return index <= 0;
}

double peek_stack(double *stack, int *index) {
    if (stack_empty(*index)) {
        fprintf(stderr, "Error in peek: stack is empty\n");
        exit(1);
    }
    return stack[*index - 1];
}

void duplicate(double *stack, int *index) {
    if(stack_empty(*index)) {
        fprintf(stderr, "Error in duplicate: stack is empty");
        exit(1);
    }

    stack[*index] = peek_stack(stack, index);
    (*index)++;
}

void print_top(double *stack, int *index) {
    printf("%f\n", peek_stack(stack, index));
}

double intApply2(char operand, double a, double b) {
    switch(operand) {
        case MUL: return a * b; break;
        case ADD: return a + b; break;
        case SUB: return a - b; break;
        case DIV: {
                      if (b == 0) {
                          fprintf(stderr, "Attempted division by zero in %f / %f\n", a, b);
                          exit(1);
                      }
                      return a / b;
                  }
        case MOD: {
                      return fmod(a, b);
                  }
        case POW: return pow(a, b);
    }

    fprintf(stderr, "Logical error: Operand not defined in apply2 method\n");
    exit(1);
}

void apply2(char operand, double *stack, int *index) {
    double b = pop(stack, index);
    double a = pop(stack, index);

    push(intApply2(operand, a, b), stack, index);
}

double intApply1(char operand, double a) {
    switch(operand) {
        case SIN: return sin(a);
        case EXP: return exp(a);
    }

    fprintf(stderr, "Logical error: Operand not defined in apply1 method\n");
    exit(1);
}

void apply1(char operand, double *stack, int *index) {
    double a = pop(stack, index);

    push(intApply1(operand, a), stack, index);
}

int compare(char *command, char *possible_command) {
    if(strncmp(command, possible_command, MAX_COMMAND) == 0)
        return 1;
    return 0;
}

int match_command(char *command) {
    int code;
    if(compare(command, "CLEAR"))
        code = CLEAR;
    else if (compare(command, "DUPLICATE"))
        code = DUPLICATE;
    else if (compare(command, "PEEK"))
        code = PEEK;
    else if (compare(command, "SWAP"))
        code = SWAP;
    else if (compare(command, "POW"))
        code = POW;
    else if (compare(command, "EXP"))
        code = EXP;
    else if (compare(command, "SIN"))
        code = SIN;
    else
        code = -1;

    if (code == -1) {
        fprintf(stderr, "Command `%s` is not recognized\n", command);
        exit(1);
    }
    free(command);
    return code;
}

void handle_command(int command, double *stack, int *index) {
    switch(command) {
        case PEEK: return print_top(stack, index);
        case SWAP: return swap(stack, index);
        case DUPLICATE: return duplicate(stack, index);
        case CLEAR: return clear(index);
        case SIN: return apply1(SIN, stack, index);
        case EXP: return apply1(EXP, stack, index);
        case POW: return apply2(POW, stack, index);
    }
    fprintf(stderr, "Error: command code %d not yet implemented\n", command);
    exit(1);
}

char *get_command(char first_letter) {
    int w = 0;
    char c;
    char *command = malloc(MAX_COMMAND + 1);
    command[w++] = first_letter;
    while((c = getchar()) != EOF && !isspace(c) && w < MAX_COMMAND)
        command[w++] = c;

    if(w == MAX_COMMAND && !isspace(c)) {
        fprintf(stderr, "Command sequence length too long, max length is %d\n", MAX_COMMAND);
        exit(1);
    }

    command[w] = '\0';
    return command;
}

void handle_operand(char first_letter, double *stack, int *index) {
    if (is_unary_operand(first_letter)) {
        switch(first_letter) {
            case '*': return apply2(MUL, stack, index);
            case '+': return apply2(ADD, stack, index);
            case '-': return apply2(SUB, stack, index);
            case '/': return apply2(DIV, stack, index);
            case '%': return apply2(MOD, stack, index);
        }
    } else {
        int command = match_command(get_command(first_letter));
        return handle_command(command, stack, index);
    }
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

void handle_value(char c, double *stack, int *index) {
    push(get_val(c, index), stack, index);
}

int main(void) {
    int size = 48;
    double *stack = malloc(size * sizeof(double));
    int index = 0;
    char c, peek;
    while((c = getchar())) {
        if (c == EOF) {
            break;
        } else if (c == '-') {
            peek = getchar();
            ungetc(peek, stdin);
            if (isdigit(peek)) {
                handle_value(c, stack, &index);
            } else {
                handle_operand(c, stack, &index);
            }
        } else if (isdigit(c)) {
            handle_value(c, stack, &index);
        } else if (!isspace(c)) {
            handle_operand(c, stack, &index);
        }

        if (index == size) {
            size *= 2;
            stack = realloc(stack, size);
        }
    }

    if(!stack_empty(index)) {
        print_top(stack, &index);
    }
    free(stack);
}
