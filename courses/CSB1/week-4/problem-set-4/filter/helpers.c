#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N_CHANNELS 3
#define N_KERNEL 3

// Filter prototypes
void grayscale(int height, int width, RGBTRIPLE image[height][width]);
void reflect(int height, int width, RGBTRIPLE image[height][width]);
void edges(int height, int width, RGBTRIPLE image[height][width]);
void blur(int height, int width, RGBTRIPLE image[height][width]);

// My function prototypes
int iavg(float sum, float n);
void swap(RGBTRIPLE *pixel_a, RGBTRIPLE *pixel_b);
void set_pixel(RGBTRIPLE *pixel, int red, int green, int blue);
void sum_pixel_colors(RGBTRIPLE *pixel, float *sum_red, float *sum_green, float *sum_blue, float *n);
void copy_image(int height, int width, RGBTRIPLE img_a[height][width], RGBTRIPLE img_b[height][width]);
void compute_kernel(int height, int width, RGBTRIPLE image[height][width], float RGB[N_CHANNELS], int G[N_KERNEL][N_KERNEL], int i, int j);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // for each row element
    {
        for (int j = 0; j < width; j++) // for each column element
        {
            // Calculate average of all colors of pixel
            float num_colors = N_CHANNELS;
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
    // Allocate memory for copy of image to blur pixels to
    RGBTRIPLE(*blured)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (blured == NULL)
    {
        fprintf(stderr, "Not enough memory to store copy of image for blurring.\n");
        free(blured);
        return;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Count and sum variables to keep track of RGB channels' sum and count of valid neighbours
            float n = 0, red = 0, green = 0, blue = 0;

            // Always add the center pixel colors to the sum
            sum_pixel_colors(&image[i][j], &red, &green, &blue, &n);

            // Check if each of the 8 neighbours exists, then add it to sum and keep count of valid neigbours
            if (i - 1 >= 0) // N
                sum_pixel_colors(&image[i - 1][j], &red, &green, &blue, &n);

            if (i - 1 >= 0 && j - 1 >= 0) // NW
                sum_pixel_colors(&image[i - 1][j - 1], &red, &green, &blue, &n);

            if (i - 1 >= 0 && j + 1 <= width - 1) // NE
                sum_pixel_colors(&image[i - 1][j + 1], &red, &green, &blue, &n);

            if (j - 1 >= 0) // W
                sum_pixel_colors(&image[i][j - 1], &red, &green, &blue, &n);

            if (j + 1 <= width - 1) // E
                sum_pixel_colors(&image[i][j + 1], &red, &green, &blue, &n);

            if (i + 1 <= height - 1) // S
                sum_pixel_colors(&image[i + 1][j], &red, &green, &blue, &n);

            if (i + 1 <= height - 1 && j - 1 >= 0) // SW
                sum_pixel_colors(&image[i + 1][j - 1], &red, &green, &blue, &n);

            if (i + 1 <= height - 1 && j + 1 <= width - 1) // SE
                sum_pixel_colors(&image[i + 1][j + 1], &red, &green, &blue, &n);

            // Set each RGB pixel color to the RBG average of its valid neigbours
            set_pixel(&blured[i][j], iavg(red, n), iavg(green, n), iavg(blue, n));
        }
    }

    // Copy elements of blured to image
    copy_image(height, width, image, blured);

    return;
}

// Highlight edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for copy of image to blur pixels to
    RGBTRIPLE(*edge)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (edge == NULL)
    {
        fprintf(stderr, "Not enough memory to store copy of image for blurring.\n");
        free(edge);
        return;
    }

    // Initialize kernels
    int Gx[N_KERNEL][N_KERNEL] = {{-1,  0,  1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[N_KERNEL][N_KERNEL] = {{-1, -2, -1}, { 0, 0, 0}, { 1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Count and sum variables to keep track of RGB channels' sum and count of valid neighbours
            float n = 0;
            float RGBx[N_CHANNELS] = {0, 0, 0};
            float RGBy[N_CHANNELS] = {0, 0, 0};

            // Compute kernels for x and y
            compute_kernel(height, width, image, RGBx, Gx, i, j);
            compute_kernel(height, width, image, RGBy, Gy, i, j);

            // Calculate sqrt as nearest int
            int red   = fminf(round(sqrtf(RGBx[0] * RGBx[0] + RGBy[0] * RGBy[0])), 255);
            int green = fminf(round(sqrtf(RGBx[1] * RGBx[1] + RGBy[1] * RGBy[1])), 255);
            int blue  = fminf(round(sqrtf(RGBx[2] * RGBx[2] + RGBy[2] * RGBy[2])), 255);

            // SET PIXEL
            set_pixel(&edge[i][j], red, green, blue);
        }
    }

    // Copy elements of edge to image
    copy_image(height, width, image, edge);

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
void sum_pixel_colors(RGBTRIPLE *pixel, float *sum_red, float *sum_green, float *sum_blue, float *n)
{
    *sum_red   += pixel->rgbtRed;
    *sum_green += pixel->rgbtGreen;
    *sum_blue  += pixel->rgbtBlue;
    (*n)++;
}

// Copy contents of one image to another for two identically sized images
void copy_image(int height, int width, RGBTRIPLE img_a[height][width], RGBTRIPLE img_b[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img_a[i][j] = img_b[i][j];
        }
    }
}


// Assuming 3 RGB channels and a kernel of 3*3... :C
void compute_kernel(int height, int width, RGBTRIPLE image[height][width], float RGB[3], int G[3][3], int i, int j)
{
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            // Coordinates of current neighbour
            int cx = i + x;
            int cy = j + y;

            if (cx >= 0 && cx < height && cy >= 0 && cy < width)
            {
                RGB[0] += image[cx][cy].rgbtRed   * G[x + 1][y + 1];
                RGB[1] += image[cx][cy].rgbtGreen * G[x + 1][y + 1];
                RGB[2] += image[cx][cy].rgbtBlue  * G[x + 1][y + 1];
            }
        }
    }
}
