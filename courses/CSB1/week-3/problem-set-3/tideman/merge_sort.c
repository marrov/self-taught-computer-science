#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Global constants
#define len 6
int array[len] = {3, 4, 1, 5, 2, 6};

// Function prototypes
void merge_sort(void);
void print_array(void);

int main(void)
{

    printf("before:\n"); print_array();

    merge_sort();

    printf("\nafter:\n"); print_array();
}

void merge_sort(void)
{
    // Pseudocode:
    // 1) Sort left half
    // 2) Sort right half
    // 3) Merge halves
}

void print_array(void)
{
    for (int i = 0; i < len; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}