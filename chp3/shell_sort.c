// D. I. Shell, invented in 1959
// In early stages far away elements are compared, rather than adjacent ones
// - tends to remove lots of disorder quickly, so later stages have less to do
// - interval between compared elements gradually decreases to one
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(int *v, int n) {
    // v is a list of n elements indexed 0..n-1
    int gap, i, j, temp;

    for(gap = n / 2; gap > 0; gap /= 2) {
        for(i = gap; i < n; i++) {
            for(j = i - gap; j >= 0 && v[j] > v[j + gap]; j-= gap) {
                v[j] ^= v[j + gap];
                v[j + gap] ^= v[j];
                v[j] ^= v[j + gap];
            }
        }
    }
}

int *random_array(int n, int max) {
    int *array = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) {
        array[i] = rand() % max;
    }
    return array;
}

void print_array(int *arr, int size, int items_per_row) {
    for(int i = 0; i < size; i++) {
        printf("%3d%c", arr[i], ((i + 1) % items_per_row) ? ',' : '\n');
    }
    printf("\n");
}

int main() {
    clock_t t;
    int size = 1000000;
    int *v = random_array(size, 100);
    print_array(v, size, 10);
    printf("Sorting %d elements\n", size);
    t = clock();
    shell_sort(v, size);
    t = clock() - t;
    print_array(v, size, 10);
    double secs = ((double)t)/CLOCKS_PER_SEC;
    printf("Time taken %d:%d seconds\n", (int)secs, (int)round(fmod(secs, 1.0) * 60));
}
