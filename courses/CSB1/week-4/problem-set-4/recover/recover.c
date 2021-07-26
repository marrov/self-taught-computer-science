#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

// Number of bytes in a memory block
const int BLOCK_SIZE = 512;

// Prototypes
bool is_jepg(BYTE *buffer);

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
    BYTE buffer[BLOCK_SIZE];

    // TEMPORARY
    int count = 0;

    // Read to buffer until the end of card
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if (is_jepg(buffer))
        {
            printf("Number of blocks: %i\n", count);
            printf("Jepg block!\n");
            count = 0;
        }
        else
        {
            count++;
        }
    }

    // Close files and free memory
    fclose(input);
}

bool is_jepg(BYTE *buffer)
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0);
}
