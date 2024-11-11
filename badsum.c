#include <cs50.h>
#include <stdio.h>

int add_two_ints(int a, int b);

int main(void)
{
    int a = get_int("Enter digit a: ");
    int b = get_int("Enter digit b: ");
    int sum = add_two_ints(a,b);
    printf("The sum is %i\n", sum);

}

int add_two_ints(int a, int b)
{
    int sum = 0;
    if(a > 0)
        for(int i = 0; i < a; sum++, i++);
    else
        for(int i = 0; i < 0; sum--, i++);
    if(b > 0)
        for(int i = 0; i < b; sum++, i++);
    else
        for(int i = 0; i < 0; sum--, i++);
    return sum;
}
