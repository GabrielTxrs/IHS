/* C Program for Bad Character Heuristic of Boyer
   Moore String Matching Algorithm */

# include <string.h>
# include <stdio.h>

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

void main()
{
    char txt[] = "GCAATGCCTATGTGACC";
    char padrao[] = "TATGTG";
    BoyerMooreStringMatch(txt, padrao);

}