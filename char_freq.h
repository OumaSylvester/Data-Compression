long int calcFilesize(char* inputFile);
void readInputFile(char* inputFile, char fileContents[]);
void frequency(char* inputFile, char charArray[], int freqArray[], int *size_);

long int calcFilesize(char* inputFile)
{
    long int FILE_SIZE;
     //find file size
    FILE* fp;
    if((fp = fopen(inputFile, "r")) == NULL)
    {
        printf("Error in opening %s", inputFile);
    }
    fseek(fp, 0L, SEEK_END); //seek to end of the file
    FILE_SIZE = ftell(fp); //get size of the file

    fseek(fp, 0L, SEEK_SET); //reset file position
    fclose(fp);
    return FILE_SIZE;
}

void readInputFile(char* inputFile, char fileContents[])
{
    /*Reads content of Input file and stores them as char literals in the fileContents array
        It edits the fileContents array
    */
    int i=0;
    char ch;

    FILE* fp;
    if((fp = fopen(inputFile, "r")) == NULL)
    {
        printf("Error in opening %s", inputFile);
    }



    while((ch=getc(fp)) != EOF)
    {
        *(fileContents + i) = ch; //feel the array with the file contents
        i++;
    }
    fclose(fp);

}

void frequency(char* inputFile, char charArray[], int freqArray[], int *size_)
{
    /*Algorithm frequency: Finds unique characters and their frequency  in the fileContentsArray.
        Returns number of unique characters found in the fileContents
    */

    //Local definitions

    int i, j; //i is the index of the fileContents and j the index of charArray and freqArray.
    long int fileSize;
    int counter=0; //keeps track of unique of characters already added
    bool found=false; //condition if character is already in the charArray


    fileSize = calcFilesize(inputFile);
    //printf("%ld\n", fileSize); //check number of unique characters
    char fileContents[fileSize];
    readInputFile(inputFile, fileContents); //fill the fileContents Array

    for(i=0; i<fileSize; i++) //loop only for fields with valid data
    {
        //Loop to handle duplicates
        for(j=0; j<counter; j++) //will fail the first time because j won't be lees than 0
        {
            if(fileContents[i] == charArray[j])
            {
                //character already in the charArray
                *(freqArray + j) += 1; //increment character count
                found = true;
                break; //will break loop of j only
            }
            else{
                found = false; //resets found
            }
        }
        //add to charArray if does not exits in the array
        if(!found){ //character not in array. Avoid adding duplicates
            *(charArray + counter) = fileContents[i];
            *(freqArray + counter)+= 1;
            counter++;
        }
    }

    *(size_) = counter; //get the size of the unique characters
   // return counter;

    /*
        Refactoring: Avoid using fileContents array
            Use binarySearch to find duplicates
    */
}

