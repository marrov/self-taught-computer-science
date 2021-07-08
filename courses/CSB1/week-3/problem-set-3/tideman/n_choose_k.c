#include <cs50.h>
#include <stdio.h>

// Function prototypes
int nck_factorial(int n, int k);
int nck_recursive(int n, int k);
int nck_multiplicative(int n, int k);
long fact(int n);

// Computes binomial coefficients in different manners
// For theory see: https://en.wikipedia.org/wiki/Binomial_coefficient
int main(void)
{
    int n, k;

    do
    {
        n = get_int("n: ");
    }
    while (n <= 0 || n > 20);

    do
    {
        k = get_int("k: ");
    }
    while (k < 1 || k > n - 1);

    printf("Factorial:      C(%i, %i) = %i\n", n, k, nck_factorial(n, k));
    printf("Recursive:      C(%i, %i) = %i\n", n, k, nck_recursive(n, k));
    printf("Multiplicative: C(%i, %i) = %i\n", n, k, nck_multiplicative(n, k));
}

// Calculate binomial coefficients with the multiplicative formula
int nck_multiplicative(int n, int k)
{
    float sum = 1;

    for (int i = 1; i < k + 1; i++)
    {
        sum *= (n + 1. - i) / i;
    }

    return (int)sum;
}

// Calculate binomial coefficients with recursion explicitly using additive formula
int nck_recursive(int n, int k)
{
    if (n == k || k == 0)
    {
        return 1;
    }
    else
    {
        return nck_recursive(n - 1, k - 1) + nck_recursive(n - 1, k);
    }
}

// Calculate binomial coefficients with recursion implicitly using factorials
int nck_factorial(int n, int k)
{
    return (fact(n)) / (fact(k) * fact(n - k));
}

// Function to calculate the factorial of n (i.e. n!)
long fact(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n*fact(n-1);
    }
}