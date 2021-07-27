#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

// Number of bytes in a memory block
const int BLOCK_SIZE = 512;

// Number of chars in jpg image name
const int NAME_SIZE = 8;

// Prototypes
bool is_jpg(BYTE *buffer);

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
        printf("Could not open input file.\n");
        return 1;
    }

    // Initialize buffer and output image file
    BYTE buffer[BLOCK_SIZE];
    FILE *output;

    // Variable that keeps track of the number of JPGs found
    int jpg_count = 0;

    // Allocate enough memory for a string that stores the JPG image name
    char *filename = malloc(NAME_SIZE);
    if (filename == NULL)
    {
        return 1;
    }

    // Read to buffer until the end of card
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if (is_jpg(buffer))
        {
            if (jpg_count == 0)
            {
                // Create an adequate file name
                sprintf(filename, "%03i.jpg", jpg_count);

                // Open new output file to write to
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("Could not open output file.\n");
                    return 1;
                }

                // Write current block, stored in the buffer, to the new file
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);

                // Update count variable
                jpg_count++;
            }
            else
            {
                // Close previous image file
                fclose(output);

                // Create an adequate file name
                sprintf(filename, "%03i.jpg", jpg_count);

                // Open new output file to write to
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("Could not open output file.\n");
                    return 1;
                }

                // Write current block, stored in the buffer, to the new file
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);

                // Update count variable
                jpg_count++;
            }
        }
        else
        {
            if (jpg_count != 0)
            {
                // Write current block, stored in the buffer, to the new file
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
            }
        }
    }

    // Close files and free memory
    fclose(input);
    fclose(output);
    free(filename);
}

// Returns true if the memory in buffer corresponds to a JPG file
bool is_jpg(BYTE *buffer)
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0);
}