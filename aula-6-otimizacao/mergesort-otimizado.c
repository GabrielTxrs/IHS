#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h>
#define swapExample(i, j)\
    __asm__(\
        "mov (%0), %%eax;"\
        "mov (%1), %%ecx;"\
        "mov %%eax, (%1);"\
        "mov %%ecx, (%0);"\
        :\
        : "r"(i), "r"(j)\
        : "eax", "ecx", "memory"\
    )
#define IreceiveJ(i, j)\
    __asm__(\
        "mov (%1), %%eax;"\
        "mov %%eax, (%0);"\
        :\
        : "r"(i), "r"(j)\
        : "eax", "memory"\
    )

void merge(int32_t* arr, int32_t low, int32_t mid, uint32_t high) { 
	uint32_t i = low, j = mid + 1, k = 0; 
	uint32_t* temp = (uint32_t*)calloc(high - low + 1, sizeof(uint32_t)); 
	while ((i <= mid) && (j <= high)) 
		if (arr[i] < arr[j]) 
			IreceiveJ(&temp[k++], &arr[i++]); // IreceiveJ(&arr[i++], &temp[k++]);
		else
			IreceiveJ(&temp[k++], &arr[j++]); // IreceiveJ(&arr[i++], &temp[j++]);
	while (j <= high) 
		IreceiveJ(&temp[k++], &arr[j++]); // IreceiveJ(&arr[i++], &temp[k++]);
	while (i <= mid) 
		IreceiveJ(&temp[k++], &arr[i++]); // IreceiveJ(&arr[i++], &temp[k++]);

	for (i = low, k = 0; i <= high; i++, k++) 
		IreceiveJ(&arr[i], &temp[k]); // IreceiveJ(&temp[k], &arr[i]);
	free(temp); 
} 
void mergesort(int32_t* arr, int32_t low, int32_t high) { 
	if (low < high) { 
		int32_t mid = (low + high) / 2; 
		mergesort(arr, low, mid); 
		mergesort(arr, mid + 1, high); 

		if (arr[mid] > arr[mid + 1]) 
			merge(arr, low, mid, high); 
	} 
} 
int main() {
    const uint32_t n = 10000000;
    int32_t* V = (int32_t*) malloc(n * sizeof(int32_t));
    for (uint32_t i = 0; i < n; i++) 
        V[i] = rand() * rand();
    mergesort(V, 0, n - 1);
    printf("min = %i, max = %i\n", V[0], V[n-1]);
    free(V);
    return 0;
}