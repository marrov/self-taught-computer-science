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
        
        // Use Luhn's algorithm to check validity
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

        // Use Luhn's algorithm to check validity
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
        
        // Use Luhn's algorithm to check validity        
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

    is_valid = check_luhn(num);
}

// Function to check if a credit card number is valid using Luhn's algorithm
bool check_luhn(long num)
{
    int  i = 0;
    int  sum_odd  = 0;
    int  sum_even = 0;
    int  last_digit = 0;
    bool is_valid;

    // Luhn's algorithm
    while (num != 0)
    {
        // Update digit position counter
        i++;

        // Extract last digit
        last_digit = num % 10;

        // Update number
        num /= 10;

        // Check if digit position is odd or even and sum digits accordingly
        if (i % 2 == 0)
        {
            if (last_digit * 2 > 9)
            {
                // Last digit can at max be 9, so last digit*2 can at max have two digits
                sum_even += (last_digit * 2 % 10) + (((last_digit * 2) / 10) % 10);
            }
            else
            {
                sum_even += last_digit * 2;
            }
        }
        else
        {
            sum_odd  += last_digit;
        }
    }

    // Make sum of sums
    int sum = sum_even + sum_odd;

    // Check is sum of sums last digit is 0, and define validity accordingly
    if (sum % 10 == 0)
    {
        is_valid = 1;
    }
    else
    {
        is_valid = 0;
    }

    return is_valid;
}