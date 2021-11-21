#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //To grayscale: (Red + Green + Blue) / 3 = Average, all the variables should use the average value.

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            int average = round((red + green + blue) / 3);

            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }

}

//set limit to 255
int limit(int limit)
{
    if (limit > 255)
    {
        limit = 255;
    }
    return limit;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int OgRed = pixel.rgbtRed;
            int OgGreen = pixel.rgbtGreen;
            int OgBlue = pixel.rgbtBlue;

            image[i][j].rgbtRed = limit(round(0.393 * OgRed + 0.769 * OgGreen + 0.189 * OgBlue));
            image[i][j].rgbtGreen = limit(round(0.349 * OgRed + 0.686 * OgGreen + 0.168 * OgBlue));
            image[i][j].rgbtBlue = limit(round(0.272 * OgRed + 0.534 * OgGreen + 0.131 * OgBlue));

        }
    }

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // invert the first row of the array (Pixels in picture), so the 1st pixel is in the last place. Probs with for loop.

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            
            image[i][width - j - 1].rgbtRed = red;
            image[i][width - j - 1].rgbtGreen = green;
            image[i][width - j - 1].rgbtBlue = blue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Take the average RGB value from the surrounding pixels, example; 1 pixel is surounded by eight other ones.

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float counter = 0.00;

            for (int k = -1; k < 2; k++)
            {
                for (int m = -1; m < 2; m++)
                {
                    if (i + k < 0 || i + k > height - 1 || j + m < 0 || j + m > width - 1)
                    {
                        continue;
                    }

                    sumRed += image[i+k][j+m].rgbtRed;
                    sumGreen += image[i+k][j+m].rgbtGreen;
                    sumBlue += image[i+k][j+m].rgbtBlue;

                    counter++;
                }
            }

            temp[i][j].rgbtRed = round(sumRed/counter);
            temp[i][j].rgbtGreen = round(sumGreen/counter);
            temp[i][j].rgbtBlue = round(sumBlue/counter);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

}
