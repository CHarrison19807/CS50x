#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startSize, endSize;
    do
    {
        startSize = get_int("What is the starting size of population? ");
    }
    while (startSize < 9);

    // TODO: Prompt for end size
    do
    {
        endSize = get_int("What is the ending size of population? ");
    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    int llamaPopulation = startSize;
    int llamasDied;
    int llamasBorn;
    int years = 0;
    while (llamaPopulation < endSize)
    {
        llamasBorn = llamaPopulation / 3;
        llamasDied = llamaPopulation / 4;
        llamaPopulation += ((llamasBorn) - (llamasDied));
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);
}
