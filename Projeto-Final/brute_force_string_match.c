#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char** argv){

    FILE *file = fopen("string.txt", "r");
    char *string;
    long file_size;

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Movendo o cursor para o final do arquivo para determinar o tamanho
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    // Alocando memória dinamicamente para armazenar a string
    string = (char *)malloc((file_size + 1) * sizeof(char));  // +1 para o caractere null-terminador
    if (string == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        fclose(file);
        return 1;
    }

    // Lendo o conteúdo do arquivo no buffer
    fread(string, sizeof(char), file_size, file);
    string[file_size] = '\0';  // Adicionando o null-terminador

    patternSearching(string, "ABCD");

    // Liberando a memória e fechando o arquivo
    free(string);
    fclose(file);

    return 0;
}