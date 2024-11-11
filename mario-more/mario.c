#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int left_bricks, int middle_space,
               int right_bricks); // allows print_row function to be called in the main function
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
        print_row(n - i - 1, i + 1, 2, i + 1); // prints rows of left sided and right sided bricks
                                               // and constant space in between
    }
}

void print_row(int spaces, int left_bricks, int middle_space,
               int right_bricks) // function that prints the pyramid
{
    for (int j = 0; j < spaces; j++) // print spaces
    {
        printf(" ");
    }
    for (int k = 0; k < left_bricks; k++) // print left sided bricks
    {
        printf("#");
    }
    for (int l = 0; l < middle_space; l++) // print constant space between bricks
    {
        printf(" ");
    }
    for (int m = 0; m < right_bricks; m++) // print right sided bricks
    {
        printf("#");
    }
    printf("\n");
}
