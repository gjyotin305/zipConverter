#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define CHUNK_SIZE 16384

int main()
{
    const char *zip_file = "compressed_lvl1.zip";
    const char *file_output = "inflated_file.png";

    gzFile zip_fp = gzopen(zip_file, "rb"); // gzopen opens the file in Read Binary form, gz
    if (!zip_fp)
    {
        perror("Error in opening the zip file.\n");
        return 1;
    }
    FILE *output_fp = fopen(file_output, "wb"); // fopen represents output file here wb is write binary
    if (!output_fp)
    {
        perror("Error in creating the output file.\n");
        gzclose(zip_fp);
        return 1;
    } // gives error message if it is not output file

    unsigned char input_buffer[CHUNK_SIZE];
    unsigned char output_buffer[CHUNK_SIZE]; // buffers are defined to hold the chunks of data

    z_stream stream;                  // zstream is structure to hold info and state for inflation process
    memset(&stream, 0, sizeof(char)); // memset ensures all members are set to zero
    inflateInit(&stream);             // initialize the inflated state

    int ret;
    do
    {
        stream.avail_in = gzread(zip_fp, input_buffer, CHUNK_SIZE);
        if (stream.avail_in == 0)
        {
            if (gzeof(zip_fp))
            {
                break; // End of input file
            }
            else
            {
                perror("Error in reading the zip file.\n");
                inflateEnd(&stream);
                gzclose(zip_fp);
                fclose(output_fp);
                return 1;
            }
        }
        stream.next_in = input_buffer;
        do // do while is used to read the data in chunks and inflate it till the end is reached
        {
            stream.avail_out = CHUNK_SIZE;
            stream.next_out = output_buffer;
            ret = inflate(&stream, Z_NO_FLUSH);
            if (ret == Z_STREAM_ERROR)
            {
                perror("Inflate Error");
                inflateEnd(&stream);
                gzclose(zip_fp);
                fclose(output_fp);
                return 1;
            }
            unsigned int uncompressed_size = CHUNK_SIZE - stream.avail_out;
            if (fwrite(output_buffer, 1, uncompressed_size, output_fp) != uncompressed_size)
            {
                perror("Error in writing the output file.\n");
                inflateEnd(&stream);
                gzclose(zip_fp);
                fclose(output_fp);
                return 1;
            }

        } while (stream.avail_out == 0);

    } while (ret != Z_STREAM_END);

    inflateEnd(&stream);
    gzclose(zip_fp);
    fclose(output_fp);

    printf("File %s is inflated to %s.\n", zip_file, file_output);

    return 0;
}