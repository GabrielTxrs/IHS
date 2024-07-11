#include <stdio.h>

int SelectionSort(int tamanho, int *vetordeint) {
	int menor, temp, comparacoes = 0;
	for(int i = 0; i < tamanho-1; i++) {
	    menor = i;
		for(int j = i+1; j < tamanho; j++) {
			if(vetordeint[j] < vetordeint[menor]) {
				menor = j;
				comparacoes++;
			}
		}
		temp = vetordeint[i];
		vetordeint[i] = vetordeint[menor];
		vetordeint[menor] = temp;
	}
	return comparacoes;
}

int bubbleSort(int tamanhoLista, int *vetordeinteiros) {
	int temporario, comparacoes = 0;
	for(int i = 0; i < tamanhoLista-1; i++) {
		for(int j = 0; j < (tamanhoLista-1)-i; j++) {
			if(vetordeinteiros[j+1] < vetordeinteiros[j]) {
				temporario = vetordeinteiros[j];
				vetordeinteiros[j] = vetordeinteiros[j+1];
				vetordeinteiros[j+1] = temporario;
                comparacoes++;
			}
		}
	}
	return comparacoes;
}

int main() {
	int vetor[12] = {4, 5, 6, 9, 2, 3, 1, 8, 7, 10};
	int originalVetor[12] = {4, 5, 6, 9, 2, 3, 1, 8, 7, 10}; 
	int ss = 0, bs = 0;

    for (int i = 0; i < 10000000; i++) {
        for (int j = 0; j < 10; j++) {
            vetor[j] = originalVetor[j];
        }

        ss += SelectionSort(10, vetor); 

        for (int j = 0; j < 10; j++) {
            vetor[j] = originalVetor[j];
        }

        bs += bubbleSort(10, vetor);
    }
	printf("SelectionSort: %d BubbleSort: %d\n", ss, bs);
	return 0;
}
