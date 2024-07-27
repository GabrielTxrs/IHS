#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h>

void merge(int32_t* arr, int32_t low, int32_t mid, uint32_t high) { 
	uint32_t i = low, j = mid + 1, k = 0; 
	uint32_t* temp = (uint32_t*)calloc(high - low + 1, sizeof(uint32_t)); 
	while ((i <= mid) && (j <= high)) 
		if (arr[i] < arr[j]) 
			temp[k++] = arr[i++]; 
		else
			temp[k++] = arr[j++]; 
	while (j <= high) 
		temp[k++] = arr[j++];
	while (i <= mid) 
		temp[k++] = arr[i++]; 

	for (i = low, k = 0; i <= high; i++, k++) 
		arr[i] = temp[k];
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