# zipConverter
# CSL1010: Course Project

## Team Members: 
* Jyotin Goel
* Jadhav Avadhut Maruti 
* Keshika Sharma 
* Kamal 
* Pragyanidhi

## Algorithm used 
   We are using the standard algorithm used for the .zip format that is the Deflate algorithm which comprises of Huffman coding and L277 encoding to compress the file


## How to download our repository:

`git clone https://github.com/gjyotin305/zipConverter.git`
`cd zipConverter/`
`gcc deflate.c -o deflate -lz`
`./deflate`
This will make the zip file in your current directory to retrieve it run 
`gcc inflateCompression.c -o inflateCompression -lz`
`./inflateCompression`
This will generate a inflated_file in your working directory.





