#include <stdio.h>
#include "esteganografia.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <imagem BMP> <arquivo de dados>\n", argv[0]);
        return 1;
    }

    const char *bmp_filename = argv[1];
    const char *data_filename = argv[2];

    // Exemplo de chamada para incorporar dados
    embed_data(bmp_filename, data_filename);

    // Exemplo de chamada para extrair dados
    extract_data(bmp_filename, "output.txt");

    return 0;
}
