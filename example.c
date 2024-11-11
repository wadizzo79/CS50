#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string first_name = get_string("Enter your first name: ");
    string last_name = get_string("Enter your last name: ");
    int age = get_int("Age: ");
    string contact = get_string("Contact: ");

    printf("Hello, %s %s\n", first_name, last_name);
    printf("Age: %i\n", age);
    printf("Number: %s\n", contact);
}
