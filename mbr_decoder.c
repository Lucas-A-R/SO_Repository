#include <stdio.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t boot_indicator; // 0x80 - bootable, 0x00 - non-bootable
    uint8_t start_head;
    uint8_t start_sector;
    uint8_t start_cylinder;
    uint8_t partition_type;
    uint8_t end_head;
    uint8_t end_sector;
    uint8_t end_cylinder;
    uint32_t start_lba;     // Start of partition in LBA
    uint32_t size_in_sectors; // Size of partition in sectors
} PartitionEntry;
#pragma pack(pop)

typedef struct {
    uint8_t boot_code[446];
    PartitionEntry partition_table[4];
    uint16_t signature; // Should be 0xAA55
} MBR;

void print_partition_table(PartitionEntry* pt) {
    for (int i = 0; i < 4; i++) {
        printf("Partição %d:\n", i + 1);
        printf("  Status: 0x%02X\n", pt[i].boot_indicator);
        printf("  Tipo de Partição: 0x%02X\n", pt[i].partition_type);
        printf("  Início (LBA): %u\n", pt[i].start_lba);
        printf("  Tamanho (setores): %u\n\n", pt[i].size_in_sectors);
    }
}

int main() {
    FILE *file = fopen("mbr.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, file);
    fclose(file);

    if (mbr.signature != 0xAA55) {
        printf("Assinatura inválida: 0x%X\n", mbr.signature);
        return 1;
    }

    print_partition_table(mbr.partition_table);

    return 0;
}
