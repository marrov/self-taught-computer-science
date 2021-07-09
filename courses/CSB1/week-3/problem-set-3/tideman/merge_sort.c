#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Global constants

#define len 6
int arr[len] = {5, 2, 1, 3, 6, 4};

//#define len 2
//int array[len] = {2, 1};

// Function prototypes
void merge_sort(int fst, int lst);
void print_array(void);

int main(void)
{

    printf("before:\n"); print_array();

    merge_sort(0, len - 1);

    printf("\nafter:\n"); print_array();
}

// Question: do I really need to pass the array???
void merge_sort(int fst, int lst)
{
    // Hint: define arrays with two indices, first (fst) and last (lst)

    if (fst != lst)
    {
        // divide array in two halves

        printf("\nleft:\n");
        for (int i = fst; i <= ((lst + 1) / 2 ) - 1; i++)
        {
            printf("%i ", arr[i]);
        }
        printf("\n");

        printf("\nright:\n");
        for (int i = ((lst + 1) / 2 ); i <=  lst; i++)
        {
            printf("%i ", arr[i]);
        }
        printf("\n");
    }
    else
    {
        printf("%i", arr[0]);
    }
}

void print_array(void)
{
    for (int i = 0; i < len; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
}