#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

int aux[20];

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(int E[], int first, int last) {
	if ((last - first) < 1) { return; }
	for (int i = (first + 1); i <= last; i++) {
		for (int j = i; j > first; j--) {
			if (E[j] < E[j - 1]) {
                 trocar(&E[j], &E[j - 1]); 
            }
            break;
		}
	}
}

void mergeAB(int c[], int a[], int N, int b[], int M ) {
    int i = 0, j = 0, k = 0;
    for (; k < N + M; k++) {
        if (i == N) { c[k] = b[j++]; continue; }
        if (j == M) { c[k] = a[i++]; continue; }
        c[k] = (a[i] < b[j]) ? a[i++] : b[j++];
    }
}

void mergesortABr(int a[], int b[], int l, int r) {
    printf("MergeSortABr\n");
    printf("l = %i, r = %i\n aux = ", l, r);
    for (int i = l; i <= r; i++)
        printf(" %i ", aux[i]);
    printf("\n");

    int m = (l + r) / 2;
    if (r - l <= 10) {
        insertionSort(a, l, r);
        return;
    }
    mergesortABr(b, a, l, m);
    mergesortABr(b, a, m+1, r);
    mergeAB(a+1, b+1, m-l+1, b+m+1, r - m);
}

void mergesortAB(int a[], int l, int r) {
    for (int i = l; i <= r; i++)
        aux[i] = a[i];
    mergesortABr(a, aux, l, r);
}

int main() {
    const int n = 20;
    int* V = (int*) malloc(n * sizeof(int));
    int* B = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        V[i] = rand() % 10;

    // for (uint32_t i = 0; i < n; i++)
    //     V[i] = rand() * rand();
    mergesortAB(V, 0, 19);
    for (int i = 0; i < n; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
    printf("min = %i, max = %i\n", V[0], V[n-1]);
    free(V);
    return 0;
}