#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Filter prototypes
void grayscale(int height, int width, RGBTRIPLE image[height][width]);
void reflect(int height, int width, RGBTRIPLE image[height][width]);
void edges(int height, int width, RGBTRIPLE image[height][width]);
void blur(int height, int width, RGBTRIPLE image[height][width]);

// My function prototypes
int iavg(float sum, float n);
void swap(RGBTRIPLE *pixel_a, RGBTRIPLE *pixel_b);
void set_pixel(RGBTRIPLE *pixel, int red, int green, int blue);
void sum_pixel_colors(RGBTRIPLE *pixel, float *sum_red, float* sum_green, float* sum_blue);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // for each row element
    {
        for (int j = 0; j < width; j++) // for each column element
        {
            // Calculate average of all colors of pixel
            float num_colors = 3.0;
            float sum_colors = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            int   avg_colors = iavg(sum_colors, num_colors);

            // Set RGB pixel colors as average
            set_pixel(&image[i][j], avg_colors, avg_colors, avg_colors);
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
            sum_pixel_colors(&image[i][j], &red, &green, &blue);
            n++;

            // Check if each of the neighbours exists, then add it and keep count
            if (i - 1 >= 0) // N
            {
                sum_pixel_colors(&image[i - 1][j], &red, &green, &blue);
                n++;
            }

            if (i - 1 >= 0 && j - 1 >= 0) // NW
            {
                sum_pixel_colors(&image[i - 1][j - 1], &red, &green, &blue);
                n++;
            }

            if (i - 1 >= 0 && j + 1 <= width - 1) // NE
            {
                sum_pixel_colors(&image[i - 1][j + 1], &red, &green, &blue);
                n++;
            }

            if (j - 1 >= 0) // W
            {
                sum_pixel_colors(&image[i][j - 1], &red, &green, &blue);
                n++;
            }

            if (j + 1 <= width - 1) // E
            {
                sum_pixel_colors(&image[i][j + 1], &red, &green, &blue);
                n++;
            }

            if (i + 1 <= height - 1) // S
            {
                sum_pixel_colors(&image[i + 1][j], &red, &green, &blue);
                n++;
            }

            if (i + 1 <= height - 1 && j - 1 >= 0) // SW
            {
                sum_pixel_colors(&image[i + 1][j - 1], &red, &green, &blue);
                n++;
            }

            if (i + 1 <= height - 1 && j + 1 <= width - 1) // SE
            {
                sum_pixel_colors(&image[i + 1][j + 1], &red, &green, &blue);
                n++;
            }

            // Set
            set_pixel(&blured[i][j], iavg(red, n), iavg(green, n), iavg(blue, n));
        }
    }

    // Copy elements of blured to image
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

// Average by dividing sum over number of elements as nearest int using round()
int iavg(float sum, float n)
{
    return round(sum / n);
}

// Swap pixel positions
void swap(RGBTRIPLE *pixel_a, RGBTRIPLE *pixel_b)
{
    RGBTRIPLE tmp = *pixel_a;
    *pixel_a = *pixel_b;
    *pixel_b = tmp;
}

// Set colors of pixel
void set_pixel(RGBTRIPLE *pixel, int red, int green, int blue)
{
    pixel->rgbtRed   = red;
    pixel->rgbtGreen = green;
    pixel->rgbtBlue  = blue;
}

// Update cumulative sum of red, green and blue from colors of pixel
void sum_pixel_colors(RGBTRIPLE *pixel, float *sum_red, float* sum_green, float* sum_blue)
{
    *sum_red   += pixel->rgbtRed;
    *sum_green += pixel->rgbtGreen;
    *sum_blue  += pixel->rgbtBlue;
}