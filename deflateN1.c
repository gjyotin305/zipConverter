#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 16384

typedef struct {
    unsigned int length;
    unsigned int distance;
    unsigned char symbol;
} Match;

void compressDeflate(const unsigned char* input, size_t inputSize, unsigned char* output, size_t* outputSize) {
    // Your implementation of deflate compression goes here
    // This is just a placeholder to demonstrate the basic logic

    // Copy the input data as is to the output (no compression)
    memcpy(output, input, inputSize);
    *outputSize = inputSize;
}

int main() {
    const char *file_input = "filename.txt";
    const char *zip_file = "compressed_try1.zip";

    FILE *input_fp = fopen(file_input, "rb");
    if (!input_fp) {
        perror("Error in opening the input file.\n");
        return 1;
    }

    fseek(input_fp, 0, SEEK_END);
    long inputSize = ftell(input_fp);
    fseek(input_fp, 0, SEEK_SET);

    unsigned char *input_buffer = (unsigned char *)malloc(inputSize);
    fread(input_buffer, 1, inputSize, input_fp);
    fclose(input_fp);

    unsigned char *output_buffer = (unsigned char *)malloc(inputSize); // Assuming compressed size won't exceed input size
    size_t outputSize;

    compressDeflate(input_buffer, inputSize, output_buffer, &outputSize);

    FILE *output_fp = fopen(zip_file, "wb");
    if (!output_fp) {
        perror("Error in creating the output file.\n");
        free(input_buffer);
        free(output_buffer);
        return 1;
    }

    fwrite(output_buffer, 1, outputSize, output_fp);
    fclose(output_fp);

    free(input_buffer);
    free(output_buffer);

    printf("File %s is compressed in %s.\n", file_input, zip_file);

    return 0;
}