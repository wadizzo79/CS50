#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks); // allows print_row function to be called in the main function
int main(void)
{
    // Prompt for pyramid height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8); // loops if n is less than 1 or greater than 8

    for (int i = 0; i < n; i++) // prints pyramid of specified height
    {
        print_row(n - i - 1, i + 1); // prints rows of spaces and bricks
    }
}

void print_row(int spaces, int bricks) // function that prints the pyramid
{
    for (int j = 0; j < spaces; j++) // print spaces
    {
        printf(" ");
    }
    for (int k = 0; k < bricks; k++) // print bricks
    {
        printf("#");
    }
    printf("\n");
}
