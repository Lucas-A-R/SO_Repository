#ifndef ESTEGANOGRAFIA_H
#define ESTEGANOGRAFIA_H

void read_bmp(const char *filename);
void write_bmp(const char *filename);
void embed_data(const char *bmp_filename, const char *data_filename);
void extract_data(const char *bmp_filename, const char *output_filename);

#endif
