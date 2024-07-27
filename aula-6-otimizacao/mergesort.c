#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void merge(int32_t arr[], int32_t l, int32_t m, uint32_t r) {
    uint32_t i, j, k;
    int32_t n1 = m - l + 1;
    int32_t n2 = r - m;

    int32_t* L = (int32_t*) malloc(n1 * sizeof(int32_t));
    int32_t* R = (int32_t*) malloc(n2 * sizeof(int32_t));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int32_t arr[], int32_t l, int32_t r) {
    if (l < r) {
        int32_t m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
    const uint32_t n = 10000000;
    int32_t* V = (int32_t*) malloc(n * sizeof(int32_t));
    for (uint32_t i = 0; i < n; i++) 
        V[i] = rand() * rand();
    mergeSort(V, 0, n - 1);
    printf("min = %i, max = %i\n", V[0], V[n-1]);
    free(V);
    return 0;
}
