#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<zlib.h>

#define CHUNK_SIZE 16384

int main () {
    const char * file_input = "filename.txt";
    const char * zip_file = "compressedboi.zip";

    FILE *input_fp = fopen(file_input,"rb");
    if(!input_fp){
        perror("Error in opening the file.\n");
        return 1;
    }
    gzFile zip_fp = gzopen(zip_file,"wb");
    if(!zip_fp){
        perror("Error in creating the zip file.\n");
        return 1;
    }

    unsigned char input_buffer[CHUNK_SIZE]; 
    unsigned char output_buffer[CHUNK_SIZE]; 

    z_stream stream;
    memset(&stream,0,sizeof(char));
    deflateInit(&stream, 8);

    int ret;
    do{
        stream.avail_in = fread(input_buffer,1,CHUNK_SIZE,input_fp);
        if(ferror(input_fp)){
            perror("Error in opening input file.\n");
            deflateEnd(&stream);
            gzclose(zip_fp);
            fclose(input_fp);
            return 1;
        }
        stream.next_in = input_buffer;
        do{
            stream.avail_out = CHUNK_SIZE;
            stream.next_out = output_buffer;
            ret = deflate(&stream,feof(input_fp) ? Z_FINISH : Z_NO_FLUSH );
            if(ret == Z_STREAM_ERROR){
                perror("Deflate Error");
                deflateEnd(&stream);
                gzclose(zip_fp);
                fclose(input_fp);
                return 1;
            }
            unsigned int compressed_size = CHUNK_SIZE - stream.avail_out;
            if(gzwrite(zip_fp,output_buffer,compressed_size) != compressed_size){
                perror("Error in Creating Zip file\n");
                deflateEnd(&stream);
                gzclose(zip_fp);
                fclose(input_fp);
                return 1;
            }


        }while(stream.avail_out==0);
        
    }while(ret != Z_STREAM_END);

    deflateEnd(&stream);
    gzclose(zip_fp);
    fclose(input_fp);

    printf("File %s is compressed in %s.\n",file_input,zip_file);

    return 0;
}