#include <stdio.h>

int main() {
    int value = 13;
    int count = 0;
    while(value != 0) {
        value &= value - 1;
        count += 1;
    }
    printf("%d\n", count);
}
