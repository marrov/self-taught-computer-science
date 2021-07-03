#include <cs50.h>
#include <stdio.h>

// Function prototypes
int nck_factorial(int n, int k);
long fact(int n);

// Compute binomial coefficients in different manners
int main(void)
{
    int n, k;

    do
    {
        n = get_int("n: ");
    }
    while (n <= 0 || n > 15);

    do
    {
        k = get_int("k: ");
    }
    while (k < 1 || k > n - 1);

    printf("C(%i, %i) = %i\n", n, k, nck_factorial(n, k));
}

// Calculate binomial coefficients with recursion explicitly using additive formula
int nck_recursive(int n, int k)
{
    // TODO: use (n k) = (n-1 k-1) + (n-1 k)
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
