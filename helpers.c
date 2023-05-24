#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Defines a new struct with float values for each of the colors
typedef struct
{
    float red;
    float green;
    float blue;
}
color;


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0, h = height; a < h; a++)
    {
        for (int b = 0, w = width; b < w; b++)
        {
            // Dynamically allocates the grayscale variable used later to find the average of the colors in the pixel
            float *grayscale = malloc(sizeof(float));
            
            // Implementation of the grayscale variable as well as rounding it to the nearest variable
            *grayscale = (float)(image[a][b].rgbtBlue + image[a][b].rgbtGreen + image[a][b].rgbtRed) / (float)3.0;
            *grayscale = llrint(*grayscale);
            
            // Allocates the value of the grayscale variable to each color
            image[a][b].rgbtBlue = *grayscale;
            image[a][b].rgbtGreen = *grayscale;
            image[a][b].rgbtRed = *grayscale;
            
            // Frees the dynamically allocated variable
            free(grayscale);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0, h = height; a < h; a++)
    {
        for (int b = 0, w = width / 2; b < w; b++)
        {
            // Swaps the blue value of the selected pixel with the mirrored pixel on the right side of the picture
            int* temp_blue = malloc(sizeof(int));
            *temp_blue = image[a][b].rgbtBlue;
            image[a][b].rgbtBlue = image[a][width - b - 1].rgbtBlue;
            image[a][width - b - 1].rgbtBlue = *temp_blue;
            free(temp_blue);
            
            // Swaps the green value
            int* temp_green = malloc(sizeof(int));
            *temp_green = image[a][b].rgbtGreen;
            image[a][b].rgbtGreen = image[a][width - b - 1].rgbtGreen;
            image[a][width - b - 1].rgbtGreen = *temp_green;
            free(temp_green);
            
            // Swaps the red value
            int* temp_red = malloc(sizeof(int));
            *temp_red = image[a][b].rgbtRed;
            image[a][b].rgbtRed = image[a][width - b - 1].rgbtRed;
            image[a][width - b - 1].rgbtRed = *temp_red;
            free(temp_red);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Array variable initiation
    color temp[height][width];
    int counter[height][width];
    
    // Sets each value in the counter variable to 0
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            counter[a][b] = 0;
        }
    }
    
    // Overall, this function works by first adding the pixels color values, including the said pixel itself, located around the selected pixel that exist into a temporary array
    // Then, you divide each element of the array by the amount of pixels added to the array to find the average for each color and set that value as the image array value
    for (int a = 0; a < height; a ++)
    {
        for (int b = 0; b < width; b++)
        {
            // Adds the pixel itself to the temporary array
            temp[a][b].blue = image[a][b].rgbtBlue;
            temp[a][b].green = image[a][b].rgbtGreen;
            temp[a][b].red = image[a][b].rgbtRed;
            counter[a][b]++;
            
            if (b > 0)
            {
                // Adds the pixel to the left of the selected pixel, if exists
                temp[a][b].blue = temp[a][b].blue + image[a][b - 1].rgbtBlue;
                temp[a][b].green = temp[a][b].green + image[a][b - 1].rgbtGreen;
                temp[a][b].red = temp[a][b].red + image[a][b - 1].rgbtRed;
                counter[a][b]++;
            }
            
            if (b < width - 1)
            {
                // Adds the pixel to the right of the selected pixel, if exists
                temp[a][b].blue = temp[a][b].blue + image[a][b + 1].rgbtBlue;
                temp[a][b].green = temp[a][b].green + image[a][b + 1].rgbtGreen;
                temp[a][b].red = temp[a][b].red + image[a][b + 1].rgbtRed;
                counter[a][b]++;
            }
            
            if (a > 0)
            {
                // Adds the pixel above the selected pixel, if exists
                temp[a][b].blue = temp[a][b].blue + image[a - 1][b].rgbtBlue;
                temp[a][b].green = temp[a][b].green + image[a - 1][b].rgbtGreen;
                temp[a][b].red = temp[a][b].red + image[a - 1][b].rgbtRed;
                counter[a][b]++;
            }
            
            if (a > 0 && b > 0)
            {
                // Adds the pixel diagonally to the top left of the selected pixel, if exists
                temp[a][b].blue = temp[a][b].blue + image[a - 1][b - 1].rgbtBlue;
                temp[a][b].green = temp[a][b].green + image[a - 1][b - 1].rgbtGreen;
                temp[a][b].red = temp[a][b].red + image[a - 1][b - 1].rgbtRed;
                counter[a][b]++;
            }
            
            if (a > 0 && b < width - 1)
            {
                // Adds the pixel diagonally to the top right of the selected pixel, if exists
                temp[a][b].blue = temp[a][b].blue + image[a - 1][b + 1].rgbtBlue;
                temp[a][b].green = temp[a][b].green + image[a - 1][b + 1].rgbtGreen;
                temp[a][b].red = temp[a][b].red + image[a - 1][b + 1].rgbtRed;
                counter[a][b]++;
            }
            
            if (a < height - 1)
            {
                // Adds the pixel below the selected pixel, if exists
                temp[a][b].blue = temp[a][b].blue + image[a + 1][b].rgbtBlue;
                temp[a][b].green = temp[a][b].green + image[a + 1][b].rgbtGreen;
                temp[a][b].red = temp[a][b].red + image[a + 1][b].rgbtRed;
                counter[a][b]++;
            }
            
            if (a < height - 1 && b > 0)
            {
                // Adds the pixel diagonally to the bottom left of the selected pixel, if exists
                temp[a][b].blue = temp[a][b].blue + image[a + 1][b - 1].rgbtBlue;
                temp[a][b].green = temp[a][b].green + image[a + 1][b - 1].rgbtGreen;
                temp[a][b].red = temp[a][b].red + image[a + 1][b - 1].rgbtRed;
                counter[a][b]++;
            }
            
            if (a < height - 1 && b < width - 1)
            {
                // Adds the pixel diagonally to the bottom left of the selected pixel, if exists
                temp[a][b].blue = temp[a][b].blue + image[a + 1][b + 1].rgbtBlue;
                temp[a][b].green = temp[a][b].green + image[a + 1][b + 1].rgbtGreen;
                temp[a][b].red = temp[a][b].red + image[a + 1][b + 1].rgbtRed;
                counter[a][b]++;
            }
            
            // Divides the temporary array element by the amount of pixels added to the element for each color, to find the average
            temp[a][b].blue = temp[a][b].blue / (float)counter[a][b];
            temp[a][b].green = temp[a][b].green / (float)counter[a][b];
            temp[a][b].red = temp[a][b].red / (float)counter[a][b];
        }
    }
    
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            // Sets each element of the temporary array, rounded, to the image array
            image[a][b].rgbtBlue = round(temp[a][b].blue);
            image[a][b].rgbtGreen = round(temp[a][b].green);
            image[a][b].rgbtRed = round(temp[a][b].red);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Dynamically allocates a 2d array for the gx "kernel"
    color *gx_temp[height];
    for (int i = 0; i < height; i++)
    {
        gx_temp[i] = (color*)malloc(width * sizeof(color));
    }
    
    // Dynamically allocates a 2d array for the gy "kernel"
    color *gy_temp[height];
    for (int i = 0; i < height; i++)
    {
        gy_temp[i] = (color*)malloc(width * sizeof(color));
    }
    
    // Dynamically allocates a 2d array used as the combined "kernel" for the Sobel algorithm
    color* temp[height];
    for (int i = 0; i < height; i++)
    {
        temp[i] = (color*)malloc(width * sizeof(color));
    }
    
    // Overall, this portion function works by computing the gx and gy kernal values for each color for the pixel based on the location of the pixel
    // These values are allocated to the gx_temp and gy_temp arrays
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            // This if statement would apply to the top left corner pixel
            if (a == 0 && b == 0)
            {
                gx_temp[a][b].blue = 
                    (image[a][b + 1].rgbtBlue * 2) + image[a + 1][b + 1].rgbtBlue;
            
                gy_temp[a][b].blue = 
                    (image[a + 1][b].rgbtBlue * 2) + image[a + 1][b + 1].rgbtBlue;
                
                
                gx_temp[a][b].green = 
                    (image[a][b + 1].rgbtGreen * 2) + image[a + 1][b + 1].rgbtGreen;
            
                gy_temp[a][b].green = 
                    (image[a + 1][b].rgbtGreen * 2) + image[a + 1][b + 1].rgbtGreen;
                
                
                gx_temp[a][b].red = 
                    (image[a][b + 1].rgbtRed * 2) + image[a + 1][b + 1].rgbtRed;
            
                gy_temp[a][b].red = 
                    (image[a + 1][b].rgbtRed * 2) + image[a + 1][b + 1].rgbtRed;
            }
            
            // This applies to the pixels that are located on the top edge of the picture, excluding the corners
            if (a == 0 && b != 0 && b != width - 1)
            {
                gx_temp[a][b].blue = 
                    (image[a][b - 1].rgbtBlue * -2) - image[a + 1][b - 1].rgbtBlue +
                    (image[a][b + 1].rgbtBlue * 2) + image[a + 1][b + 1].rgbtBlue;
                
                gy_temp[a][b].blue = 
                    image[a + 1][b - 1].rgbtBlue + (image[a + 1][b].rgbtBlue * 2) + image[a + 1][b + 1].rgbtBlue;
                
                
                gx_temp[a][b].green = 
                    (image[a][b - 1].rgbtGreen * -2) - image[a + 1][b - 1].rgbtGreen +
                    (image[a][b + 1].rgbtGreen * 2) + image[a + 1][b + 1].rgbtGreen;
                
                gy_temp[a][b].green = 
                    image[a + 1][b - 1].rgbtGreen + (image[a + 1][b].rgbtGreen * 2) + image[a + 1][b + 1].rgbtGreen;
                
                
                gx_temp[a][b].red = 
                    (image[a][b - 1].rgbtRed * -2) - image[a + 1][b - 1].rgbtRed +
                    (image[a][b + 1].rgbtRed * 2) + image[a + 1][b + 1].rgbtRed;
                
                gy_temp[a][b].red = 
                    image[a + 1][b - 1].rgbtRed + (image[a + 1][b].rgbtRed * 2) + image[a + 1][b + 1].rgbtRed;
            }
            
            // This applies to the top right corner pixel
            if (a == 0 && b == width - 1)
            {
                gx_temp[a][b].blue = 
                    (image[a][b - 1].rgbtBlue * -2) - image[a + 1][b - 1].rgbtBlue;
                
                gy_temp[a][b].blue = 
                    image[a + 1][b - 1].rgbtBlue + (image[a + 1][b].rgbtBlue * 2);
                
                
                gx_temp[a][b].green = 
                    (image[a][b - 1].rgbtGreen * -2) - image[a + 1][b - 1].rgbtGreen;
                
                gy_temp[a][b].green = 
                    image[a + 1][b - 1].rgbtGreen + (image[a + 1][b].rgbtGreen * 2);
                
                
                gx_temp[a][b].red = 
                    (image[a][b - 1].rgbtRed * -2) - image[a + 1][b - 1].rgbtRed;
                
                gy_temp[a][b].red = 
                    image[a + 1][b - 1].rgbtRed + (image[a + 1][b].rgbtRed * 2);
            }
            
            // This applies to the left edge of the picture, excluding the corner pixels
            if (a != 0 && a != height - 1 && b == 0)
            {
                gx_temp[a][b].blue = 
                    image[a - 1][b + 1].rgbtBlue + (image[a][b + 1].rgbtBlue * 2) + image[a + 1][b + 1].rgbtBlue;
                
                gy_temp[a][b].blue = 
                    (image[a - 1][b].rgbtBlue * -2) + (image[a + 1][b].rgbtBlue * 2) -
                    image[a - 1][b + 1].rgbtBlue + image[a + 1][b + 1].rgbtBlue;
                
                
                gx_temp[a][b].green = 
                    image[a - 1][b + 1].rgbtGreen + (image[a][b + 1].rgbtGreen * 2) + image[a + 1][b + 1].rgbtGreen;
                
                gy_temp[a][b].green = 
                    (image[a - 1][b].rgbtGreen * -2) + (image[a + 1][b].rgbtGreen * 2) -
                    image[a - 1][b + 1].rgbtGreen + image[a + 1][b + 1].rgbtGreen;
                
                
                gx_temp[a][b].red = 
                    image[a - 1][b + 1].rgbtRed + (image[a][b + 1].rgbtRed * 2) + image[a + 1][b + 1].rgbtRed;
                
                gy_temp[a][b].red = 
                    (image[a - 1][b].rgbtRed * -2) + (image[a + 1][b].rgbtRed * 2) -
                    image[a - 1][b + 1].rgbtRed + image[a + 1][b + 1].rgbtRed;
            }
            
            // This applies to all pixels excluding the edges and corners of the picture
            if (a != 0 && a != height - 1 && b != 0 && b != width - 1)
            {
                gx_temp[a][b].blue = 
                    -image[a - 1][b - 1].rgbtBlue + (image[a][b - 1].rgbtBlue * -2) -
                    image[a + 1][b - 1].rgbtBlue + image[a - 1][b + 1].rgbtBlue +
                    (image[a][b + 1].rgbtBlue * 2) + image[a + 1][b + 1].rgbtBlue;
                
                gy_temp[a][b].blue = 
                    -image[a - 1][b - 1].rgbtBlue + image[a + 1][b - 1].rgbtBlue +
                    (image[a - 1][b].rgbtBlue * -2) + (image[a + 1][b].rgbtBlue * 2) -
                    image[a - 1][b + 1].rgbtBlue + image[a + 1][b + 1].rgbtBlue;
                
                
                gx_temp[a][b].green = 
                    -image[a - 1][b - 1].rgbtGreen + (image[a][b - 1].rgbtGreen * -2) -
                    image[a + 1][b - 1].rgbtGreen + image[a - 1][b + 1].rgbtGreen +
                    (image[a][b + 1].rgbtGreen * 2) + image[a + 1][b + 1].rgbtGreen;
                
                gy_temp[a][b].green = 
                    -image[a - 1][b - 1].rgbtGreen + image[a + 1][b - 1].rgbtGreen +
                    (image[a - 1][b].rgbtGreen * -2) + (image[a + 1][b].rgbtGreen * 2) -
                    image[a - 1][b + 1].rgbtGreen + image[a + 1][b + 1].rgbtGreen;
                
                
                gx_temp[a][b].red = 
                    -image[a - 1][b - 1].rgbtRed + (image[a][b - 1].rgbtRed * -2) -
                    image[a + 1][b - 1].rgbtRed + image[a - 1][b + 1].rgbtRed +
                    (image[a][b + 1].rgbtRed * 2) + image[a + 1][b + 1].rgbtRed;
                
                gy_temp[a][b].red = 
                    -image[a - 1][b - 1].rgbtRed + image[a + 1][b - 1].rgbtRed +
                    (image[a - 1][b].rgbtRed * -2) + (image[a + 1][b].rgbtRed * 2) -
                    image[a - 1][b + 1].rgbtRed + image[a + 1][b + 1].rgbtRed;
            }
            
            // This applies to the right edge of the picture, excluding the corner pixels
            if (a != 0 && a != height - 1 && b == width - 1)
            {
                gx_temp[a][b].blue = 
                    -image[a - 1][b - 1].rgbtBlue + (image[a][b - 1].rgbtBlue * -2) - image[a + 1][b - 1].rgbtBlue;
                
                gy_temp[a][b].blue = 
                    -image[a - 1][b - 1].rgbtBlue + image[a + 1][b - 1].rgbtBlue +
                    (image[a - 1][b].rgbtBlue * -2) + (image[a + 1][b].rgbtBlue * 2);
                
                
                gx_temp[a][b].green = 
                    -image[a - 1][b - 1].rgbtGreen + (image[a][b - 1].rgbtGreen * -2) - image[a + 1][b - 1].rgbtGreen;
                
                gy_temp[a][b].green = 
                    -image[a - 1][b - 1].rgbtGreen + image[a + 1][b - 1].rgbtGreen +
                    (image[a - 1][b].rgbtGreen * -2) + (image[a + 1][b].rgbtGreen * 2);
                
                
                gx_temp[a][b].red = 
                    -image[a - 1][b - 1].rgbtRed + (image[a][b - 1].rgbtRed * -2) - image[a + 1][b - 1].rgbtRed;
                
                gy_temp[a][b].red = 
                    -image[a - 1][b - 1].rgbtRed + image[a + 1][b - 1].rgbtRed +
                    (image[a - 1][b].rgbtRed * -2) + (image[a + 1][b].rgbtRed * 2);
            }
            
            // This applies to the bottom left corner pixel
            if (a == height - 1 && b == 0)
            {
                gx_temp[a][b].blue = 
                    image[a - 1][b + 1].rgbtBlue + (image[a][b + 1].rgbtBlue * 2);
                
                gy_temp[a][b].blue = 
                    (image[a - 1][b].rgbtBlue * -2) - image[a - 1][b + 1].rgbtBlue;
                
                
                gx_temp[a][b].green = 
                    image[a - 1][b + 1].rgbtGreen + (image[a][b + 1].rgbtGreen * 2);
                
                gy_temp[a][b].green = 
                    (image[a - 1][b].rgbtGreen * -2) - image[a - 1][b + 1].rgbtGreen;
                
                
                gx_temp[a][b].red = 
                    image[a - 1][b + 1].rgbtRed + (image[a][b + 1].rgbtRed * 2);
                
                gy_temp[a][b].red = 
                    (image[a - 1][b].rgbtRed * -2) - image[a - 1][b + 1].rgbtRed;
            }
            
            // This applies to the bottom edge, excluding the corner pixels
            if (a == height - 1 && b != 0 && b != width - 1)
            {
                gx_temp[a][b].blue = 
                    -image[a - 1][b - 1].rgbtBlue + (image[a][b - 1].rgbtBlue * -2) +
                    image[a - 1][b + 1].rgbtBlue + (image[a][b + 1].rgbtBlue * 2);
                
                gy_temp[a][b].blue = 
                    -image[a - 1][b - 1].rgbtBlue + (image[a - 1][b].rgbtBlue * -2) - image[a - 1][b + 1].rgbtBlue;
                
                
                gx_temp[a][b].green = 
                    -image[a - 1][b - 1].rgbtGreen + (image[a][b - 1].rgbtGreen * -2) +
                    image[a - 1][b + 1].rgbtGreen + (image[a][b + 1].rgbtGreen * 2);
                
                gy_temp[a][b].green = 
                    -image[a - 1][b - 1].rgbtGreen + (image[a - 1][b].rgbtGreen * -2) - image[a - 1][b + 1].rgbtGreen;
                
                
                gx_temp[a][b].red = 
                    -image[a - 1][b - 1].rgbtRed + (image[a][b - 1].rgbtRed * -2) +
                    image[a - 1][b + 1].rgbtRed + (image[a][b + 1].rgbtRed * 2);
                
                gy_temp[a][b].red = 
                    -image[a - 1][b - 1].rgbtRed + (image[a - 1][b].rgbtRed * -2) - image[a - 1][b + 1].rgbtRed;
            }
            
            // This applies to the bottom right corner pixel
            if (a == height - 1 && b == width - 1)
            {
                gx_temp[a][b].blue = 
                    -image[a - 1][b - 1].rgbtBlue + (image[a][b - 1].rgbtBlue * -2);
                
                gy_temp[a][b].blue = 
                    -image[a - 1][b - 1].rgbtBlue + (image[a - 1][b].rgbtBlue * -2);
                
                
                gx_temp[a][b].green = 
                    -image[a - 1][b - 1].rgbtGreen + (image[a][b - 1].rgbtGreen * -2);
                
                gy_temp[a][b].green = 
                    -image[a - 1][b - 1].rgbtGreen + (image[a - 1][b].rgbtGreen * -2);
                
                
                gx_temp[a][b].red = 
                    -image[a - 1][b - 1].rgbtRed + (image[a][b - 1].rgbtRed * -2);
                
                gy_temp[a][b].red = 
                    -image[a - 1][b - 1].rgbtRed + (image[a - 1][b].rgbtRed * -2);
            }
        }
    }
    
    // Combines the gx and gy kernels using the Sobel algorithm
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            temp[a][b].blue = sqrt(pow(gx_temp[a][b].blue, 2) + pow(gy_temp[a][b].blue, 2));
            temp[a][b].green = sqrt(pow(gx_temp[a][b].green, 2) + pow(gy_temp[a][b].green, 2));
            temp[a][b].red = sqrt(pow(gx_temp[a][b].red, 2) + pow(gy_temp[a][b].red, 2));
        }
    }
    
    // Frees the dynamically allocated gx_temp and gy_temp 2d arrays
    for (int i = 0; i < height; i++)
    {
        free(gx_temp[i]);
        free(gy_temp[i]);
    }
    
    // Assigns the values for the colors in the temp array to the image array (with 255 as a max)
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            if (temp[a][b].blue > 255)
            {
                image[a][b].rgbtBlue = 255;
            }
            else
            {
                image[a][b].rgbtBlue = llrint(temp[a][b].blue);
            }
            
            if (temp[a][b].green > 255)
            {
                image[a][b].rgbtGreen = 255;
            }
            else
            {
                image[a][b].rgbtGreen = llrint(temp[a][b].green);
            }
            
            if (temp[a][b].red > 255)
            {
                image[a][b].rgbtRed = 255;
            }
            else
            {
                image[a][b].rgbtRed = llrint(temp[a][b].red);
            }
        }
    }
    
    // Frees the temp 2d array
    for (int i = 0; i < height; i++)
    {
        free(temp[i]);
    }
    return;
}
