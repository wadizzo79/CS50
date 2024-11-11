#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum;
    float avg;

    // Loop the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the average of red, green and blue
            BYTE red = image[i][j].rgbtRed;
            BYTE green = image[i][j].rgbtGreen;
            BYTE blue = image[i][j].rgbtBlue;

            sum = (float) red + (float) green + (float) blue;
            avg = round(sum / 3.0);
            // Update pixels
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    // Loop the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE red = image[i][j].rgbtRed;
            BYTE green = image[i][j].rgbtGreen;
            BYTE blue = image[i][j].rgbtBlue;
            // Compute sepia
            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            // Checks if the maximum value exceeds 255 and caps them if so
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Update pixels
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {

            // Reflect image
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int counter = 0;
            int row[] = {i - 1, i, i + 1};
            int column[] = {j - 1, j, j + 1};
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int activeRow = row[k];
                    int activeColumn = column[l];
                    if (activeRow >= 0 && activeRow < height && activeColumn >= 0 &&
                        activeColumn < width)
                    {
                        RGBTRIPLE pixel = image[activeRow][activeColumn];
                        sumRed += pixel.rgbtRed;
                        sumGreen += pixel.rgbtGreen;
                        sumBlue += pixel.rgbtBlue;

                        counter++;
                    }
                }
            }
            copy[i][j].rgbtRed = round(sumRed / counter);
            copy[i][j].rgbtGreen = round(sumGreen / counter);
            copy[i][j].rgbtBlue = round(sumBlue / counter);
        }
    }
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n] = copy[m][n];
        }
    }
    return;
}
