#include <cs50.h>
#include <stdio.h>

void buildPyramid(int height);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    buildPyramid(height);
}
void buildPyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        // Right side of pyramid
        for (int k = height - i; k > 1; k--)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("  "); // Gap

        // Left side of pyramid
        int m = i;
        while (m >= 0)
        {
            printf("#");
            m--;
        }
        // Next level
        printf("\n");
    }
}
