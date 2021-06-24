#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt for height of pyramid
    do
    {
        height = get_int("Height (from 1 to 8): ");
    }
    while (height < 1 || height > 8);

    // Print pyramid block characters
    for (int i = 0; i < height; i++)
    {
        // Loop for left-hand side
        for (int j = 0; j < height; j++)
        {
            char c = (j >= (height - 1) - i) ? '#' : ' ';
            printf("%c", c);
        }

        printf("  ");

        // Loop for right-hand side
        for (int j = 0; j < height; j++)
        {
            if (j <= i)
            {
                printf("#");
            }
        }

        printf("\n");
    }
}
