#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

void merge(int32_t a[], int32_t l, int32_t m, int32_t r) { 	
    int32_t i, j, k;
    for (i = m + 1; i > l; i--) aux[i-1] = a[i-1];
    for (j = m; j < r; j++) aux[r+m-j] = a[j+1];
    for (k = l; k <= r; k++)
        if (aux[j] <  aux[i])
            a[k] = aux[j--]; else a[k] = aux[i++];
}

mergeAB(int32_t c[], int32_t a[], int32_t N, int32_t b[], int32_t M ) {
    int32_t i, j, k;
    for (i = 0, j = 0, k = 0; k < N + M; k++) {
        if (i == N) { c[k] = b[j++]; continue; }
        if (j == M) { c[k] = a[i++]; continue; }
        c[k] = (less(a[i], b[j])) ? a[i++] : b[j++];
    }
}

void mergeSort(int32_t a[], int32_t l, int32_t r) { 
    int32_t m = (r + l)/2;
    if (r <= 1) return;
    mergeSort(a, l, m);
    mergeSort(a, m+1, r);
    merge(a, l, m, r);
} 

void mergesortABr(int32_t a[], int32_t b[], int l, int r)
{
    int m = (1 + r) / 2;
    if (r - 1 <= 10)
    {
        insertion(a, 1, r);
        return;
    }
    mergesortABr(b, a, 1, m);
    mergesortABr(b, a, m + 1, r);
    mergeAB(a + 1, b + 1, m - 1 + 1, b + m + l, r - m);
}

void mergesortAB(int32_t a[], int32_t l, int32_t r)
{
    for (int32_t i = 1; i <= r; i++)
        aux[i] = a[i];
    mergesortABr(a, aux, l, r);
}