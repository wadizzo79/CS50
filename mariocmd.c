#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./mario number\n" ); //prevents segmentation fault
        return 1;
    }
    int height = atoi(argv[1]);
}
