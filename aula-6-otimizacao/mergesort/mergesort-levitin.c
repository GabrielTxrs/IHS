#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
void merge(int32_t B[], int32_t p, int32_t C[], int32_t q, int32_t A[]) {
    uint32_t i = 0, j = 0, k = 0;

    while (i < p && j < q) {
        if (B[i] <= C[j]) {
            A[k] = B[i];
            i++;
        } else {
            A[k] = C[j];
            j++;
        }
        k++;
    }
    if(i == p) {
        while (j < q) {
            A[k] = C[j];
            j++;
            k++;
        }
    } else {
        while (i < p) {
            A[k] = B[i];
            i++;
            k++;
        }
    }
}
void mergeSort(int32_t *A, int32_t n) {
    if (n > 1) {
        int32_t mid = n / 2;
        int32_t *B = (int32_t *)malloc(mid * sizeof(int32_t));
        int32_t *C = (int32_t *)malloc((n - mid) * sizeof(int32_t));

        for (int32_t i = 0; i < mid; i++) {
            B[i] = A[i];
        }

        for (int32_t i = mid; i < n; i++) {
            C[i - mid] = A[i];
        }

        mergeSort(B, mid);
        mergeSort(C, n - mid);
        merge(B, mid, C, n - mid, A);

        free(B);
        free(C);
    }
}

int main() {
    const uint32_t n = 10000000;
    int32_t* V = (int32_t*) malloc(n * sizeof(int32_t));
    for (uint32_t i = 0; i < n; i++)
        V[i] = rand() * rand();
    mergeSort(V, n);
    printf("min = %i, max = %i\n", V[0], V[n-1]);
    free(V);
    return 0;
}