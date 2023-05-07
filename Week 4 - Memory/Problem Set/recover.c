#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *rawFile = fopen(argv[1], "r");
    if (rawFile == NULL)
    {
        printf("Could not open for reading %s.\n", argv[1]);
        return 1;
    }

    const int BLOCKSIZE = 512;
    BYTE buffer[BLOCKSIZE];
    int count = 0;

    FILE *jpg;
    char *filename = malloc(sizeof(char) * 8);

    while (fread(buffer, 1, BLOCKSIZE, rawFile) == BLOCKSIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", count);

            if (count == 0)
            {
                jpg = fopen(filename, "w");
                fwrite(buffer, 1, BLOCKSIZE, jpg);
                count++;
            }
            else
            {
                fclose(jpg);

                jpg = fopen(filename, "w");
                fwrite(buffer, 1, BLOCKSIZE, jpg);
                count++;
            }
        }
        else
        {
            if (count == 0)
            {
                continue;
            }
            else
            {
                fwrite(buffer, 1, BLOCKSIZE, jpg);
            }
        }
    }
    fclose(jpg);
    fclose(rawFile);
    free(filename);
    return 0;
}
