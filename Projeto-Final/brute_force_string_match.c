#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

void patternSearching(char *string, char *pattern) {
    for (int i = 0; i < strlen(string); i++)
    {
        int count = 0;
        if (i + strlen(pattern) <= strlen(string))
        {
            for (int j = 0; j < strlen(pattern); j++)
            {
                if (string[i+j] == pattern[j])
                {
                    count++;
                }
            }
        }
        
        if (count == strlen(pattern))
        {
            printf("Encontra-se na posição: %d\n", i);
        }   
    }
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

    patternSearching(string, "ABCD");

    free(string);
    fclose(file);

    return 0;
}