#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
void trocar(int32_t* i, int32_t* j) {
    int32_t k = *i;
    *i = *j; *j = k;
}
void heapify(int32_t* V, uint32_t i, uint32_t n) {
    uint32_t P = i, E = 2 * i + 1, D = 2 * i + 2;
    for (uint32_t j = E; j < n && j <= D; j++) {
            if(V[j] > V[P]) P = j;
        if(P != i) {
            trocar(&V[i], &V[P]);
            heapify(V, P, n);
        }         
    }
}
void contruir_heap(int32_t* V, uint32_t n) {
    for (int32_t i = n / 2; i >= 0; i--) 
        heapify(V, i, n);
}
void ordenar(int32_t* V, uint32_t n) {
    contruir_heap(V, n);
    for (uint32_t i = n - 1; i > 0; i--) {
        trocar(&V[0], &V[i]);
        heapify(V, 0, i);
    }
}

int main() {
    const uint32_t n = 100000;
    int32_t* V = (int32_t*) malloc(n * sizeof(int32_t));
    for (uint32_t i = 0; i < n; i++) 
        V[i] = rand() * rand();
    ordenar(V, n);
    // printf("min = %i, max = %i\n", V[0], V[n-1]);
    return 0;
}