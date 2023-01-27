#include "solutions.h"

//running_total
int sum = 0;
int running_total(int x) {
    sum += x;
    return sum;
}

//reverse
int *reverse(int arr[], int len) {
    int *r = (int *)calloc(len, sizeof(int));
    for (int i = len-1; i >= 0; i--) {
        r[len - i - 1] = arr[i];
    }
    return r;
}

//reverse_in_place
void reverse_in_place(int arr[], int len) {
    int rp = 0;
    for (int i = 0; i<len/2; i++) {
        rp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i- 1] = rp;
    }
    for (int i = 0; i < len; i++) {
        printf("%d", arr[i]);
    }
}

//num_occurences
int num_occurences(int arr[], int len, int num) {
    int count = 0;
    for (int i = 0; i<len; i++) {
        if (arr[i] == num) {
            count++;
        }
    }
    return count;
}