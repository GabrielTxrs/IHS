#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_LENGTH 4
#define MAX_PASSWORDS 238328 // 62^4 (maximum number of passwords of length 4)

char senhas[MAX_PASSWORDS][MAX_LENGTH + 1] = {0};
int numSenhas = 0;

void generate_passwords(char *senha, int current_length, int max_length) {
    if (current_length == max_length) {
        if (numSenhas < MAX_PASSWORDS) {
            strcpy(senhas[numSenhas++], senha);
        }
        return;
    }

    char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int num_chars = strlen(chars);

    for (int i = 0; i < num_chars; i++) {
        senha[current_length] = chars[i];
        senha[current_length + 1] = '\0';
        generate_passwords(senha, current_length + 1, max_length);
    }
}

void MAU_64(uint8_t *hash, const char *senha) {
    // Declarando variáveis auxiliares
    uint32_t i, n, nr = 256, s = 0;
    n = strlen(senha);
    // Geração da semente a partir da senha ( sdbm )
}

int main() {
    char senha[MAX_LENGTH + 1] = {0}; // Initialize the password array

    for (int length = 2; length < 5; length++) {
        generate_passwords(senha, 0, length);
    }
    for (int i = 0; i < numSenhas; i++) {
        printf(" %s ", senhas[i]);
    }
    // printf(" %s ", senhas[0]);
    // printf(" %s ", senhas[1]);
    // printf(" %s ", senhas[2]);
    // printf(" %s ", senhas[100]);
    // printf(" %s ", senhas[1000]);
    // printf(" %s ", senhas[2000]);
    // printf(" %s ", senhas[3000]);
    // printf(" %s ", senhas[9000]);
    // printf(" %s ", senhas[10000]);
    // printf(" %s ", senhas[MAX_PASSWORDS-1]);

    return 0;
}