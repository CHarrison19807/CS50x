#include "helpers.h"
#include "math.h"

void swap(RGBTRIPLE *a, RGBTRIPLE *b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sum = (double)image[i][j].rgbtRed + (double)image[i][j].rgbtBlue + (double)image[i][j].rgbtGreen;
            int average = round(sum / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            swap(&image[i][j], &image[i][width - (j + 1)]);
        }
    }
    return;
}
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pixels = 0;

            double sumRed = 0;
            double sumGreen = 0;
            double sumBlue = 0;

            for (int k = i - 1; k < i + 2; k++)
            {
                for (int n = j - 1; n < j + 2; n++)
                {
                    if (k >= 0 && k < height && n >= 0 && n < width)
                    {
                        sumRed += copy[k][n].rgbtRed;
                        sumGreen += copy[k][n].rgbtGreen;
                        sumBlue += copy[k][n].rgbtBlue;
                        pixels++;
                    }
                }
            }

            image[i][j].rgbtRed = round(sumRed / pixels);
            image[i][j].rgbtGreen = round(sumGreen / pixels);
            image[i][j].rgbtBlue = round(sumBlue / pixels);

        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double gxRed = 0;
            double gxGreen = 0;
            double gxBlue = 0;

            double gyRed = 0;
            double gyGreen = 0;
            double gyBlue = 0;

            int row = 0;

            for (int k = i - 1; k < i + 2; k++)
            {
                int col = 0;
                for (int n = j - 1; n < j + 2; n++)
                {
                    if (k >= 0 && k < height && n >= 0 && n < width)
                    {
                        gxRed += (gx[row][col] * copy[k][n].rgbtRed);
                        gxGreen += (gx[row][col] * copy[k][n].rgbtGreen);
                        gxBlue += (gx[row][col] * copy[k][n].rgbtBlue);

                        gyRed += (gy[row][col] * copy[k][n].rgbtRed);
                        gyGreen += (gy[row][col] * copy[k][n].rgbtGreen);
                        gyBlue += (gy[row][col] * copy[k][n].rgbtBlue);
                    }
                    col++;
                }
                row++;
            }
            int sobRed = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            int sobGreen = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            int sobBlue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));

            image[i][j].rgbtRed = (sobRed > 255) ? 255 : sobRed;
            image[i][j].rgbtGreen = (sobGreen > 255) ? 255 : sobGreen;
            image[i][j].rgbtBlue = (sobBlue > 255) ? 255 : sobBlue;
        }
    }
    return;
}
