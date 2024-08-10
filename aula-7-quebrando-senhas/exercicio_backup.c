#include <stdint.h>
#include <stdio.h>
// Macro rand8
#define rand8 ((rand() >> 8) & 0b111)
// Função de hash MAU -64
void MAU_64(uint8_t *hash, const char *senha)
{
    // Declarando variáveis auxiliares
    uint32_t i, n = strlen(senha), nr = 256, s = 0;
    // Geração da semente a partir da senha ( sdbm )
    for (i = 0; i < n; i++)
        s = senha[i] + (s << 6) + (s << 16) - s;
    // Semente dos números pseudo - aleatórios
    srand(s);
    // Executando rodadas sobre os bytes do hash
    for (i = 0; i < nr; i++)
        hash[(rand8)] = hash[rand8] ^ rand();
}

int main(int argc, char ** argv){
    uint8_t hash[8];
    MAU_64(hash,argv[1]);
    for(int i=0;i<=7;i++){
        printf("%02x", hash[i]);
    }
    printf("\n");
    return 0;

}