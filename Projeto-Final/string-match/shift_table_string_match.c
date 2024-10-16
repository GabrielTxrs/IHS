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

void main()
{
    char txt[] = "GCAATGCCS GCAATGCCS gabrielGACC";
    
    char padrao[] = "gabriel";
    printf("%d", HorspoolMatching(padrao, txt));
    
}