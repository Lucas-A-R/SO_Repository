#include <stdio.h>
#include <stdbool.h>

#define TAMANHO_MEMORIA 1024 // Definindo o tamanho do array de memória

char memoria[TAMANHO_MEMORIA]; // Array global representando a memória
bool alocado[TAMANHO_MEMORIA]; // Array para manter o controle de quais blocos estão alocados

// Função para alocar memória
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

// Função para desalocar memória
void desaloca(void* ponteiro, size_t tamanho) {
    int indice = (char*)ponteiro - memoria;
    for (int i = 0; i < tamanho; i++) {
        alocado[indice + i] = false;
    }
    // Mesclar blocos livres adjacentes
    for (int i = 0; i < TAMANHO_MEMORIA; i++) {
        if (!alocado[i]) {
            int j = i;
            while (j < TAMANHO_MEMORIA && !alocado[j]) {
                j++;
            }
            // i é o início do bloco livre e j é o fim (não inclusivo)
            int tamanho_livre = j - i;
            for (int k = 0; k < tamanho_livre; k++) {
                alocado[i + k] = false;
            }
            i = j - 1; // Continuar da próxima posição livre
        }
    }
}

int main() {
    // Inicializar a memória como livre
    for (int i = 0; i < TAMANHO_MEMORIA; i++) {
        alocado[i] = false;
    }

    // Exemplo de uso das funções aloca e desaloca
    char* bloco1 = (char*)aloca(10);
    if (bloco1 != NULL) {
        printf("Bloco de 10 bytes alocado.\n");
    } else {
        printf("Falha ao alocar bloco de 10 bytes.\n");
    }

    desaloca(bloco1, 10);
    printf("Bloco de 10 bytes desalocado.\n");

    // Testes adicionais
    char* bloco2 = (char*)aloca(50);
    char* bloco3 = (char*)aloca(20);
    desaloca(bloco2, 50);
    desaloca(bloco3, 20);

    return 0;
}
