#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calculate_score(string word);

int main(void)
{
    // Get the input from both players
    string player_one = get_string("Player 1: ");
    string player_two = get_string("Player 2: ");

    // Calculate the score
    int score_one = calculate_score(player_one);
    int score_two = calculate_score(player_two);

    // Print the winner
    if (score_one > score_two)
    {
        printf("Player 1 wins\n");
    }
    else if (score_two > score_one)
    {
        printf("Player 2 wins\n");
    }
    else
    {
        printf("Tie\n");
    }
}

int calculate_score(string word)
{
    // Keep track of score
    int score = 0;

    // Compute the score for each character
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isupper(word[i]))
        {
            score += points[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += points[word[i] - 'a'];
        }
    }

    return score;
}
