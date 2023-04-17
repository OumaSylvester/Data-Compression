
/*
    Huffman Coding Algorithm.
*/
// C program for Huffman Coding
#include <stdlib.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_HEAP_SIZE 128


// A Huffman tree node
struct MinHeapNode {

    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child of this node
    struct MinHeapNode *left, *right;
};

// A Min Heap:  Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap {

    // Current size of min heap
    unsigned size;

    // capacity of min heap
    unsigned capacity;

    // Array of minheap node pointers
    struct MinHeapNode** array;
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(
        sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)

{

    struct MinHeap* minHeap
        = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHeapNode**)malloc(
        minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)

{
    /*Only used when building the min heap*/
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size
        && minHeap->array[left]->freq
               < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size
        && minHeap->array[right]->freq
               < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; //destroy the extracted node

    --minHeap->size;
    minHeapify(minHeap, 0); //rebuild the heap. Now with 1 less node

    return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap,
                   struct MinHeapNode* minHeapNode)

{
    //Inserts a new node to the heap and ensures that smallest node is at the root
    ++minHeap->size; //increment heap size
    int i = minHeap->size - 1; //index of the last node

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        /*Compares new heap frequency with the left child and the parent.
        If its less than the left child we insert a new node at index i with
        frequency equal to the left child. Then it compares with the parent of the
        left child in the next iteration till i becomes 0>>root. So the heap is organized
        during insertion. It ensures the smallest is at the root.
        */
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap)

{
    /*Build the heap using the desired order, in this case minHeap*/
    int n = minHeap->size - 1; //get the index of the last node
    int i;

    for (i = (n - 1) / 2; i >= 0; --i) //start from the parent of the node
        minHeapify(minHeap, i);
}


// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[],
                                      int freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size); //create a minHeap of size size

    for (int i = 0; i < size; ++i) //push nodes to the heap with no order at all
        minHeap->array[i] = newNode(data[i], freq[i]); //create new node and insert it to the heap array

    minHeap->size = size; //set the heap size
    buildMinHeap(minHeap); //build the heap, heapifying/reaping it to get all of its
    // nodes in order

    return minHeap; //return the mean heap. Returns a minheap with the ordered by the frequency in non decreasing order
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[],
                                     int freq[], int size)

{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity
    // equal to size.  Initially, there are
    // modes equal to size.
    struct MinHeap* minHeap
        = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1. Remember when the size becomes 1
    // the tree is build
    while (!isSizeOne(minHeap)) {
        //Create the internal nodes

        // Step 2: Extract the two minimum
        // freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3:  Create a new internal
        // node with frequency equal to the
        // sum of the two nodes frequencies.
        // Make the two extracted node as
        // left and right children of this new node.
        // Add this node to the min heap
        // '$' is a special value for internal nodes, not
        // used
        top = newNode('$', left->freq + right->freq); //new node with the frequency as sum of the left and right children

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top); //deals only with the new nodes, 2 less each time without bothering the hidden 2 nodes
        //added  to this new node.
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.
    return extractMin(minHeap); //make the last internal
    //node created to be the root node, and remove the root node
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

void getCodes(int arr[], int n, char value, char values[], char* codes[])
{
    static int index=0;
    //char code[n];//allocate memory equal  to size of char * n for code in the heap
    char *code = malloc(sizeof(char) * n);
    if(!code)
        exit(EXIT_FAILURE);
    int i;
    //build the code
    for(i=0; i<n; i++)
    {
        code[i] =  arr[i] + '0'; //change int to char

    }
    //add null character at the end of the  code. Helps during encoding to find end of code
    code[n] = '\0';
    //store code in heap in the memory allocated above
    *(values + index) = value; //add the value to values array as in in the tree
    *(codes + index) = code; //add the code to the codes array at the corresponding index as the value
   // printf("\n%i %c:%s",index, values[index], code);
    index++;
    //Research: how to return strings from functions
}

void printCodes(struct MinHeapNode* root, int arr[],
                int top, char values[], char* codes[])

{

    // Assign 0 to left edge and recur
    if (root->left) { //while left not a leaf. Data is only found at the leaf.

        arr[top] = 0;
        printCodes(root->left, arr, top + 1, values, codes);
    }

    // Assign 1 to right edge and recur
    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1, values, codes);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (isLeaf(root)) {
        //printf("%c: ", root->data);
        //printArr(arr, top);
        //char code[top]; //problem -> the size of code is known at runtime. can we use memory allocation
        getCodes(arr, top, root->data, values,codes);

    }
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size_, char values[], char *codes[])

{
    // Construct Huffman Tree
    struct MinHeapNode* root
        = buildHuffmanTree(data, freq, size_);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_HEAP_SIZE];
    int  top = 0;
    //int index = 0;
    printCodes(root, arr, top, values, codes);

}
