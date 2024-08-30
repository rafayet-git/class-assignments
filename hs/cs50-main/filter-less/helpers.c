#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen;
            image[i][j].rgbtRed = round(avg / 3);
            image[i][j].rgbtBlue = round(avg / 3);
            image[i][j].rgbtGreen = round(avg / 3);
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double newR;
    double newG;
    double newB;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newR = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            newG = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            newB = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));
            if (newR > 255.0)
            {
                newR = 255.0;  /// bytes are max 255
            }
            if (newG > 255.0)
            {
                newG = 255.0;
            }
            if (newB > 255.0)
            {
                newB = 255.0;
            }
            image[i][j].rgbtRed = newR;
            image[i][j].rgbtGreen = newG;
            image[i][j].rgbtBlue = newB;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // width is half so it doesnt reverse back to original
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make copy of original values
    RGBTRIPLE orig[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            orig[i][j] = image[i][j];
        }
    }
    double newR;
    double newG;
    double newB;
    int blocks;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // reset value
            blocks = 0;
            newR = 0;
            newG = 0;
            newB = 0;
            // find what blocks it has near it, incase it is in corner or edge
            for (int r = i - 1; r < i + 2; r++)
            {
                for (int t = j - 1; t < j + 2; t++)
                {
                    if ((r >= 0 && r < height) && (t >= 0 && t < width))
                    {
                        blocks++;
                        newR += orig[r][t].rgbtRed;
                        newG += orig[r][t].rgbtGreen;
                        newB += orig[r][t].rgbtBlue;
                    }
                }
            }
            // add to file
            image[i][j].rgbtRed = round(newR / blocks);
            image[i][j].rgbtGreen = round(newG / blocks);
            image[i][j].rgbtBlue = round(newB / blocks);
        }
    }
}
