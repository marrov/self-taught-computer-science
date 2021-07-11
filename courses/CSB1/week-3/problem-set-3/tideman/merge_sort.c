#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Global constants

//#define len 6
//int arr[len] = {5, 2, 1, 3, 6, 4};

//#define len 3
//int arr[len] = {5, 2, 1};

#define len 20
int arr[len] = {4, 5, 7, 1, 2, 8, 3, 10, 3, 11, 19, 6, 8, 13, 16, 18, 12, 14, 4, 20};

// Is this extra array necessary?
int srt[len] = {0};

// Function prototypes
void merge_sort(int fst, int lst);
void print_array(int array[], int n);

int main(void)
{

    printf("before:\n");
    print_array(arr, len);

    merge_sort(0, len - 1);

    printf("\nafter:\n");
    print_array(srt, len);
}

void merge_sort(int fst, int lst)
{
    int mid;

    // Check if array has only one element
    if (fst == lst)
    {
        srt[fst] = arr[fst];
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
    printf("left  is %i to %i\n", srt[fst], srt[mid - 1]);
    printf("right is %i to %i\n", srt[mid], srt[lst]);

    // Merging pseudocode:
    // 1) Compare first elem of left with first elem of right
    // 2) Put highest in first non-ocuppied position
    // 3) Pop out that element
    // 4) Repeat until sorted

    // Initialize two indexes, one for each half (left and right)
    int idx_l = 0, idx_r = 0;

    // KEY TO FINISH: GET A VARIABLE SIZE ARRAY
    int n_tmp = lst - fst + 1;
    int tmp[n_tmp];
    for (int i = 0; i < n_tmp; i++)
    {
        tmp[i] = 0;
    }

    print_array(tmp, n_tmp);
    print_array(srt, len);

    for (int i = 0; i <= n_tmp; i++)
    {

        // Check if out of bounds
        if (fst + idx_l > mid - 1)
        {
            printf("No items remaining on left\n");
            for (int j = mid + idx_r; j <= lst; j++)
            {
                tmp[i + (j - (mid + idx_r))] = srt[j];
            }
            break;
        }
        else if (mid + idx_r > lst)
        {
            printf("No items remaining on right\n");
            for (int j = fst + idx_l; j <= mid - 1; j++)
            {
                tmp[i + (j - (fst + idx_l))] = srt[j];
            }
            break;
        }

        // Compare first item in left with first item in right
        if (srt[fst + idx_l] <= srt[mid + idx_r])
        {
            tmp[i] = srt[fst + idx_l];
            idx_l++;
            print_array(tmp, n_tmp);
            print_array(srt, len);
        }
        else
        {
            tmp[i] = srt[mid + idx_r];
            idx_r++;
            print_array(tmp, n_tmp);
            print_array(srt, len);
        }
    }

    print_array(tmp, n_tmp);
    print_array(srt, len);

    // Copy items from temporary array to sorted array
    for (int i = 0; i < n_tmp; i++)
    {
        srt[fst + i] = tmp[i];
    }

    print_array(tmp, n_tmp);
    print_array(srt, len);

    return;
}

void print_array(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}