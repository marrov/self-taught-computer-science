#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Global constants

//#define len 6
//int arr[len] = {5, 2, 1, 3, 6, 4};

#define len 5
int arr[len] = {5, 2, 1, 3, 6};

// Function prototypes
void merge_sort(int fst, int lst);
void print_array(void);

int main(void)
{

    printf("before:\n");
    print_array();

    merge_sort(0, len - 1);

    printf("\nafter:\n");
    print_array();
}

// Question: do I really need to pass the array???
void merge_sort(int fst, int lst)
{
    int mid;

    // Check if array has only one element
    if (fst == lst)
    {
        return;
    }
    else if ((lst - fst + 1) % 2 == 0)
    {
        // Calculate midpoint if array longer than one
        // and has even number of elements
        mid = (lst + fst + 1) / 2;
    }
    else
    {
        // Calculate midpoint if array longer than one
        // and has odd number of elements
        mid = (lst + fst) / 2;
    }

    // divide array in two halves
    printf("\nleft:\n");
    for (int i = fst; i < mid; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
    merge_sort(fst, mid - 1);

    printf("\nright:\n");
    for (int i = mid; i < lst + 1; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
    merge_sort(mid, lst);

    return;
}

void print_array(void)
{
    for (int i = 0; i < len; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
}