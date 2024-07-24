#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
void trocar(int32_t* i, int32_t* j) {
    int32_t k = *i;
    *i = *j; *j = k;
}
void ordenar(int32_t* V, uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        uint32_t min = i;
        for (uint32_t j = i; j < n; j++) {
            if(V[j] < V[min]) min = j;
            if (i != min) trocar(&V[i], &V[min]);            
        }   
    }
}
int main() {
    const uint32_t n = 100000;
    int32_t* V = (int32_t*) malloc(n * sizeof(int32_t));
    for (uint32_t i = 0; i < n; i++) 
        V[i] = rand() * rand();
    ordenar(V, n);
    printf("min = %i, max = %i\n", V[0], V[n-1]);
    return 0;
}