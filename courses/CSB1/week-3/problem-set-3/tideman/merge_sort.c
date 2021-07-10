#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Global constants

#define len 6
int arr[len] = {5, 2, 1, 3, 6, 4};

//#define len 4
//int arr[len] = {5, 2, 1, 3};

// Is this extra array necessary?
int srt[len] = {0};

// Function prototypes
void merge_sort(int fst, int lst);
void print_array(int array[]);

int main(void)
{

    printf("before:\n");
    print_array(arr);

    merge_sort(0, len - 1);

    printf("\nafter:\n");
    print_array(srt);
}

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

    // merge two halves (temporarily is a dummy print)
    printf("\nMerging halves:\n");
    printf("left  is %i to %i\n", arr[fst], arr[mid - 1]);
    printf("right is %i to %i\n", arr[mid], arr[lst]);

    // Merging pseudocode:
    // 1) Compare first elem of left with first elem of right
    // 2) Put highest in first non-ocuppied position
    // 3) Pop out that element
    // 4) Repeat until sorted

    return;
}

void print_array(int array[])
{
    for (int i = 0; i < len; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}