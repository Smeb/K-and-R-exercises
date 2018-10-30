#include <stdio.h>

// v has n elements 0..n-1
int binary_search(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while(low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

int binary_search_2(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    mid = (low + high) / 2;
    while(low < high && v[mid] != x) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low + high) / 2;
    }

    if(x == v[mid])
        return mid;
    return -1;
}

int main() {
    int arr1[] = { 0, 0, 1, 2, 3, 4, 5, 101 };
    int arr2[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    int arr3[] = {  };
    int arr4[] = { 1, 5, 9 };
    int arr5[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };

    printf("index: %d\n", binary_search(101, arr1, 8));
    printf("index: %d\n", binary_search(2, arr2, 8));
    printf("index: %d\n", binary_search(0, arr3, 0));
    printf("index: %d\n", binary_search(0, arr4, 3));
    printf("index: %d\n", binary_search(18, arr5, 11));

    printf("index: %d\n", binary_search_2(101, arr1, 8));
    printf("index: %d\n", binary_search_2(2, arr2, 8));
    printf("index: %d\n", binary_search_2(0, arr3, 0));
    printf("index: %d\n", binary_search_2(0, arr4, 3));
    printf("index: %d\n", binary_search_2(18, arr5, 11));
}
