#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define trocar(i, j)\
    __asm__(\
        "mov (%0), %%eax;"\
        "mov (%1), %%ecx;"\
        "mov %%eax, (%1);"\
        "mov %%ecx, (%0);"\
        :\
        : "r"(i), "r"(j)\
        : "eax", "ecx", "memory"\
    )

void heapify(int32_t* V, uint32_t i, uint32_t n) {
    while(i < n) {
        uint32_t P = i, E = (P << 1) + 1, D = E + 1;
        if(E < n && V[E] > V[P]) P = E;
        if(D < n && V[D] > V[P]) P = D;
        if(P == i) break; 
        trocar(&V[P], &V[i]);
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
    const uint32_t n = 10000000;
    int32_t* V = (int32_t*) malloc(n * sizeof(int32_t));
    for (uint32_t i = 0; i < n; i++) 
        V[i] = rand() * rand();
    ordenar(V, n);
    printf("min = %i, max = %i\n", V[0], V[n-1]);
    return 0;
}