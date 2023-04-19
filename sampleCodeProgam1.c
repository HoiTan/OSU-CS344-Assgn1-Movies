// from ED #27
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char** strings;
} node;

int main(int argc, char* argv[])
{
    node myNode; // Sample struct
    FILE* myDataFile = NULL; // Handle for the .csv file
    char* readBuffer = NULL; // Will store a line from the file, allocated on heap
    size_t len = 0; // ignored by getline, but required
    int i = 0; // Looping var

    myDataFile = fopen("./my.csv", "r"); // Open up the data file

    if (myDataFile == NULL) { printf("fopen() failed\n"); return -1; } // Error check fopen()

    while(getline(&readBuffer, &len, myDataFile) != -1) // Read the file line by line
    {
        printf("%s", readBuffer); // Display the line
        memset(readBuffer, '\0', sizeof(readBuffer)); // Clear the reading buffer
    }

    free(readBuffer); // Free the reading buffer
    fclose(myDataFile); // Close the data file

    myNode.strings = malloc(5 * sizeof(char*)); // Allocate space for 5 pointers to strings

    // Allocate the space for each string
    for (i = 0; i < 5; i++)
        myNode.strings[i] = malloc(21 * sizeof(char)); 

    // Show the fruits of our labors
    sprintf(myNode.strings[0], "FIRSTSTRING");
    printf("First string contents: '%s'\n", myNode.strings[0]);
    printf("Third character from first string: '%c'\n", myNode.strings[0][2]);

    // Free all the space allocated for strings
    for (i = 0; i < 5; i++)
        free(myNode.strings[i]);

    free(myNode.strings);

    return 0;
}