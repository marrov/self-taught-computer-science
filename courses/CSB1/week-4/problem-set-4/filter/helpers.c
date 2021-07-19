#include "helpers.h"

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

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Loop through non-boundary elements
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            int red = 0, green = 0, blue = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    red   += image[i + x][j + y].rgbtRed;
                    green += image[i + x][j + y].rgbtGreen;
                    blue  += image[i + x][j + y].rgbtBlue;
                }
            }

            image[i][j].rgbtRed   = red   / 9.0 + 0.5;
            image[i][j].rgbtGreen = green / 9.0 + 0.5;
            image[i][j].rgbtBlue  = blue  / 9.0 + 0.5;
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