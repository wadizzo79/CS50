#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Count the number of letters, words and sentences in text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the readability test
    float L = (float) letters / (float) words *
              100; // Calcuate the average number of letters per 100 words
    float S = (float) sentences / (float) words *
              100; // Calculate the avg number of sentences per 100 words
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print the grade level
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

// Counts the number of letters
int count_letters(string text)
{
    int letters = 0;

    // Checks every character
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i])) // Checks if it is a letter
        {
            letters++; // If true add one to number of letters
        }
    }

    return letters; // Returns the number of letters
}

// Count the number of words
int count_words(string text)
{
    int words = 1; // For every space there is one extra word so initialize to 1 instead of 0

    // Checks every character
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == ' ') // Checks for a space
        {
            words++; // If true add one to number of words
        }
    }

    return words; // Returns the number of words
}

// Count the number of sentences
int count_sentences(string text)
{
    int sentences = 0;

    // Checks every character
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Checks for end of sentence
        if (text[i] == '.' || text[i] == '?' ||
            text[i] == '!') // sentences end in a fullstop, question mark,exclamation mark
        {
            sentences++; // If true add one to number of sentences
        }
    }
    return sentences; // Returns the number of sentences
}
