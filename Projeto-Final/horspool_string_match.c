#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

# define TAMANHO_ALFABETO 256
# define maior2(a, b) ((a) > (b) ? (a) : (b))


void ShiftTable(char *padrao, int tamanhoPadrao, int alfabeto[TAMANHO_ALFABETO])
{
	for(int i = 0; i < TAMANHO_ALFABETO; i++)
	{
		alfabeto[i] = tamanhoPadrao;
	}
	for(int j = 0; j < tamanhoPadrao-1; j++)
	{
		alfabeto[padrao[j]] = tamanhoPadrao-1-j;
	}
}
int HorspoolMatching(char *padrao, char *texto)
{
	int tamanhoPadrao = strlen(padrao);
	int tamanhoTexto = strlen(texto);

	int alfabeto[TAMANHO_ALFABETO];
	
	ShiftTable(padrao, tamanhoPadrao, alfabeto);

	int i = tamanhoPadrao - 1;
	int k;
	while(i <= tamanhoTexto - 1) {
		
		k = 0;
		while(k <= tamanhoPadrao-1 && padrao[tamanhoPadrao-1-k] == texto[i-k]) {
			k++;
		}
		if(k == tamanhoPadrao) {
			return i-tamanhoPadrao+1;
		}
		else {
			i += alfabeto[texto[i]];
		}	
	}
	return -1;
}

int main() {
    FILE *file = fopen("string.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *string = (char *)malloc((file_size + 1) * sizeof(char));
    if (string == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        fclose(file);
        return 1;
    }

    fread(string, sizeof(char), file_size, file);
    string[file_size] = '\0';  

    HorspoolMatching("ABCD", string);

    free(string);
    fclose(file);

    return 0;
}