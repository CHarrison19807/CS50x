#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int textFormula(string text);

int main(void)
{
    string text = get_string("Text: ");
    int index = textFormula(text);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int textFormula(string text)
{
    int length = strlen(text);
    float index = 0;
    int letters = 0;
    int sentences = 0;
    int words = 1;
    for (int i = 0; i < length; i++)
    {
        if ((text[i] < 91 && text[i] > 64)  || (text[i] < 122 && text[i] > 96))
        {
            letters++;
        }
        if (text[i] == 33 || text[i] == 63 || text[i] == 46)
        {
            sentences++;
        }
        if (text[i] == 32)
        {
            words++;
        }
    }
    double L = (((float) letters / (float) words) * 100.0);
    double S = (((float) sentences / (float) words) * 100.0);
    index = 0.0588 * (((float) letters / (float) words) * 100.0) - 0.296 * (((float) sentences / (float) words) * 100.0) - 15.8;

    index = round(index);

    return index;

}
/*
    printf("%f\n", L);
    printf("%f\n", S);
    printf("%i\n", index);
    printf("%i\n", letters);
    printf("%i\n", words);
    printf("%i\n", sentences);
    */
