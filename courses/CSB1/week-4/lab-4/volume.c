// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Get factor as float from string input
    float factor = atof(argv[3]);

    //Copy header from input file to output file

    // Initialize header
    uint8_t header[HEADER_SIZE];

    // Reader header from input
    // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    // This function reads data from a file that has been opened via fopen. It expects as input:
    //  ptr, which is the address (of the first byte) of memory into which to read the data,
    //  size, which is the size (in bytes) of the type of data to read,
    //  nmemb, which is the number of those types to read at once, and
    //  stream, which is the pointer to a FILE returned by fopen.
    //For instance, if reading one char at a time, size would be sizeof(char) (i.e., 1), and nmemb would be 1.

    // Write heeader to output
    // size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream);
    // This function writes data to a file that has been opened via fopen. It expects as input:
    //  ptr, which is the address (of the first byte) of memory from which to read the data,
    //  size, which is the size (in bytes) of the type of data to write,
    //  nmemb, which is the number of those types to write at once, and
    //  stream, which is the pointer to a FILE returned by fopen.
    // For instance, if writing one char at a time, size would be sizeof(char) (i.e., 1), and nmemb would be 1.

    //Read samples from input file and write updated data to output file
    int16_t buffer;

    // Close files
    fclose(input);
    fclose(output);
}
