#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string phrase = get_string("Enter a phrase: ");

    for (int i = 0, length = strlen(phrase); i < length - 1; i++)
    {
        //check if characters are NOT alphabetical
        if (phrase[i] > phrase[i + 1]) // checks if the following letter is greater than the previous letter according to the ASCII format
        {
            printf("Not in alphabetical order.\n");
            return 0;
        }
    }
    printf("Alphabetical order\n");
    return 0;
}
