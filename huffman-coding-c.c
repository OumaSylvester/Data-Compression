#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#include "huffman-coding-c.h"
#include "char_freq.h"
#include "compress.h"
#include "decompress.h"


// Driver code
int main(int argc, char* argv[])
{
    /*Depending on the command line option, it calls compress or decompress
        program_name -c inputFile outputFile to compress
        program_name -d inputFile outputFile to decompress

    */
    //Research-Processing command line options
    if(argc != 3)
    {
        puts("Unexpected number of arguments.");
        printf("Usage: program_name inputFile.ext outputFile.ext");
        exit(EXIT_FAILURE);
    }

    int size_;
    char charArray[ASCII_SIZE];
    int freqArray[ASCII_SIZE] = {0};
    frequency(argv[1], charArray, freqArray, &size_);

    char values[size_];
    char *codes[size_];

    int bits = 0; //total bits written to a file
    //Process Compression

    compress(argv[1], argv[2],charArray, freqArray,  values, codes, size_ , &bits);
    //% compressed
    /*
    long int inputFileSize, outputFileSize, diff;
    float saved;
    inputFileSize = calcFilesize(argv[1]) * 8;
    outputFileSize = calcFilesize(argv[2]) * 8;
    diff = inputFileSize - outputFileSize;
    saved = (diff/inputFileSize) * 100;


    printf("\nOriginal file size in bits: %ld", inputFileSize);
    printf("\nCompress file size in bits: %ld", outputFileSize);
    printf("\nSpace saved: %d", diff);
    //printf("\nPercentage saved: %.2f", saved);

    //Process Decompression if -d
    */
    //decompress("test-pdf.oom", "test-pdf-2.pdf", charArray, freqArray, values, codes, size_, &bits);

    return 0;
}

