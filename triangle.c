#include <cs50.h>
#include <stdio.h>

bool valid_triangle(int a, int b, int c);

int main(void)
{
    int x = get_int("Enter x: ");
    int y = get_int("Enter y: ");
    int z = get_int("Enter z: ");
    bool a = valid_triangle(x, y, z);
    printf("%s\n", a ? "true" : "false");
}

bool valid_triangle(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return false;
    }

    if((a + b <= c) || (b + c <= a) || (a + c <= b) )
    {
    return false;
    }

    else
    {
        return true;
    }
}
