#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // for each row element
    {
        for (int j = 0; j < width; j++) // for each column element
        {
            // Calculate RBG average as nearest integer
            int iavg = avg_rbg(image[i][j]);

            // Set RGB pixel colors as integer average
            image[i][j].rgbtRed   = iavg;
            image[i][j].rgbtGreen = iavg;
            image[i][j].rgbtBlue  = iavg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < 1; i++) // for each row
    {
        for (int j = 0; j < 1; j++) // for each column until the middle
        {
            int temp;
        }
    }

    // Swap left and right pixel
    image[0][0].rgbtRed   = 255;
    image[0][0].rgbtBlue  = 0;
    image[0][0].rgbtGreen = 0;

    image[0][599].rgbtRed   = 0;
    image[0][599].rgbtBlue  = 255;
    image[0][599].rgbtGreen = 0;

    image[1][0].rgbtRed   = 0;
    image[1][0].rgbtBlue  = 0;
    image[1][0].rgbtGreen = 255;

    printf("Height: %i px\nWidth: %i px\n", height, width);

    //swap(&image[0][0], &image[0][width])

return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Average RGB colors (always positive) as nearest int using type casting
int avg_rbg(RGBTRIPLE pixel)
{
    return (pixel.rgbtRed + pixel.rgbtBlue + pixel.rgbtGreen) / 3.0 + 0.5;
}

// Swap pixel positions
void swap(RGBTRIPLE* a, RGBTRIPLE* b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}