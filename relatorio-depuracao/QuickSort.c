#include <stdio.h>

void trocar(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int lomutoPartition(int inicio, int fim, int *vetor) {
	int pivot = vetor[inicio];
	int mediana = inicio;// indice do ultimo elemento do primeiro segmento
	for(int i = inicio + 1; i < fim; i++) {
		if(vetor[i] < pivot) {
			mediana++;
			trocar(&vetor[mediana],&vetor[i]);
		}
	}
	trocar(&vetor[inicio],&vetor[mediana]);
	return mediana;
}

void QuickSort(int inicio, int fim, int *vetor) {
	int particao;
	if(inicio < fim) {
		particao = lomutoPartition(inicio, fim, vetor);
		QuickSort(inicio, particao, vetor);
		QuickSort(particao+1, fim, vetor);
	}
}

int main() {
	int vetor[12] = {4, 5, 6, 9, 2, 3, 1, 8, 7, 10};

	for(int i = 0 ; i < 10 ;i++) {
		printf("%d ", vetor[i]);
	}
	printf("\n");
	QuickSort(0, 10, vetor);
	for(int i = 0 ; i < 10 ;i++) {
		printf("%d ", vetor[i]);
	}
	printf("\n");
	return 0;
}