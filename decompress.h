int search_codes(char *codes[], int size_, char *code)
{
    int cmp;
	for (int i = 0; i < size_; i++)
    {
        cmp = strcmp(code, codes[i]);
        if (cmp == 0) //if the code matches a value in the  codes array
			return i;
    }

	return -1;
}

void writeByte(FILE *outputFP, char ch)
{
    fwrite(&ch, 1, 1, outputFP);
    //fprintf(outputFP, "%c", ch);
}

void decompress(char* inputFile, char* outputFile, char charArray[], int freqArray[], char values[], char* codes[], int size_, int *bits)
{
    /*
    Open unique file
    get the unique character and frequency
    Build the tree and fill the codes
    Open input file in binary
    Decompress the input file
    */
    //Local Definitions
    FILE* inputFP, *outputFP;
    unsigned char ch; //holds character from file
    int i, j;
    int bit;
   // unsigned char byte; //holds character during manipulation
    int bitCounter;
    char code[ASCII_SIZE];
    unsigned int MASK = 128; //start at MSB
    int loc;//index of the found code

    if((inputFP = fopen(inputFile, "rb")) == NULL)
    {
        printf("Error in opening file %s", inputFile);
    }
    if((outputFP = fopen(outputFile, "w")) == NULL)
    {
        printf("Error in opening the file %s", outputFile);
    }
    i=0; //keeps track of the current bit the file. Don't exeeed valid bits. Avoid trailing bits
    j=0;
    printf("\n%d", *bits);
    while(true)
    {
        ch = getc(inputFP);
        bitCounter=0;
        MASK = 128;
        //process 1 byte at a time
        while(bitCounter < 8 && i<=*bits)
        {
            bit = ch & MASK; //get the current bit
            printf("\n%c\t%d", ch, bitCounter);
            MASK = MASK >> 1;//right shift mask by 1. Turn  next bit on
            if(bit)//bit was 1
            {
                printf("\nBit1: %d", bit);
                code[j] = 1 + '0';

            }

            else //bit was 0
            {
                printf("\nBit0: %d", bit);
                code[j] = 0 +  '0'; //append the null character to code
            }

            code[j+1] = '\0';
            loc = search_codes(codes, size_, code); //search the codes array for the current code
            printf("\nLocation: %d", loc);
            printf("\n%di", i);
            i++; //increment bits already handled
            bitCounter++; //decrement
            if(loc > -1)
            {
                writeByte(outputFP, values[loc]); //write the corresponding character to file
                j=0; //reset j
            }
            else
            {
                j++;
            }


        }//exit inner while
        if(i>*bits)
            break;

    }
    fclose(inputFP);
    fclose(outputFP);
}

