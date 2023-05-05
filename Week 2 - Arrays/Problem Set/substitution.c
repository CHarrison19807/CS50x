#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < strlen(key); i++) //Checks if key contains non-alphabet symbols
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain letters.\n");
            return 1;

        }
        for (int j = i + 1; j < strlen(key); j++) //Checks for duplicate characters
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                printf("Key must not contain duplicate letters\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    encrypt(plaintext, key);
}
void encrypt(string plaintext, string key)
{
    int textLength = strlen(plaintext);
    const int keyLength = 26;
    for (int i = 0; i < keyLength; i++)
    {
        key[i] = toupper(key[i]);
    }

    for (int j = 0; j < textLength; j++)
    {
        if (isupper(plaintext[j]))
        {
            int letter = plaintext[j] - 65;
            printf("%c", key[letter]);
        }
        else if (islower(plaintext[j]))
        {
            int letter = plaintext[j] - 97;
            printf("%c", key[letter] + 32);
        }
        else
        {
            printf("%c", plaintext[j]);
        }
    }
    printf("\n");



}
