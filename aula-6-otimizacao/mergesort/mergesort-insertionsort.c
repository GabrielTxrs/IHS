#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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
void insertionSort(int32_t E[], int32_t first, int32_t last) {
	if ((last - first) < 1) { return; }
	for (int32_t i = (first + 1); i <= last; i++) {
		for (int32_t j = i; j > first; j--) {
			if (E[j] < E[j - 1]) {
                 trocar(&E[j], &E[j - 1]); 
            }
            break;
		}
	}
}

void merge(int32_t E[], int32_t first, int32_t mid, int32_t last) {
	if ((last - first) < 1) { return; }
	int32_t *left, *right;
	left = malloc((mid - first + 1) * sizeof(int32_t)); 
    memcpy(&left[0], &E[first], (mid - first + 1) * sizeof(int32_t));
	right = malloc((last - mid) * sizeof(int32_t)); 
    memcpy(&right[0], &E[mid + 1], (last - mid) * sizeof(int32_t));

	int32_t compare, index = first, indexLeft = 0, indexRight = 0;
	while (indexLeft < (mid - first + 1) && indexRight < (last - mid)) {
		compare = right[indexRight] - left[indexLeft];
		if (compare > 0) { E[index++] = left[indexLeft++]; } 
		else if (compare < 0) { E[index++] = right[indexRight++]; } 
		else { E[index++] = left[indexLeft++]; E[index++] = right[indexRight++]; } 
	}
	while (indexLeft < (mid - first + 1)) { E[index++] = left[indexLeft++]; }
	while (indexRight < (last - mid)) { E[index++] = right[indexRight++]; }
	free(left); 
    free(right);
}
void mersertionSort(int32_t E[], int32_t first, int32_t last, int32_t S) {
	if (last - first > S) {
		int32_t mid = (first + last) / 2;
		mersertionSort(E, first, mid, S);
		mersertionSort(E, mid + 1, last, S);
		merge(E, first, mid, last);
	}
	else {
		insertionSort(E, first, last);
	}
}

int main() {
    const uint32_t n = 10000000;
    int32_t* V = (int32_t*) malloc(n * sizeof(int32_t));
    for (uint32_t i = 0; i < n; i++)
        V[i] = rand() * rand();
    mersertionSort(V, 0, n - 1, 5);
    printf("min = %i, max = %i\n", V[0], V[n-1]);
    free(V);
    return 0;
}