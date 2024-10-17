#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

# define TAMANHO_ALFABETO 256

int maior2(int a, int b) {
	return (a > b)? a : b;
}

void ShiftTable(char *str, int tamanhoPadrao, int badchar[TAMANHO_ALFABETO])
{
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
    	badchar[i] = -1;
	}
    for (int i = 0; i < tamanhoPadrao; i++) {
    	badchar[str[i]] = i;
	}
}

void BoyerMooreStringMatch(char *txt, char *padrao)
{
    int m = strlen(padrao);
    int n = strlen(txt);

    int badchar[TAMANHO_ALFABETO];

    ShiftTable(padrao, m, badchar);

    int s = 0; 
    while(s <= (n - m))
    {
        int j = m-1;

        while(j >= 0 && padrao[j] == txt[s+j]) {
        	j--;
		}

        if (j < 0)
        {
            printf("Padrao esta na posicao = %d", s);

            s += (s+m < n)? m-badchar[txt[s+m]] : 1;
        }
        else
            s += maior2(1, j - badchar[txt[s+j]]);
    }
}

int main() {
    FILE *file = fopen("string_grande.txt", "r");
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

    BoyerMooreStringMatch(string, "ABCD");

    free(string);
    fclose(file);

    return 0;
}