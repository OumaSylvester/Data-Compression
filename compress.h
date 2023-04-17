#define ASCII_SIZE 256
#define BUF_SIZE 8


int currentBit=0; //keeps track of where in the buffer we add the code
unsigned char  bitBuf; //. Holds bits before written to disk write a byte at a time
int buffersWritten=0; //Total number of buffers written. To be added to the stats array 1

int search_values(char values[], int size_, char val)
{

	for (int i = 0; i < size_; i++)
		if (values[i] == val)
			return i;
	return -1;
}


//Utility Function to write bits to a file
void writeBinaryFile(int bit, FILE* outputFP)
{
    /*writes a byte of code(0s and 1s) to a binary file.
        Manipulates the bits in the file directly.

   */
   //If a 0 shift. If a 1  shift and OR with a 1
   bitBuf <<= 1; //fill buffer from right to left
   if(bit) //if bit is 1 perform an OR with the original byte
    bitBuf |= 0x1; //ORing(masking) with a 1 turns the bit to 1


    currentBit++;
    if(currentBit == 8)
    {
        fwrite(&bitBuf, 1, 1, outputFP);
        buffersWritten++;
        currentBit = 0;
        bitBuf = 0;
    }

}
//Utility function to add the trailing 0 s case the compressed version is not a multiple of 8
void flushBits(FILE* outputFP)
{
    while(currentBit)
        writeBinaryFile(0, outputFP); //add zeros to end of file to make it  a multiple of 8 with padded
    //0 s in case it was not
}

int encode(FILE* inputFP, FILE* outputFP, char values[], char *codes[], int size_)
{
    /*
        Algorithm encode. Reads a file, character at a time and writes its Huffman code to
        the binary output file.
    */
    char ch; //holds the character read from the file
    int total=0; //the total bits to the outputFile. To be added to the stats array 0

    char *code;
    int i; // used to get the characters from the code
    int loc=-1; //location of the character in the values array
    int bit; //a 0 or 1

    while((ch=getc(inputFP)) != EOF)
    {
        //find the location of the file in values array
        loc = search_values(values,size_, ch);
        code = codes[loc];
        i=0; //set the code iterator to 0
        while(code[i] != '\0')
        {
            //add to buffer the integer form of the character

            //printf("\n %c", code[i]);
            bit = code[i] - '0';
            writeBinaryFile(bit, outputFP);
            total++;
            i++;
        }
    }

    //return the statistics
    //stats[0] = total;
    //stats[1] = buffersWritten;
    //append  trailing 0 s in case of compressed version not being a multiple of 8
    flushBits(outputFP);
    return total;
}


void compress(char* inputFile, char* outputFile,char charArray[], int freqArray[], char values[], char* codes[], int size_, int *bits)
{
    /*Compresses a file*/
    FILE *inputFP;
    FILE *outputFP;
    FILE *uniqueFP;
    //int len = strlen(inputFile) + 11;
    //char uniqueFile[len];
    //uniqueFile = inputFile;
    //strcat(uniqueFile, "Unique.txt");



    if((inputFP = fopen(inputFile, "r")) == NULL)
    {
        printf("Error in opening %s", inputFile);
    }
    if((outputFP = fopen(outputFile, "wb")) == NULL)
    {
        printf("Error in opening %s", outputFile);
    }
    if((uniqueFP = fopen("unique.txt", "wb")) == NULL)
    {
        printf("Error in opening unique.txt");
    }


    HuffmanCodes(charArray,  freqArray, size_, values, codes);
    for(int i=0; i<size_; i++)
    {
        fprintf(uniqueFP, "%c%d", charArray[i], freqArray[i]);
    }

    *(bits) = encode(inputFP,outputFP, values, codes, size_);
    //write bits written to a file
    fclose(inputFP);
    fclose(outputFP);
}

