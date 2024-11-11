#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Program should run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Every character in argv[1] must be a digit
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert argv[1] from a string to an integer
    int key = atoi(argv[1]); // atoi converts a string to an interger

    // Prompt user for plaintext
    string plaintext = get_string("Plaintext: ");
    printf("Ciphertext: ");

    // Encrypt plaintext to ciphertext
    for (int j = 0; j < strlen(plaintext); j++)
    {
        if (isupper(plaintext[j])) // Checks if character is in uppercase
        {
            // Resets value to zero and ensures it loops over back to A
            printf("%c", (plaintext[j] - 65 + key) % 26 + 65);
        }

        else if (islower(plaintext[j])) // Checks if character is in lowercase
        {
            // Resets value to zero and ensures it loops over back to a
            printf("%c", (plaintext[j] - 97 + key) % 26 + 97);
        }

        else
        {
            // if not an upper-case or lower-case letter just print as it is
            printf("%c", plaintext[j]);
        }
    }
    printf("\n");
}
