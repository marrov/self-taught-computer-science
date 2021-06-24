#include <cs50.h>
#include <stdio.h>

bool check_luhn(long num);

int main(void)
{
    long num;
    bool is_valid;

    // Prompt for credit card number
    do
    {
        num = get_long("Number: ");
    }
    while (num <= 0);

    // Decide which type of credit card it is
    if (num / (long)1e13 == 34 || num / (long)1e13 == 37)
    {
        // 15-digits, starting with 34 or 37, so can only (potentially) be AMEX
        is_valid = check_luhn(num);

        if (is_valid)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (num / (long)1e12 == 4 || num / (long)1e15 == 4)
    {
        // 13-digits or 16-digits, starting with 4, so can only (potentially) be VISA
        is_valid = check_luhn(num);

        if (is_valid)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (num / (long)1e14 >= 51 && num / (long)1e14 <= 55)
    {
        // 16-digits, starting with 51 to 55, so can only (potentially) be MASTERCARD
        is_valid = check_luhn(num);

        if (is_valid)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// TODO: Luhn's algorithm
// Function to check if a credit card number is valid using Luhn's algorithm
bool check_luhn(long num)
{
    bool is_valid;

    if (num > 1)
    {
        is_valid = 1;
    }
    else
    {
        is_valid = 0;
    }

    return is_valid;
}