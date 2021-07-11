#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Global constants

#define len 20
int arr[len] = {4, 5, 7, 1, 2, 8, 3, 9, 3, 6, 2, 6, 8, 1, 5, 3, 7, 9, 4, 1};

// Function prototypes
void merge_sort(int fst, int lst);
void merge(int fst, int mid, int lst);
void print_array(int array[], int n);

int main(void)
{

    printf("before:\n");
    print_array(arr, len);

    merge_sort(0, len - 1);

    printf("\nafter:\n");
    print_array(arr, len);
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
        // element and has even number of elements
        mid = (lst + fst + 1) / 2;
    }
    else
    {
        // Calculate midpoint if array longer than one
        // element and has odd number of elements
        mid = (lst + fst) / 2;
    }

    // Sort left half, then sort right half
    merge_sort(fst, mid - 1);
    merge_sort(mid, lst);

    // Merge both halves
    merge(fst, mid, lst);

    return;
}

void merge(int fst, int mid, int lst)
{
    // Initialize two indexes, one for each half (left and right)
    int idx_l = 0, idx_r = 0;

    // Initialize a temporary array of size equal to combined sizes of left and right
    int n_tmp = lst - fst + 1;
    int tmp[n_tmp];
    for (int i = 0; i < n_tmp; i++)
    {
        tmp[i] = 0;
    }

    // Loop for merging both halves
    for (int i = 0; i <= n_tmp; i++)
    {
        // Check if out of bounds
        if (fst + idx_l > mid - 1)
        {
            // If out of bounds in left, copy all remaining items in right
            for (int j = mid + idx_r; j <= lst; j++)
            {
                tmp[i + (j - (mid + idx_r))] = arr[j];
            }
            break;
        }
        else if (mid + idx_r > lst)
        {
            // If out of bounds in right, copy all remaining items in left
            for (int j = fst + idx_l; j <= mid - 1; j++)
            {
                tmp[i + (j - (fst + idx_l))] = arr[j];
            }
            break;
        }

        // Compare first item in left with first item in right and copy the highest
        if (arr[fst + idx_l] >= arr[mid + idx_r])
        {
            tmp[i] = arr[fst + idx_l];
            idx_l++;
        }
        else
        {
            tmp[i] = arr[mid + idx_r];
            idx_r++;
        }
    }

    // Copy items from temporary array to original array
    for (int i = 0; i < n_tmp; i++)
    {
        arr[fst + i] = tmp[i];
    }
}

void print_array(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}