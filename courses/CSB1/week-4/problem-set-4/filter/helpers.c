#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Filter prototypes
void grayscale(int height, int width, RGBTRIPLE image[height][width]);
void reflect(int height, int width, RGBTRIPLE image[height][width]);
void edges(int height, int width, RGBTRIPLE image[height][width]);
void blur(int height, int width, RGBTRIPLE image[height][width]);

// My function prototypes
int avg_rbg(RGBTRIPLE pixel);
void swap(RGBTRIPLE *pixel_a, RGBTRIPLE *pixel_b);


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
    for (int i = 0; i < height; i++) // for each row
    {
        for (int j = 0, mid = (width + 1) / 2; j < mid; j++) // for each column until the middle
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blured[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float n = 0; // Count for number of neighbouring pixels to make average from
            float red = 0, green = 0, blue = 0;

            // Always add the center pixel
            red   += image[i][j].rgbtRed;
            green += image[i][j].rgbtGreen;
            blue  += image[i][j].rgbtBlue;
            n++;

            // Check if each of the neighbours exists, then add it and keep count
            if (i - 1 >= 0) // N
            {
                red   += image[i - 1][j].rgbtRed;
                green += image[i - 1][j].rgbtGreen;
                blue  += image[i - 1][j].rgbtBlue;
                n++;
            }

            if (i - 1 >= 0 && j - 1 >= 0) // NW
            {
                red   += image[i - 1][j - 1].rgbtRed;
                green += image[i - 1][j - 1].rgbtGreen;
                blue  += image[i - 1][j - 1].rgbtBlue;
                n++;
            }

            if (i - 1 >= 0 && j + 1 <= width - 1) // NE
            {
                red   += image[i - 1][j + 1].rgbtRed;
                green += image[i - 1][j + 1].rgbtGreen;
                blue  += image[i - 1][j + 1].rgbtBlue;
                n++;
            }

            if (j - 1 >= 0) // W
            {
                red   += image[i][j - 1].rgbtRed;
                green += image[i][j - 1].rgbtGreen;
                blue  += image[i][j - 1].rgbtBlue;
                n++;
            }

            if (j + 1 <= width - 1) // E
            {
                red   += image[i][j + 1].rgbtRed;
                green += image[i][j + 1].rgbtGreen;
                blue  += image[i][j + 1].rgbtBlue;
                n++;
            }

            if (i + 1 <= height - 1) // S
            {
                red   += image[i + 1][j].rgbtRed;
                green += image[i + 1][j].rgbtGreen;
                blue  += image[i + 1][j].rgbtBlue;
                n++;
            }

            if (i + 1 <= height - 1 && j - 1 >= 0) // SW
            {
                red   += image[i + 1][j - 1].rgbtRed;
                green += image[i + 1][j - 1].rgbtGreen;
                blue  += image[i + 1][j - 1].rgbtBlue;
                n++;
            }

            if (i + 1 <= height - 1 && j + 1 <= width - 1) // SE
            {
                red   += image[i + 1][j + 1].rgbtRed;
                green += image[i + 1][j + 1].rgbtGreen;
                blue  += image[i + 1][j + 1].rgbtBlue;
                n++;
            }

            blured[i][j].rgbtRed   = round(red   / n);
            blured[i][j].rgbtGreen = round(green / n);
            blured[i][j].rgbtBlue  = round(blue  / n);
        }
    }

    // Copy elements of blur to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blured[i][j];
        }
    }

    return;
}

// Highlight edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Average RGB colors (always positive) as nearest int using type casting
int avg_rbg(RGBTRIPLE pixel)
{
    return (pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0 + 0.5;
}

// Swap pixel positions
void swap(RGBTRIPLE *pixel_a, RGBTRIPLE *pixel_b)
{
    RGBTRIPLE tmp = *pixel_a;
    *pixel_a = *pixel_b;
    *pixel_b = tmp;
}