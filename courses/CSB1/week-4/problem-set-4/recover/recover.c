#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

// Number of bytes in .wav header
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: recover input.raw\n");
        return 1;
    }

    // Open memory card
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Initialize buffer
    BYTE buffer[BLOCK_SIZE]

    // Read to buffer until the end of card
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
    }

    // Close files and free memory
    fclose(input);
}