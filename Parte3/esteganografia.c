#include <stdio.h>
#include <stdlib.h>
#include "esteganografia.h"

void read_bmp(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    // Código para ler a imagem BMP
    fclose(f);
}

void write_bmp(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    // Código para escrever a imagem BMP
    fclose(f);
}

void embed_data(const char *bmp_filename, const char *data_filename) {
    FILE *bmp_file = fopen(bmp_filename, "rb+");
    FILE *data_file = fopen(data_filename, "rb");
    if (!bmp_file || !data_file) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    // Pular o cabeçalho BMP (54 bytes)
    fseek(bmp_file, 54, SEEK_SET);

    int ch;
    while ((ch = fgetc(data_file)) != EOF) {
        for (int i = 0; i < 8; i++) {
            int bmp_byte = fgetc(bmp_file);
            if (bmp_byte == EOF) {
                printf("Erro: A imagem BMP é muito pequena para acomodar os dados.\n");
                fclose(bmp_file);
                fclose(data_file);
                return;
            }
            bmp_byte = (bmp_byte & 0xFE) | ((ch >> (7 - i)) & 0x01);
            fseek(bmp_file, -1, SEEK_CUR);
            fputc(bmp_byte, bmp_file);
        }
    }

    fclose(bmp_file);
    fclose(data_file);
}

void extract_data(const char *bmp_filename, const char *output_filename) {
    FILE *bmp_file = fopen(bmp_filename, "rb");
    FILE *output_file = fopen(output_filename, "wb");
    if (!bmp_file || !output_file) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    // Pular o cabeçalho BMP (54 bytes)
    fseek(bmp_file, 54, SEEK_SET);

    int ch;
    while (1) {
        ch = 0;
        for (int i = 0; i < 8; i++) {
            int bmp_byte = fgetc(bmp_file);
            if (bmp_byte == EOF) {
                printf("Erro: Falha ao ler a imagem BMP.\n");
                fclose(bmp_file);
                fclose(output_file);
                return;
            }
            ch |= ((bmp_byte & 0x01) << (7 - i));
        }
        if (ch == 0) break; // Assumimos que o final dos dados está marcado por um byte zero
        fputc(ch, output_file);
    }

    fclose(bmp_file);
    fclose(output_file);
}
