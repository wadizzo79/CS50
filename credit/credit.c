#include <cs50.h>
#include <stdio.h>

long checksum(long a);

int main(void)
{
    //prompt for input
    long number;

    do
    {
         number = get_long("Enter number: ");
    }
    while(number < 0);

    //Calculate checksum
    long number1=checksum(number);
    printf("%li\n", number1);

    //Check for card length and starting digits

    //print amex,mastercard, visa or invalid
}

long checksum(long a)
{
    long b = a % 20;
    return b;
}
