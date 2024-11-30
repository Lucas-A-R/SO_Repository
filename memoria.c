#include <stdio.h>
#include <stdbool.h>

#define TAMANHO_MEMORIA 1024 // Definindo o tamanho do array de memória

char memoria[TAMANHO_MEMORIA]; // Array global representando a memória
bool alocado[TAMANHO_MEMORIA]; // Array para manter o controle de quais blocos estão alocados

void* aloca(size_t tamanho) {
    for (int i = 0; i < TAMANHO_MEMORIA - tamanho; i++) {
        bool espaco_livre = true;
        for (int j = 0; j < tamanho; j++) {
            if (alocado[i + j]) {
                espaco_livre = false;
                break;
            }
        }
        if (espaco_livre) {
            for (int j = 0; j < tamanho; j++) {
                alocado[i + j] = true;
            }
            return &memoria[i];
        }
    }
    return NULL; // Memória insuficiente
}

void desaloca(void* ponteiro, size_t tamanho) {
    int indice = (char*)ponteiro - memoria;
    for (int i = 0; i < tamanho; i++) {
        alocado[indice + i] = false;
    }
}

int main() {
    // Exemplo de uso das funções aloca e desaloca
    char* bloco1 = (char*)aloca(10);
    if (bloco1 != NULL) {
        printf("Bloco de 10 bytes alocado.\n");
    } else {
        printf("Falha ao alocar bloco de 10 bytes.\n");
    }

    desaloca(bloco1, 10);
    printf("Bloco de 10 bytes desalocado.\n");

    return 0;
}
