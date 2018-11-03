#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"

#define MAX_COMMAND 15

typedef enum {
    ADD,
    ASSIGNMENT,
    DIGIT,
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
    POW,
    REFERENCE,
    PRINT,
    PRINTSTACK
} COMMAND;

struct variable {
    char *name;
    double value;
};

int n_variables = 0;
int variable_heap_size = 256;
int variables_init = 0;
struct variable *variables;
void allocate_variables() {
    variables = realloc(variables, sizeof(struct variable) * variable_heap_size);
    variables_init = 1;
}

char *get_name(char *command) {
    int i;
    for(i = 0; command[i] != '='; i++)
        ;
    char *name = malloc(i + 1);
    for(i = 0; command[i] != '='; i++)
        name[i] = command[i];
    name[i] = '\0';
    return name;
}

int assigned(char *name) {
    for (int i = 0; i < n_variables; i++)
        if(!strncmp(variables[i].name, name, MAX_COMMAND))
            return i;
    return -1;
}

const static struct {
    COMMAND    code;
    const char *str;
} commands[] = {
    {ADD, "+"},
    {MUL, "*"},
    {DIV, "/"},
    {SUB, "-"},
    {MOD, "%"},
    {DUPLICATE, "DUPLICATE"},
    {SWAP, "SWAP"},
    {PEEK, "PEEK"},
    {CLEAR, "CLEAR"},
    {SIN, "SIN"},
    {EXP, "EXP"},
    {POW, "POW"},
    {PRINTSTACK, "PRINTSTACK"}
};

const static struct {
    COMMAND    code;
    const char *str;
} variable_commands[] = {
    { PRINT, "PRINT" }
};

/* validation */
int is_number(char *str) {
    int minuses = 0;
    int periods = 0;
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]))
            continue;
        else if (str[i] == '-')
            minuses++;
        else if (str[i] == '.')
            periods++;
        else
            return 0;
    }

    if (i == 0 || minuses > 1 || periods > 1)
        return 0;
    return 1;
}

int is_reference(char *command) {
    for (int i = 0; command[i] != '\0'; i++)
        if(!isalpha(command[i]))
            return 0;
    return 1;
}

int is_assignment(char *command) {
    int i;
    // assignment names can't have numbers in, or '='
    char reference[MAX_COMMAND];
    for (i = 0; command[i] != '\0' && command[i] != '='; i++)
        reference[i] = command[i];

    if(command[i] != '=')
        return 0;

    reference[i] = '\0';

    return is_reference(reference) && is_number(command + i + 1);
}
/* stack operations */
double pop(double *stack, int * index) {
    if(*index == 0) {
        fprintf(stderr, "Not enough numbers on stack to process code\n");
        exit(1);
    }
    return stack[--(*index)];
}

void push(double val, double *stack, int *index) {
    stack[(*index)++] = val;
}

/* command IO operations */
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

double duplicate(double *stack, int *index) {
    if(stack_empty(*index)) {
        fprintf(stderr, "Error in duplicate: stack is empty");
        exit(1);
    }

    return peek_stack(stack, index);
}

void print_top(double *stack, int *index) {
    printf("%f\n", peek_stack(stack, index));
}

double reference(char *command) {
    int index = assigned(command);
    if (index == -1) {
        fprintf(stderr, "Error: variable %s has not been assigned\n", command);
        exit(1);
    } else {
        return variables[index].value;
    }
}

double intApply2(int code, char *command, double a, double b) {
    switch(code) {
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

    fprintf(stderr, "Logical error: code not defined in apply2 method\n");
    exit(1);
}

void apply2(int code, char *command, double *stack, int *index) {
    double b = pop(stack, index);
    double a = pop(stack, index);

    push(intApply2(code, command, a, b), stack, index);
}

double intApply1(int code, char *command, double a) {
    switch(code) {
        case SIN: return sin(a);
        case EXP: return exp(a);
    }

    fprintf(stderr, "Logical error: code not defined in apply1 method\n");
    exit(1);
}

void apply1(int code, char *command, double *stack, int *index) {
    double a = pop(stack, index);

    push(intApply1(code, command, a), stack, index);
}

double get_val(char *str) {
    int i = 0;
    double val, power;
    int sign = (str[i] == '-') ? -1 : 1;

    if(str[i] == '-')
        i++;

    for(val = 0; str[i] != '\0' && isdigit(str[i]); i++)
        val = val * 10 + str[i] - '0';

    if(str[i] == '\0')
        return sign * val;

    for(power = 1.0; str[i] != '\0'; i++, power *= 10.0)
        val = val * 10 + str[i] - '0';

    return sign * val / power;
}

double intApply0(int code, char *command, double *stack, int *index) {
    switch(code) {
        case DIGIT: return get_val(command);
        case DUPLICATE: return duplicate(stack, index);
        case REFERENCE: return reference(command);
    }

    fprintf(stderr, "Logical error: code not defined in apply0 method\n");
    exit(1);
}

void print(char *command) {
    char *name = strchr(command, ':') + 1;
    int index = assigned(name);
    if (index == -1) 
        printf("Variable %s is not assigned\n", name);
    else
        printf("%s: %f\n", name, variables[index].value);
}

void assignment(char *command) {
    if(variables_init == 0)
        allocate_variables();
    else if(n_variables == variable_heap_size) {
        variable_heap_size *= 2;
        allocate_variables();
    }

    char *name = get_name(command);
    double value = get_val(strchr(command, '=') + 1);
    int assignment = assigned(name);
    printf("%d\n", assignment);
    if (assignment >= 0) {
        variables[assignment].value = value;
        free(name);
    } else {
        struct variable *var = malloc(sizeof(struct variable));
        variables[n_variables].name = name;
        variables[n_variables].value = value;
        n_variables++;
    }
}

void apply0(int code, char *command, double *stack, int *index) {
    push(intApply0(code, command, stack, index), stack, index);
}

void printstack(double *stack, int *index) {
    int i;
    for(i = (*index) - 1; i >= 0; i--)
        printf("%f\n", stack[i]);
    printf("---BOTTOM---\n");
}

void operate(int code, char *command, double *stack, int *index) {
    switch(code) {
        case ASSIGNMENT: return assignment(command);
        case PEEK: return print_top(stack, index);
        case PRINT: return print(command);
        case SWAP: return swap(stack, index);
        case CLEAR: return clear(index);
        case PRINTSTACK: return printstack(stack, index);
    }
    fprintf(stderr, "Logical error: code not defined in operate method\n");
    exit(1);
}

void handle_command(int code, char *command, double *stack, int *index) {
    switch(code) {
        case ASSIGNMENT: case CLEAR: case PEEK: case PRINT: case PRINTSTACK: case SWAP:
            return operate(code, command, stack, index);
        case DIGIT: case DUPLICATE: case REFERENCE:
            return apply0(code, command, stack, index);
        case SIN: case EXP:
            return apply1(code, command, stack, index);
        case ADD: case SUB: case MUL: case DIV: case MOD: case POW:
            return apply2(code, command, stack, index);
    }

    fprintf(stderr, "Error: command code %d not yet implemented for %s\n", code, command);
    exit(1);
}

COMMAND match_command(char *command) {
    for(int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
        if(!strncmp(command, commands[i].str, MAX_COMMAND))
            return commands[i].code;

    for(int i = 0; i < sizeof(variable_commands) / sizeof(variable_commands[0]); i++)
        if(!strncmp(command, variable_commands[i].str, strlen(variable_commands[i].str)))
            return variable_commands[i].code;

    if (is_reference(command))
        return REFERENCE;

    fprintf(stderr, "Command `%s` is not recognized\n", command);
    exit(1);
}

COMMAND read_command(char *command) {
    if(is_number(command))
        return DIGIT;
    else if (is_assignment(command))
        return ASSIGNMENT;
    else
        return match_command(command);
}

char *get_command(char *argument) {
    int i = 0;
    char c;
    while((c = getchar()) && isspace(c))
        ;

    if(c == EOF)
        return NULL;

    ungetc(c, stdin);

    while((c = getchar()) != EOF && !isspace(c) && i < MAX_COMMAND)
        argument[i++] = c;
    if (i == MAX_COMMAND) {
        fprintf(stderr, "max command size of %d exceeded\n", MAX_COMMAND);
        exit(1);
    }

    argument[i] = '\0';

    if (c == EOF)
        ungetc(c, stdin);

    return argument;
}

int main(void) {
    int size = 48;
    char command[MAX_COMMAND + 1];
    double *stack = malloc(size * sizeof(double));
    int index = 0;
    int code;
    while(get_command(command)) {
        code = read_command(command);
        handle_command(code, command, stack, &index);

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
