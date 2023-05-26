#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>

#define CHUNK_SIZE 16384
#define Z_LIB_VERSION "1.2.13"

int main()
{
    char *file_input = "filename.txt";
    char *compressed_file = "compressed_lvl1.zip";

    FILE *fp = fopen(file_input, "rb");
    if (fp == NULL)
    {
        perror("Error Input File is not opening");
        return 1;
    }
    gzFile compzip = gzopen(compressed_file, "wb");
    if (compzip == NULL)
    {
        perror("Error in making compressed file");
        return 1;
    }

    unsigned char input_buffer[CHUNK_SIZE];
    unsigned char output_buffer[CHUNK_SIZE];

    z_stream stream1;
    memset(&stream1, 0, sizeof(char)); // Initialsing z_stream data structure as told in documentation
    deflateInit(&stream1, 9);
    int ret;
    do
    {
        stream1.avail_in = fread(input_buffer, 1, CHUNK_SIZE, fp);
        if (ferror(fp))
        {
            perror("Error in opening input File");
            deflateEnd(&stream1);
            gzclose(compzip);
            fclose(fp);
            return 1;
        }
        stream1.next_in = input_buffer;
        do
        {
            stream1.avail_out = CHUNK_SIZE;
            stream1.next_out = output_buffer;
            ret = deflate(&stream1, feof(fp) ? Z_FINISH : Z_NO_FLUSH);
            if (ret == Z_STREAM_ERROR)
            {
                perror("Deflate Error");
                deflateEnd(&stream1);
                gzclose(compzip);
                fclose(fp);
                return 1;
            }
            unsigned int compressed_size = CHUNK_SIZE - stream1.avail_out;
            if (gzwrite(compzip, output_buffer, compressed_size) != compressed_size)
            {
                perror("Error in writing to Zip file");
                deflateEnd(&stream1);
                gzclose(compzip);
                fclose(fp);
                return 1;
            }

        } while (stream1.avail_out == 0);
    } while (ret != Z_STREAM_END);

    deflateEnd(&stream1);
    gzclose(compzip);
    fclose(fp);
    printf("\nThannks");

    return 0;
}